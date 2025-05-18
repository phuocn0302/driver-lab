#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
MODULE_DESCRIPTION("");
MODULE_VERSION("1.0");

static char str1[256] = "";
static char str2[256] = "";

module_param_string(str1, str1, sizeof(str1), 0);
module_param_string(str2, str2, sizeof(str2), 0);

static int count_chars(const char *s) {
  int count = 0;
  while (s[count] != '\0')
    count++;
  return count;
}

static void reverse_by_length(char *s, int len) {
  int i;
  char tmp;
  for (i = 0; i < len / 2; i++) {
    tmp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = tmp;
  }
}

static void reverse_by_null(char *s) {
  int len = 0;
  int i;
  char tmp;
  while (s[len] != '\0')
    len++;
  for (i = 0; i < len / 2; i++) {
    tmp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = tmp;
  }
}

static void normalize_string(char *s) {
  int i = 0, j = 0;
  int capitalize = 1;
  while (s[i] == ' ' || s[i] == '\t')
    i++;
  while (s[i] != '\0') {
    if (s[i] == ' ' || s[i] == '\t') {
      if (j > 0 && s[j - 1] != ' ')
        s[j++] = ' ';
      i++;
    } else {
      char c = s[i];
      if (c >= 'A' && c <= 'Z')
        c = c + 32;
      if (capitalize && c >= 'a' && c <= 'z') {
        s[j++] = c - 32;
        capitalize = 0;
      } else {
        s[j++] = c;
        if (c == '.' || c == '!' || c == '?')
          capitalize = 1;
      }
      i++;
    }
  }
  if (j > 0 && s[j - 1] == ' ')
    j--;
  s[j] = '\0';
}

static void concat_strings(char *dest, const char *src) {
  int i = 0, j = 0;
  while (dest[i] != '\0')
    i++;
  while (src[j] != '\0' && i < 255)
    dest[i++] = src[j++];
  dest[i] = '\0';
}

static int __init m_init(void) {
  char temp1[256], temp2[256], concat[512];

  int i;
  for (i = 0; i < 255 && str1[i] != '\0'; i++)
    temp1[i] = str1[i];

  temp1[i] = '\0';

  for (i = 0; i < 255 && str2[i] != '\0'; i++)
    temp2[i] = str2[i];

  temp2[i] = '\0';

  printk(KERN_INFO "Original str1: %s\n", temp1);
  printk(KERN_INFO "Original str2: %s\n", temp2);
  printk(KERN_INFO "Length of str1: %d\n", count_chars(temp1));

  normalize_string(temp1);
  normalize_string(temp2);
  printk(KERN_INFO "Normalized str1: %s\n", temp1);
  printk(KERN_INFO "Normalized str2: %s\n", temp2);

  reverse_by_length(temp1, count_chars(temp1));
  printk(KERN_INFO "Reversed str1 by length: %s\n", temp1);

  reverse_by_null(temp2);
  printk(KERN_INFO "Reversed str2 by null: %s\n", temp2);

  for (i = 0; i < 255 && temp1[i] != '\0'; i++)
    concat[i] = temp1[i];
  concat[i] = '\0';
  concat_strings(concat, " ");
  concat_strings(concat, temp2);
  printk(KERN_INFO "Concatenated: %s\n", concat);

  return 0;
}

static void __exit m_exit(void) { printk(KERN_INFO "String Module Exited.\n"); }

module_init(m_init);
module_exit(m_exit);
