#include <stdio.h>

<<<<<<< HEAD
/*
    Task:
    Write a function `int sum_to_n(int n)` that computes
    the sum of all integers from 1 up to n using a for loop.

    In main():
      - Ask user for a positive integer n
      - If n < 1, print an error
      - Otherwise, call sum_to_n and print the result
*/

int sum_to_n(int n) {
    // TODO: implement sum with a for loop
    return 0; // placeholder
}

int main(void) {
    int n;
=======
int sum_to_n(int n)
{
  int sum = 0;

  for (int i = 1; i <= n; i++)
  {
    sum += i;
  }

  return sum;
}

int main(void)
{
  int n;
>>>>>>> 03cbb44 (completed task 2)

    printf("Enter a positive integer n: ");
    scanf("%d", &n);

<<<<<<< HEAD
    // TODO: validate input, call function, and print result

    return 0;
=======
  if (scanf("%d", &n) != 1)
  {
    printf("Error: please enter an integer.\n");
    return 1;
  }

  if (n < 1)
  {
    printf("Error: n must be at least 1.\n");
  }
  else
  {
    printf("Sum from 1 to %d is %d.\n", n, sum_to_n(n));
  }

  return 0;
>>>>>>> 03cbb44 (completed task 2)
}
