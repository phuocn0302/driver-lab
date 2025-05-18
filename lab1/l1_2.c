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

static int avg_arr(int arr[], int size) {
  int sum = 0;

  int i = 0;
  for (; i < size; i++) {
    sum += arr[i];
  }

  return sum / size;
}

static int max_arr(int arr[], int size) {
  int max = arr[0];

  int i = 0;
  for (; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  return max;
}

static int min_arr(int arr[], int size) {
  int min = arr[0];

  int i = 0;
  for (; i < size; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }

  return min;
}

static void print_arr(int arr[], int size) {
  int i = 0;
  for (; i < size; i++) {
    printk(KERN_INFO "Arr[%d] = %d\n", i, arr[i]);
  }
}

static int __init m_init(void) {
  print_arr(arr, n);
  printk(KERN_INFO "Min of arr = %d\n", min_arr(arr, n));
  printk(KERN_INFO "Max of arr = %d\n", max_arr(arr, n));
  printk(KERN_INFO "Average of arr = %d\n", avg_arr(arr, n));

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
