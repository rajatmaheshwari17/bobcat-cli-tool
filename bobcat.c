#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void process_file(const char *file_name, bool *error_occurred) {
  int fd;
  ssize_t read_bytes, written_bytes;
  char buffer[BUFFER_SIZE];
  struct stat statbuf;

  if (strcmp(file_name, "-") == 0) {
    fd = STDIN_FILENO;
    if (fstat(fd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
      warnx("%s: Is a directory", file_name);
      *error_occurred = true;
      return;
    }
  } else {
    if (stat(file_name, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
      warnx("%s: Is a directory", file_name);
      *error_occurred = true;
      return;
    }
    fd = open(file_name, O_RDONLY);
    if (fd == -1) {
      warn("%s", file_name);
      *error_occurred = true;
      return;
    }
  }

  while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) > 0) {
    char *out_ptr = buffer;
    while (read_bytes > 0) {
      written_bytes = write(STDOUT_FILENO, out_ptr, read_bytes);
      if (written_bytes == -1 && written_bytes != read_bytes) {
        warn("%s", "write error");
        *error_occurred = true;
        break;
      }
      read_bytes -= written_bytes;
      out_ptr += written_bytes;
    }
  }

  if (read_bytes == -1) {
    warn("%s", "read error");
    *error_occurred = true;
  }

  if (fd != STDIN_FILENO) {
    close(fd);
  }
}

int main(int argc, char *argv[]) {
  bool any_errors = false;

  if (argc == 1) {
    process_file("-", &any_errors);
  } else {
    for (int i = 1; i < argc; i++) {
      bool error_occurred = false;
      process_file(argv[i], &error_occurred);
      if (error_occurred) {
        any_errors = true;
      }
    }
  }
  return any_errors ? 1 : 0;
}
