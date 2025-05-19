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
  int i, len = strlen(XauRo);
  int shift = 0;

  if (kstrtoint(K, 10, &shift) != 0) {
    printk(KERN_ERR "Invalid Caesar key\n");
    return;
  }

  for (i = 0; i < len; i++) {
    if (XauRo[i] >= 'A' && XauRo[i] <= 'Z') {
      XauMa[i] = ((XauRo[i] - 'A' + shift) % 26) + 'A';
    } else {
      XauMa[i] = XauRo[i];  // leave non-uppercase letters unchanged
    }
  }
  XauMa[len] = '\0';

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
