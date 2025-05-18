#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_VERSION("1.0");

static int row;
static int col;
static int matrix[10000];

module_param(row, int, 0);
module_param(col, int, 0);
module_param_array(matrix, int, NULL, 0);

static int sum_matrix(int matrix[], int row, int col) {
  int sum = 0, i, j;
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++)
      sum += matrix[i * col + j];
  return sum;
}

static int count_pos(int matrix[], int row, int col) {
  int i, j, count = 0;
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++)
      if (matrix[i * col + j] > 0)
        count++;
  return count;
}

static int count_neg(int matrix[], int row, int col) {
  int i, j, count = 0;
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++)
      if (matrix[i * col + j] < 0)
        count++;
  return count;
}

static int sum_even(int matrix[], int row, int col) {
  int i, j, sum = 0;
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++)
      if (matrix[i * col + j] % 2 == 0)
        sum += matrix[i * col + j];
  return sum;
}

static int sum_odd(int matrix[], int row, int col) {
  int i, j, sum = 0;
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++)
      if (matrix[i * col + j] % 2 != 0)
        sum += matrix[i * col + j];
  return sum;
}

static int diag_main_min(int matrix[], int row, int col) {
  int i, min = matrix[0];
  for (i = 0; i < row && i < col; i++)
    if (matrix[i * col + i] < min)
      min = matrix[i * col + i];
  return min;
}

static int diag_main_max(int matrix[], int row, int col) {
  int i, max = matrix[0];
  for (i = 0; i < row && i < col; i++)
    if (matrix[i * col + i] > max)
      max = matrix[i * col + i];
  return max;
}

static int diag_sub_min(int matrix[], int row, int col) {
  int i, min = matrix[col - 1];
  for (i = 0; i < row && i < col; i++)
    if (matrix[i * col + (col - 1 - i)] < min)
      min = matrix[i * col + (col - 1 - i)];
  return min;
}

static int diag_sub_max(int matrix[], int row, int col) {
  int i, max = matrix[col - 1];
  for (i = 0; i < row && i < col; i++)
    if (matrix[i * col + (col - 1 - i)] > max)
      max = matrix[i * col + (col - 1 - i)];
  return max;
}

static void print_matrix(int matrix[], int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printk(KERN_INFO "matrix[%d][%d] = %d\n", i, j, matrix[i * col + j]);
    }
  }
}

static int __init m_init(void) {
  printk(KERN_INFO "Matrix Module Loaded\n");

  print_matrix(matrix, row, col);

  printk(KERN_INFO "Sum of matrix = %d\n", sum_matrix(matrix, row, col));
  printk(KERN_INFO "Positive elements = %d\n", count_pos(matrix, row, col));
  printk(KERN_INFO "Negative elements = %d\n", count_neg(matrix, row, col));
  printk(KERN_INFO "Sum of even numbers = %d\n", sum_even(matrix, row, col));
  printk(KERN_INFO "Sum of odd numbers = %d\n", sum_odd(matrix, row, col));
  printk(KERN_INFO "Main Diagonal: Min = %d, Max = %d\n",
         diag_main_min(matrix, row, col), diag_main_max(matrix, row, col));
  printk(KERN_INFO "Sub Diagonal: Min = %d, Max = %d\n",
         diag_sub_min(matrix, row, col), diag_sub_max(matrix, row, col));

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
