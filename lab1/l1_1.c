#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_VERSION("1.0");

static int n;
static int arr[1000];

module_param(n, int, 0);
module_param_array(arr, int, &n, 0);

static int num1 = 0;
static int num2 = 0;
module_param(num1, int, 0);
module_param(num2, int, 0);

static int sum_array(int arr[], int size) {
  int sum = 0;

  int i = 0;
  for (; i < size; i++) {
    sum += arr[i];
  }

  return sum;
}

static int gcd(int a, int b) {
  if (a == 0 || b == 0) {
    return a + b;
  }

  int min = (a < b) ? a : b;

  int i = min;
  for (; i >= 1; i--) {
    if (a % i == 0 && b % i == 0) {
      return i;
    }
  }

  return 1;
}

static void print_arr(int arr[], int size) {
  int i = 0;
  for (; i < size; i++) {
    printk(KERN_INFO "Arr[%d] = %d\n", i, arr[i]);
  }
}

static int __init m_init(void) {
  print_arr(arr, n);
  printk(KERN_INFO "Sum of array = %d\n", sum_array(arr, n));
  printk(KERN_INFO "GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
