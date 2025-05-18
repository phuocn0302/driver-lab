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

static int gcd(int a, int b) {
  while (b != 0) {
    int tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

static int gcd_arr(int arr[], int size) {
  if (size == 0) return 0;

  int arr_gcd = arr[0];
  
  int i = 0;
  for (; i < size; i++) {
    arr_gcd = gcd(arr_gcd, arr[i]);
  }

  return arr_gcd;

}

static void print_arr(int arr[], int size) {
  int i = 0;
  for (; i < size; i++) {
    printk(KERN_INFO "Arr[%d] = %d\n", i, arr[i]);
  }
}

static int __init m_init(void) {
  print_arr(arr, n);
  printk(KERN_INFO "GCD or arr = %d\n", gcd_arr(arr, n));

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
