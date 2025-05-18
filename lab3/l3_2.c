#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_VERSION("1.0");

static char XauRo[100] = "HELLO";
static char XauMa[100];
static char K[100];

module_param_string(XauRo, XauRo, sizeof(XauRo), 0);
module_param_string(K, K, sizeof(K), 0);

static void ma_hoa_chuyen_vi(void) {
  int len = strlen(XauRo);
  int klen = strlen(K);
  int rows;
  int cols;
  int i, j;
  int key;

  if (klen <= 0 || klen > len) {
    printk(KERN_ERR "Invalid key: must be >0 and <= length of data\n");
    return;
  }

  key = 0;
  for (i = 0; i < klen; i++) {
    if (K[i] < '0' || K[i] > '9') {
      printk(KERN_ERR "Key must be numeric\n");
      return;
    }
    key = key * 10 + (K[i] - '0');
  }

  if (key <= 0) {
    printk(KERN_ERR "Invalid key number\n");
    return;
  }

  rows = key;
  cols = (len + rows - 1) / rows;

  char matrix[rows][cols];
  int idx = 0;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      if (idx < len)
        matrix[i][j] = XauRo[idx++];
      else
        matrix[i][j] = ' '; // padding
    }
  }

  idx = 0;
  for (j = 0; j < cols; j++) {
    for (i = 0; i < rows; i++) {
      XauMa[idx++] = matrix[i][j];
    }
  }
  XauMa[idx] = '\0';

  printk(KERN_INFO "Ma hoa chuyen vi: %s\n", XauMa);
}

static void ma_hoa_thay_the(void) {
  int i, len = strlen(XauRo);
  int klen = strlen(K);

  if (klen < 26) {
    printk(KERN_ERR "Key must be 26 char len\n");
    return;
  }

  for (i = 0; i < len; i++) {
    if (XauRo[i] >= 'A' && XauRo[i] <= 'Z') {
      XauMa[i] = K[XauRo[i] - 'A'];
    } else {
      XauMa[i] = XauRo[i]; // ko thay doi ky tu ngoai A - Z
    }
  }
  XauMa[len] = '\0';

  printk(KERN_INFO "Ma hoa thay the: %s\n", XauMa);
}

static void ma_hoa_hoan_vi_toan_cuc(void) {
  int len = strlen(XauRo);
  int i;
  int used[100] = {0};

  for (i = 0; i < len; i++) {
    int pos = K[i] - '0';
    if (pos < 0 || pos >= len || used[pos]) {
      printk(KERN_ERR "Invalid key\n");
      return;
    }
    XauMa[pos] = XauRo[i];
    used[pos] = 1;
  }
  XauMa[len] = '\0';

  printk(KERN_INFO "Ma hoan vi toan cuc: %s\n", XauMa);
}

static int __init m_init(void) {
  printk(KERN_INFO "Xau ro: %s\n", XauRo);

  ma_hoa_chuyen_vi();
  ma_hoa_thay_the();
  ma_hoa_hoan_vi_toan_cuc();

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
