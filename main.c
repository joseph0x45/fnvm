#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/urlapi.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *get_fnvm_home() {
  char *home = getenv("HOME");
  if (!home) {
    return NULL;
  }
  size_t fnvm_home_len = strlen(home) + strlen("/.fnvm") + 1;
  char *fnvm_home = malloc(fnvm_home_len);
  if (!fnvm_home_len) {
    return NULL;
  }
  snprintf(fnvm_home, fnvm_home_len, "%s/.fnvm", home);
  return fnvm_home;
}

void print_usage() {
  printf("Usage:\n");
  printf("\tfnvm ls: List all installed versions.\n");
  printf("\tfnvm install <version>: Install specific version. The version "
         "should be under the version number without the 'v' so for example "
         "you would run `fnvm install 18.19.0`\n");
  printf("\tfnvm rm <version>: Delete specific version\n");
}

void extract_version(char *dir_name) { return; }

void list_installed_versions() {
  printf("Installed versions:\n");
  DIR *d = opendir(get_fnvm_home());
  if (d == NULL) {
    return;
  }
  struct dirent *dir;
  while ((dir = readdir(d))) {
    if (dir->d_type != DT_DIR && strcmp(dir->d_name, ".") != 0 &&
        strcmp(dir->d_name, "..") != 0) {
      printf("  - %s\n", dir->d_name);
    }
  }
  closedir(d);
}

char *construct_download_link() { return ""; }

size_t writecb(void *contents, size_t size, size_t nmeb, void *userp) {
  return size * nmeb;
}

// send basic GET request to see if version does exist
// download and move to fnvm home
void install_version(char *version) {
  char download_url[256];
  snprintf(download_url, sizeof(download_url),
           "https://nodejs.org/download/release/v%s/", version);
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, download_url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecb);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      printf("Something went wrong: %s", curl_easy_strerror(res));
      curl_easy_cleanup(curl);
      return;
    }
    long status_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
    if (status_code != 200) {
      printf("Version %s not found!\n", version);
      return;
    }
  }
  curl_easy_cleanup(curl);
}

void remove_version(char *version) {}

int main(int argc, char **argv) {
  if (argc == 1 || argc > 3) {
    print_usage();
    return 0;
  }
  switch (argc) {
  case 2:
    if (strcmp(argv[1], "ls") != 0) {
      print_usage();
      break;
    }
    list_installed_versions();
    break;
  case 3:
    if (strcmp(argv[1], "install") == 0) {
      install_version(argv[2]);
      break;
    }
    if (strcmp(argv[1], "rm") == 0) {
      remove_version(argv[2]);
      break;
    }
    print_usage();
  }
  return 0;
}
