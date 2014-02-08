#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

enum {
  version_major = 0,
  version_minor = 1,
  version_patch  = 0
};

static const char program_name[] = "tcat";
static const char format[]       = "%Y-%m-%dT%H:%M:%S %Z\t";

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
  struct tm timeinfo;
  gmtime_r(&rawtime, &timeinfo);
  const size_t len = strftime(buffer, buffer_max, format, &timeinfo);
  if(len != fwrite(buffer, 1, len, stdout)){
    io_error(stdout);
  }
}

static void version(FILE* output) {
  fprintf(output, "%s version %d.%d.%d\n",
    program_name,
    version_major,
    version_minor,
    version_patch);
}

static void usage(FILE* output, const char* arg) {
  if (arg) {
    fprintf(output, "Invalid option: %s\n", arg);
  }
  fprintf(output,
          "Options:\n"
          "  -v, --version print %s version\n"
          "  -h, --help    print this help\n"
          "Help can be found at github.com/marcomorain/tcat\n",
          program_name);
}

static int match(const char* x, const char* a, const char* b) {
  return (!strcmp(x, a)) || (!strcmp(x, b));
}

int main(int argc, char** argv) {

  for (int i = 1; i < argc; i++) {
    if (match(argv[i], "-v", "--version")) {
      version(stdout);
      return EXIT_SUCCESS;
    }

    if (match(argv[i], "-h", "--help")) {
      usage(stdout, 0);
      return EXIT_SUCCESS;
    }

    // Unrecognised command
    usage(stderr, argv[i]);
    return EXIT_FAILURE;
  }

  int last = '\n';
  for(int c = fgetc(stdin); c != EOF; c = fgetc(stdin)) {
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
