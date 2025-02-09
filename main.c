#include <stdio.h>
void print_usage() {
  printf("Usage:\n");
  printf("\tfnvm ls: List all installed versions\n");
  printf("\tfnvm rm <version>: Delete specific version\n");
  printf("\tfnvm install <version>: Install specific version\n");
}

int main(int argc, char **argv) {
  if (argc == 1) {
    print_usage();
    return 0;
  }
  return 0;
}
