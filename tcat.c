#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

const static char format[] = "%Y-%m-%dT%H:%M:%SZ\t";

static void io_error(FILE* file) {
  if (feof(file)) {
    fputs("file closed", stderr);
  } else if (ferror(file)) {
    perror("file error");
  } else {
    fputs("unknown error", stderr);
  }
  exit(EXIT_FAILURE);
}

static void print_time() {
  enum { buffer_max = 32 };
  char buffer[buffer_max];
  time_t rawtime;
  time(&rawtime);
  struct tm* timeinfo = localtime(&rawtime);
  const size_t len = strftime(buffer, buffer_max, format, timeinfo);
  if(len != fwrite(buffer, 1, len, stdout)){
    io_error(stdout);
  }
}

int main(int argc, char** argv) {
  int last = '\n';
  int c;
  for(c = fgetc(stdin); c != EOF; c = fgetc(stdin)) {
    if (last == '\n') {
      print_time();
    }
    if (EOF == fputc(c, stdout)) {
      io_error(stdout);
    }
    last = c;
  }

  if (ferror(stdin)) {
    perror("output error");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
