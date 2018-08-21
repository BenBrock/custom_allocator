#include <vector>
#include "custom_allocator.hpp"

int main(int argc, char** argv) {
  std::vector<int, custom_allocator<int>> vec;
  return 0;
}
