#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_VERSION("1.0");

static int decimal = 0;
static char hex[20] = "";
static char binary[65] = "";
static char octal[22] = "";

module_param(decimal, int, 0);
module_param_string(hex, hex, sizeof(hex), 0);
module_param_string(binary, binary, sizeof(binary), 0);
module_param_string(octal, octal, sizeof(octal), 0);

static void strrev(char *str) {
  int i, j;
  char temp;
  int len = strlen(str);
  for (i = 0, j = len - 1; i < j; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

static int dec_to_bin(int num, char *buf) {
  int i = 0;

  if (num == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return i;
  }

  while (num > 0) {
    buf[i++] = (num % 2) + '0';
    num /= 2;
  }

  buf[i] = '\0';
  strrev(buf);
  return i;
}

static int dec_to_hex(int num, char *buf) {
  static char hex_chars[] = "0123456789ABCDEF";
  int i = 0;

  if (num == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return i;
  }

  while (num > 0) {
    buf[i++] = hex_chars[num % 16];
    num /= 16;
  }

  buf[i] = '\0';
  strrev(buf);
  return i;
}

static int hex_to_dec(const char *hex) {
  int result = 0;
  int i = 0;
  char c;
  while ((c = hex[i++]) != '\0') {
    result *= 16;
    if (c >= '0' && c <= '9')
      result += c - '0';
    else if (c >= 'a' && c <= 'f')
      result += c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      result += c - 'A' + 10;
    else
      return -1; // invalid char
  }

  return result;
}

static int bin_to_dec(const char *bin) {
  int result = 0;
  int i = 0;
  char c;
  while ((c = bin[i++]) != '\0') {
    result <<= 1;
    if (c == '1')
      result += 1;
    else if (c != '0')
      return -1; // invalid char
  }

  return result;
}

static int dec_to_oct(int num, char *buf) {
  int i = 0;

  if (num == 0) {
    buf[i++] = '0';
    buf[i] = '\0';
    return i;
  }

  while (num > 0) {
    buf[i++] = (num % 8) + '0';
    num /= 8;
  }

  buf[i] = '\0';
  strrev(buf);
  return i;
}

static int oct_to_dec(const char *oct) {
  int result = 0;
  int i = 0;
  char c;
  while ((c = oct[i++]) != '\0') {
    if (c < '0' || c > '7')
      return -1; // invalid char
    result = result * 8 + (c - '0');
  }

  return result;
}

static int __init m_init(void) {
  char buf[100];
  int ret;

  ret = hex_to_dec(hex);
  printk(KERN_INFO "Hex %s to Decimal: %d\n", hex, ret);

  ret = bin_to_dec(binary);
  printk(KERN_INFO "Binary %s to Decimal: %d\n", binary, ret);

  ret = dec_to_oct(bin_to_dec(binary), buf);
  printk(KERN_INFO "Binary %s to Octal: %s\n", binary, buf);

  ret = oct_to_dec(octal);
  printk(KERN_INFO "Octal %s to Decimal: %d\n", octal, ret);

  ret = dec_to_hex(oct_to_dec(octal), buf);
  printk(KERN_INFO "Octal %s to Hex: %s\n", octal, buf);

  ret = dec_to_bin(decimal, buf);
  printk(KERN_INFO "Decimal %d to Binary: %s\n", decimal, buf);

  ret = dec_to_hex(decimal, buf);
  printk(KERN_INFO "Decimal %d to Hex: %s\n", decimal, buf);

  ret = dec_to_bin(hex_to_dec(hex), buf);
  printk(KERN_INFO "Hex %s to bin: %s\n", hex, buf);

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "Module Exited\n"); }

module_init(m_init);
module_exit(m_exit);
