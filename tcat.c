#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

static void output_error() {
  if (feof(stdout)) {
    fputs("stdout closed", stderr);
  } else if (ferror(stdout)) {
    perror("error writing to stdout");
  } else {
    fputs("unknown error", stderr);
  }
  exit(EXIT_FAILURE);
}

static void print_time() {
  enum { buffer_max = 20 };
  char buffer[buffer_max];
  time_t rawtime;
  time(&rawtime);
  struct tm* timeinfo = localtime(&rawtime);
  const size_t len = strftime(buffer, buffer_max, "%Y:%m:%d%H:%M:%S\t", timeinfo);
  if(len != fwrite(buffer, 1, len, stdout)){
    output_error();
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
      output_error();
    }

    last = c;
  }

  return EXIT_SUCCESS;
}
