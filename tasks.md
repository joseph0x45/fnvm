#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define FNVM_DIR_NAME ".fnvm"
#define MAX_PATH_LEN 4096

// Resolves and stores the path to ~/.fnvm
const char *get_fnvm_home_dir() {
    static char path[MAX_PATH_LEN];  // static so it's usable outside
    const char *home = getenv("HOME");

    if (!home) {
        fprintf(stderr, "Error: $HOME is not set.\n");
        return NULL;
    }

    snprintf(path, sizeof(path), "%s/%s", home, FNVM_DIR_NAME);
    return path;
}
