#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define FNVM_DIR_NAME "/.fnvm"

char *get_fnvm_home_dir(void) {
  const char *home = getenv("HOME");
  if (!home) {
    fprintf(stderr, "Home is not defined\n");
    return NULL;
  }
  size_t len = strlen(home) + strlen(FNVM_DIR_NAME) + 1;
  char *full_path = malloc(len);
  if (!full_path) {
    perror("malloc:");
    return NULL;
  }
  snprintf(full_path, len, "%s%s", home, FNVM_DIR_NAME);
  return full_path;
}

void ensure_fnvm_dir_exists(void) {
  char *dir = get_fnvm_home_dir();
  if (!dir) {
    return;
  }
  struct stat st = {0};
  if (stat(dir, &st) == -1) {
    if (mkdir(dir, 0700) == -1) {
      perror("Failed to create fnvm directory:");
    }
  }
  free(dir);
}
