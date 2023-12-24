CUR_DIR := .
OBJ_DIR := $(CUR_DIR)/Obj
BIN_DIR :=$(CUR_DIR)/Bin

all:
	gcc -c -o $(OBJ_DIR)/BT_Buoi2.o $(CUR_DIR)/main.c
	gcc -o $(BIN_DIR)/BT_Buoi2 $(OBJ_DIR)/BT_Buoi2.o

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(BIN_DIR)/*

.PHONY: clean
