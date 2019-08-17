#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <queue>
#include <future>
#include <functional>

#define Err(comm) std::cerr << (comm) << std::endl;
#define OK 0
#define ERR -1
#define END "\r\n"
#define BREAK "\r\n\r\n"


struct Executor {
  std::mutex mtx_;
  int requested = 0;
  int finish;
  bool stop;
  std::condition_variable cond_;
  std::vector<std::thread> workers;
  std::queue< std::function<void()> > tasks;
public:
  Executor(int threads, int fin) : finish(fin), stop(false) {
    for(int i = 0; i < threads; i++) {
      workers.emplace_back(std::thread([this]{
            while (!this->stop) {
              std::function<void()> task;
              {
                std::unique_lock<std::mutex> lock(this->mtx_);
                this->cond_.wait(lock,
                                     [this]{ return this->requested >= this->finish || !this->tasks.empty(); });
                if(this->requested >= this->finish && this->tasks.empty()) {
                  this->stop = true;
                  return;
                }
                task = std::move(this->tasks.front());
                this->tasks.pop();
              }
              task();
            }
          }));
    }
  }

  void notify_done() {
    std::lock_guard<std::mutex> l(mtx_);
    requested++;
  }

  template<class F, class... Args>
  auto submit(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>
  {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(mtx_);
      tasks.emplace([task](){ (*task)(); });
    }
    cond_.notify_one();
    return res;
  }

  ~Executor() {
    {
      std::unique_lock<std::mutex> lock(mtx_);
      stop = true;
    }
    cond_.notify_all();
    for(std::thread &worker: workers) {
      if (worker.joinable()) {
        worker.join();
      }
    }
  }
};

typedef struct {
    int bytes;
    int words;
    int lines;
} Count;

Count char_count(char* buffer, int len) {
  Count c = {0, 0, 0};
  bool inword = false;
  //std::cout << "...... start ......." << std::endl;
  for (int i =0; i < len ;i++) {
    c.bytes++;
    if (buffer[i] == ' ') {
      if (inword) {
        inword = false;
        c.words++;
      }
    } else if (buffer[i] == '\n') {
      c.lines++;
    } else {
      inword = true;
    }
  }
  //std::cout << "...... done ......." << std::endl;
  return c;
}

Count Add(Count a, Count b) {
  Count c = {a.bytes+b.bytes, a.words+b.words, a.lines+b.lines};
  return c;
}

char* endOfHeader(char* header, int len) {
  auto found = strstr(header, BREAK);
  if (found != NULL) {
    return found+4;
  }
  return NULL;
}

int toLength(char* found) {
  //std::cout << "##Header>" << found << std::endl;
  auto ch = strtok(found, " \r\n");
  //std::cout << ">>>>>>CT" << ch << std::endl;
  if (ch != NULL) {
    ch = strtok(NULL, " \r\n");
    //std::cout << ">>>>>>NXT:" << ch << std::endl;
    return atoi(ch);
  }
  return 0;
}

int contentLength(char* header) {
  auto found = strstr(header, "Content-Length: ");
  if (found == NULL) {
    found = strstr(header, "Content-length: ");
    if (found == NULL) {
      return 0;
    }
  }
  return toLength(found);
}

Count word_count(int conn, int readLength, int contentLen) {
  Count c = {0, 0, 0};
  //std::cout << "Con:" << conn << '[' << contentLen << "] read[" << readLength << "]------------------------------" << std::endl;
  if (contentLen >0 && contentLen <= readLength) {
    return c;
  }
  int buf_size = contentLen == 0 ? 100 : 2048;
  std::unique_ptr<char[]> buffer(new char[buf_size]);
  auto buf = buffer.get();

  int n = recv(conn, buf, buf_size - 1, 0);
  if (n < 0) {
    Err("recv error");
    return c;
  }
  if (n == 0) {
    return c;
  }
  buf[std::min(n+1, buf_size-1)] = 0;

  //std::cout << '[' << contentLen << "]------------------------------" << std::endl;
  //std::cout << buf << std::endl;
  //std::cout << '[' << readLength << "]------------------------------" << std::endl;

  if (contentLen > 0) {
    return Add(char_count(buf, n), word_count(conn, readLength+n, contentLen));
  }
  auto found = endOfHeader(buf, n-1);
  if (found == NULL) {
    //std::cout << buf << std::endl;
    auto bodyLength = contentLength(buf);
    //std::cout << "Not Found" << std::endl;
    return word_count(conn, readLength, bodyLength);
  }

  auto bodyLength = contentLength(buf);
  auto len = found - buf;
  return Add(char_count(found, len), word_count(conn, len, bodyLength));
}

int handle_client(int conn, Executor* exec) {
  Count cnt = word_count(conn, 0, 0);

  std::unique_ptr< std::ostringstream > wc(new std::ostringstream);
  auto result = wc.get();
  *result << cnt.bytes << '\t' << cnt.words << '\t' << cnt.lines << END;
  auto data = result->str().c_str();

  std::unique_ptr< std::ostringstream > oss(new std::ostringstream);
  auto out = oss.get();

  *out << "HTTP/1.1 200 OK" << END;
  *out << "Server: unkown" << END;
  *out << "Cache-Control: no-cache, no-store, must-revalidate" << END;
  *out << "Content-Length: " << strlen(data) << END;
  *out << "Connection: close" << END;
  *out << "Content-Type: text/plain" << END;
  *out << END;
  *out << data;
  auto response = out->str().c_str();

  int n = send(conn, response, strlen(response), 0);
  if (n < 0) {
    Err("send error");
  }

  //std::cout << response;

  exec->notify_done();

  close(conn);
  return OK;
}

int initServerFd(int *srv_fd, sockaddr_in *addr, int port) {
  *srv_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (*srv_fd < 0) {
    return ERR;
  }

  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);
  addr->sin_addr.s_addr = htons(INADDR_ANY);

  int opt = 1;
  setsockopt(*srv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  return OK;
}

int main() {
  signal(SIGPIPE, SIG_IGN);
  const int ignore = 0;

  int srv_fd = 0;
  struct sockaddr_in sa;

  if (initServerFd(&srv_fd, &sa, 5100) != OK) {
    Err("socket error!!")
    return -1;
  }

  if (bind(srv_fd, (struct sockaddr*)&sa, sizeof(sa)) < 0) {
    Err("bind error!!")
    return -1;
  }

  if (listen(srv_fd, SOMAXCONN) < 0) {
    Err("listen() error");
    return -1;
  }

  Executor exec(4, 1000);

  while (!exec.stop) {
    //std::cout << "######## accept...." << std::endl;
    int conn = accept(srv_fd, 0, 0);
    if (conn < 0) {
      Err("accept error");
    }

    exec.submit([conn, &exec]{
        return handle_client(conn, &exec);
      });
  }

  return 0;
}
