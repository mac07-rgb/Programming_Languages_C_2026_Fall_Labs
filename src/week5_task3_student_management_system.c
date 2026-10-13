
/*
 * week5_task3_student_management_system.c
 * Name: Mohammad Anas
 * Surname: [ANAS]
 * Student ID: 251ADB003
 *
 * A small student database that saves its records in students.txt.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
  char name[NAME_LEN];
  int id;
  float gpa;
} Student;

/* Keep these function signatures unchanged for the autograder. */
int load_students(Student arr[], int max);
int save_students(const Student arr[], int count);
void add_student(Student arr[], int* count);
void list_students(const Student arr[], int count);
int read_line(const char* prompt, char* buf, size_t size);

int main(void) {
  Student students[MAX_STUDENTS];
  int count = 0;
  char input[LINE_LEN];
  int running = 1;

  /* Load saved records so they remain available between runs. */
  count = load_students(students, MAX_STUDENTS);
  printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

  while (running) {
    printf("\n=== Student Management System ===\n");
    printf("1. List students\n");
    printf("2. Add student\n");
    printf("3. Save and Exit\n");

    int choice;
    if (read_line("Select an option: ", input, sizeof input) != 0) {
      choice = 3;
    } else {
      char* end;
      long value = strtol(input, &end, 10);
      choice = (end != input && *end == '\0' && value >= 1 && value <= 3)
                   ? (int)value
                   : 0;
    }

    switch (choice) {
      case 1:
        list_students(students, count);
        break;

      case 2:
        add_student(students, &count);
        break;

      case 3:
        /* Only report success if the file was saved successfully. */
        if (save_students(students, count) != 0) {
          fprintf(stderr, "Error saving student data.\n");
          return EXIT_FAILURE;
        }
        printf("Data saved. Goodbye!\n");
        running = 0;
        break;

      default:
        printf("Invalid option. Try again.\n");
    }
  }

  return EXIT_SUCCESS;
}

/* Read one complete line and remove its trailing newline. */
int read_line(const char* prompt, char* buf, size_t size) {
  printf("%s", prompt);
  fflush(stdout);

  if (fgets(buf, (int)size, stdin) == NULL) {
    return -1;
  }

  size_t len = strcspn(buf, "\r\n");

  if (buf[len] == '\0' && len == size - 1) {
    /* Discard the rest of an overlong line to keep input aligned. */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
  }

  buf[len] = '\0';
  return 0;
}

int load_students(Student arr[], int max) {
  FILE* fp = fopen(DATA_FILE, "r");

  /* A missing file is normal on the first run. */
  if (fp == NULL) {
    return 0;
  }

  char line[LINE_LEN];
  int count = 0;

  while (count < max && fgets(line, sizeof line, fp) != NULL) {
    Student temp;
    char extra;

    /* Parse into a temporary record before accepting a line. */
    if (sscanf(line, "%49[^,],%d,%f %c", temp.name, &temp.id, &temp.gpa,
               &extra) == 3) {
      if (temp.name[0] != '\0' && temp.gpa >= 0.0f && temp.gpa <= 4.0f) {
        arr[count++] = temp;
      }
    }
    /* Blank or malformed lines are skipped. */
  }

  fclose(fp);
  return count;
}

int save_students(const Student arr[], int count) {
  FILE* fp = fopen(DATA_FILE, "w");

  if (fp == NULL) {
    return -1;
  }

  /* Rewrite the file so it contains the current complete list. */
  for (int i = 0; i < count; i++) {
    if (fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa) < 0) {
      fclose(fp);
      return -1;
    }
  }

  if (fclose(fp) != 0) {
    return -1;
  }

  return 0;
}

void add_student(Student arr[], int* count) {
  char name[LINE_LEN];
  char id_text[LINE_LEN];
  char gpa_text[LINE_LEN];
  char* end;
  long id;
  float gpa;

  /* Check capacity before asking for input. */
  if (*count >= MAX_STUDENTS) {
    printf("Cannot add more students (limit reached).\n");
    return;
  }

  if (read_line("Enter name: ", name, sizeof name) != 0) {
    return;
  }
  if (read_line("Enter ID: ", id_text, sizeof id_text) != 0) {
    return;
  }
  if (read_line("Enter GPA: ", gpa_text, sizeof gpa_text) != 0) {
    return;
  }

  /* Names must be nonempty and cannot contain the file delimiter. */
  if (name[0] == '\0' || strchr(name, ',') != NULL ||
      strlen(name) >= NAME_LEN) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  /* Parse the ID and reject extra characters or values outside int range. */
  id = strtol(id_text, &end, 10);
  if (id_text[0] == '\0' || end == id_text || *end != '\0' ||
      id < -2147483647L - 1L || id > 2147483647L) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  /* Parse GPA and ensure it is a number between 0.0 and 4.0. */
  gpa = strtof(gpa_text, &end);
  if (gpa_text[0] == '\0' || end == gpa_text || *end != '\0' || gpa < 0.0f ||
      gpa > 4.0f) {
    printf("Invalid input. Student not added.\n");
    return;
  }

  /* Add the validated record only after every check has passed. */
  strcpy(arr[*count].name, name);
  arr[*count].id = (int)id;
  arr[*count].gpa = gpa;
  (*count)++;

  printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
  if (count == 0) {
    printf("No students found.\n");
    return;
  }

  printf("%-5s %-20s %.0sGPA\n", "ID", "Name", "");
  for (int i = 0; i < count; i++) {
    printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
  }
}
