
/*
 * week5_task2_struct_save_load.c
 * Name: Mohammad Anas
 * Surname: [ANAS]
 * Student ID: 251ADB003
 *
 * Saves a student record to a text file and loads it back.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
  char name[MAX_NAME_LEN];
  int age;
  float gpa;
} Student;

/* These signatures must remain unchanged for the autograder. */
int save_student(const Student* s, const char* filename);
int load_student(const char* filename, Student* out);

int main(void) {
  Student s1 = {0};
  strcpy(s1.name, "Alice");
  s1.age = 21;
  s1.gpa = 3.75f;

  Student loaded = {0};
  const char* filename = "student.txt";

  printf("Saving student to file...\n");

  /* Stop if saving fails so we do not try to load an invalid file. */
  if (save_student(&s1, filename) != 0) {
    fprintf(stderr, "Error saving student.\n");
    return EXIT_FAILURE;
  }

  printf("Loading student from file...\n");

  /* Read the record into a separate structure to verify persistence. */
  if (load_student(filename, &loaded) != 0) {
    fprintf(stderr, "Error loading student.\n");
    return EXIT_FAILURE;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age,
         loaded.gpa);

  return EXIT_SUCCESS;
}

int save_student(const Student* s, const char* filename) {
  FILE* fp = fopen(filename, "w");

  if (fp == NULL) {
    return -1;
  }

  /* Store the three fields on one line in the required text format. */
  int result = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

  /* Check both writing and closing so file errors are not ignored. */
  int close_result = fclose(fp);

  if (result < 0 || close_result != 0) {
    return -1;
  }

  return 0;
}

int load_student(const char* filename, Student* out) {
  FILE* fp = fopen(filename, "r");

  if (fp == NULL) {
    return -1;
  }

  /* Limit the name width to prevent writing beyond the name array. */
  int fields = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);

  int close_result = fclose(fp);

  if (fields != 3 || close_result != 0) {
    return -1;
  }

  return 0;
}
