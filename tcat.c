#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

enum {
  version_major = 0,
  version_minor = 1,
  version_patch = 2
};

static const char program_name[] = "tcat";
static const char env_flag[]     = "TCAT_FORMAT";
static const char *format        = "%FT%T%z\t";

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

static inline void usage(FILE* output) {
  fprintf(output,
          "\n"
          "Available Options:\n"
          "\t-v, --version\tprint %s version\n"
          "\t-h, --help\tprint this help\n"
          "\n"
          "Help can be found at https://github.com/marcomorain/tcat\n",
          program_name);
}

static int match(const char* x, const char* a, const char* b) {
  return (!strcmp(x, a)) || (!strcmp(x, b));
}

int main(int argc, char** argv) {

  int bad_usage = 0;

  for (int i = 1; i < argc; i++) {
    if (match(argv[i], "-v", "--version")) {
      version(stdout);
      return EXIT_SUCCESS;
    }

    if (match(argv[i], "-h", "--help")) {
      usage(stdout);
      return EXIT_SUCCESS;
    }

    // Show all bad options
    bad_usage = 1;
    fprintf(stderr, "Invalid option:\t%s\n", argv[i]);
  }

  // Show correct usage
  if (bad_usage) {
    usage(stderr);
    return EXIT_FAILURE;
  }

  if (isatty(fileno(stdin))) {
    fprintf(stderr, "Warning: input is from TTY\n");
  }

  char *format_env = getenv(env_flag);
  if (format_env) {
    format = format_env;
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
