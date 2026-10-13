
/*
 * week5_task1_file_io.c
 * Name: Mohammad Anas
 * Surname: [ANAS]
 * Student ID: 251ADB003
 *
 * Writes a few lines to a text file and reads them back.
 */

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_FILENAME "data.txt"
#define LINE_LEN 256

int main(int argc, char* argv[]) {
  FILE* fp;
  const char* filename = DEFAULT_FILENAME;
  char line[LINE_LEN];
  int line_count = 0;

  /* Allow the user to choose a filename; otherwise use data.txt. */
  if (argc > 1) {
    filename = argv[1];
  }

  printf("Writing lines to %s...\n", filename);

  /* Open the file in write mode, creating it if necessary. */
  fp = fopen(filename, "w");
  if (fp == NULL) {
    perror(filename);
    return EXIT_FAILURE;
  }

  /* Write two lines so there is content to read back. */
  if (fprintf(fp, "Hello, file I/O in C!\n") < 0 ||
      fprintf(fp, "This is another line.\n") < 0) {
    perror("Writing file");
    fclose(fp);
    return EXIT_FAILURE;
  }

  if (fclose(fp) != 0) {
    perror("Closing file");
    return EXIT_FAILURE;
  }

  /* Reopen the same file in read mode. */
  fp = fopen(filename, "r");
  if (fp == NULL) {
    perror(filename);
    return EXIT_FAILURE;
  }

  printf("Reading contents:\n");

  /* Print each line and count how many lines were read. */
  while (fgets(line, sizeof line, fp) != NULL) {
    printf("%s", line);
    line_count++;
  }

  if (ferror(fp)) {
    perror("Reading file");
    fclose(fp);
    return EXIT_FAILURE;
  }

  if (fclose(fp) != 0) {
    perror("Closing file");
    return EXIT_FAILURE;
  }

  printf("Lines read: %d\n", line_count);

  return EXIT_SUCCESS;
}
