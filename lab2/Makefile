BUILD_DIR := build
SRC_FILES := $(wildcard *.c)
MOD_NAME? := l2_1

obj-m += $(MOD_NAME).o

all:
	mkdir -p $(BUILD_DIR)
	cp -f $(SRC_FILES) Makefile $(BUILD_DIR)/
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD)/$(BUILD_DIR) modules
	cp -f $(BUILD_DIR)/*.ko ./

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD)/$(BUILD_DIR) clean
	rm -f *.ko *.o *.mod.* *.cmd .*.cmd modules.order Module.symvers
	rm -rf .tmp_versions
	rm -rf $(BUILD_DIR)

.PHONY: all clean
