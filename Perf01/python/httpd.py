# -*- coding: utf-8 -*-

import time
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, wait
from functools import reduce
from http.server import BaseHTTPRequestHandler, HTTPServer

HOST_NAME = 'localhost'
PORT_NUMBER = 5100

def wd(ss):
    is_word = True
    ch_cnt = len(ss)
    wd_cnt = 0
    lf_cnt = 0
    for i, c in enumerate(ss):
        if c == ' ':
            is_word = False
        elif '\n' in c  or '\r' in c:
            lf_cnt += 1
        else:
            if is_word == False:
                wd_cnt += 1
                is_word = True

    return ch_cnt, wd_cnt, lf_cnt


def count(fp, content_length):
    with ThreadPoolExecutor(max_workers=16) as e:
        futures = []
        size = 4096
        read_size = 0
        while read_size < content_length:
            remain = content_length - read_size
            sz = size if remain > size else remain
            by = fp.read(sz)
            futures.append(e.submit(wd, by.decode('utf-8')))
            read_size = read_size + len(by)

        result = wait(futures)
        return reduce(lambda x,y: (x[0]+y[0], x[1]+y[1], x[2]+y[2]),
                      [rs.result() for rs in result.done])


class RequestHandler(BaseHTTPRequestHandler):

    def do_POST(s):
        s.send_response(200)
        s.send_header('Content-type', 'text/plain')
        s.end_headers()

        length = int(s.headers['Content-Length'])
        content = '{}'.format(count(s.rfile, length))
        s.wfile.write(content.encode())

if __name__ == '__main__':
    srv_cls = HTTPServer
    httpd = srv_cls((HOST_NAME, PORT_NUMBER), RequestHandler)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass

    httpd.server_close()

    print("Server Stops - %s:%s" % (HOST_NAME, PORT_NUMBER))


