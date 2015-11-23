#include <iostream>
#include <cstdlib>

int tarai(int x, int y, int z) {
  return x <= y
    ? y
    :tarai(tarai(x - 1, y, z),
           tarai(y - 1, z, x),
           tarai(z - 1, x, y) );
}

int main(int argc, char* argv[]) {
  if (argc < 4) return 1;
  int x = std::atoi(argv[1]);
  int y = std::atoi(argv[2]);
  int z = std::atoi(argv[3]);
  std::cout << tarai(x, y, z) << std::endl;
  return 0;
}
