#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_VERSION("1.0");

static int v1[100];
static int v2[100];
static int vsize = 2;

module_param(vsize, int, 0);
module_param_array(v1, int, NULL, 0);
module_param_array(v2, int, NULL, 0);

static int row1;
static int col1;
static int matrix1[10000];

module_param(row1, int, 0);
module_param(col1, int, 0);
module_param_array(matrix1, int, NULL, 0);

static int row2;
static int col2;
static int matrix2[10000];

module_param(row2, int, 0);
module_param(col2, int, 0);
module_param_array(matrix2, int, NULL, 0);

static int dot_product(int v1[], int v2[], int size) {
  int result = 0;
  int i;
  for (i = 0; i < size; i++)
    result += v1[i] * v2[i];
  return result;
}

static void matrix_add(int *m1, int *m2, int size, int *ret) {
  int i;
  for (i = 0; i < size; i++)
    ret[i] = m1[i] + m2[i];
}

static void matrix_sub(int *m1, int *m2, int size, int *ret) {
  int i;
  for (i = 0; i < size; i++)
    ret[i] = m1[i] - m2[i];
}

static void matrix_mul(int *m1, int *m2, int *ret, int r1, int c1, int c2) {
  int i, j, k;
  for (i = 0; i < r1; i++) {
    for (j = 0; j < c2; j++) {
      ret[i * c2 + j] = 0;
      for (k = 0; k < c1; k++) {
        ret[i * c2 + j] += m1[i * c1 + k] * m2[k * c2 + j];
      }
    }
  }
}

static void print_vector(int v[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printk(KERN_INFO "v[%d] = %d\n", i, v[i]);
  }
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
  int msize;

  printk(KERN_INFO "Vector 1:\n");
  print_vector(v1, vsize);

  printk(KERN_INFO "Vector 2:\n");
  print_vector(v2, vsize);

  printk(KERN_INFO "Dot product = %d\n", dot_product(v1, v2, vsize));

  printk(KERN_INFO "Matrix 1:\n");
  print_matrix(matrix1, row1, col1);

  printk(KERN_INFO "Matrix 2:\n");
  print_matrix(matrix2, row2, col2);

  if (row1 != row2 || col1 != col2) {
    printk(KERN_ERR
           "Matrix dimensions do not match for addition/subtraction\n");
  } else {
    msize = row1 * col1;

    int m_sum[1000];
    matrix_add(matrix1, matrix2, msize, m_sum);
    printk(KERN_INFO "Matrix Sum:\n");
    print_matrix(m_sum, row1, col1);

    int m_diff[1000];
    matrix_sub(matrix1, matrix2, msize, m_diff);
    printk(KERN_INFO "Matrix Difference:\n");
    print_matrix(m_diff, row1, col1);
  }

  if (col1 != row2) {
    printk(KERN_ERR "Matrix dimensions incompatible for multiplication\n");
  } else {
    msize = row1 * col1;

    int m_product[1000];
    matrix_mul(matrix1, matrix2, m_product, row1, col1, col2);
    printk(KERN_INFO "Matrix Product:\n");
    print_matrix(m_product, row1, col2);
  }

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
