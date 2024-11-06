SRC_DIR=./src
BUILD_DIR=./build

all:
	mkdir -p $(BUILD_DIR)
	gcc $(SRC_DIR)/cmount.c -o $(BUILD_DIR)/cmount
	gcc $(SRC_DIR)/ucmount.c -o $(BUILD_DIR)/ucmount

cmount:
	mkdir -p $(BUILD_DIR)
	gcc $(SRC_DIR)/cmount.c -o $(BUILD_DIR)/cmount

ucmount:
	mkdir -p $(BUILD_DIR)
	gcc $(SRC_DIR)/ucmount.c -o $(BUILD_DIR)/ucmount
