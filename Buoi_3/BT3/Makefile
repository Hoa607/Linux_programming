.PHONY: all clean create_lib_obj

SHARED_LIB_NAME := shared_lib
STATIC_LIB_NAME := static_lib

CC = gcc
CFLAGS = -Wall -Wextra
TARGET = myprogram

CUR_DIR := .
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
INC_LIB_DIR := $(LIB_DIR)/inc
SRC_LIB_DIR := $(LIB_DIR)/src
OBJS = $(OBJ_DIR)/%.o

all: $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/$(TARGET).o $(CUR_DIR)/main.c
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_DIR)/$(TARGET).o

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

create_lib_obj:
	gcc -c -fPIC $(SRC_LIB_DIR)/*.c -o $(OBJ_DIR)/lib.o -I $(INC_LIB_DIR)

create_shared_lib:
	gcc -shared $(OBJ_DIR)/lib.o -o $(OBJ_DIR)/lib$(SHARED_LIB_NAME).so

create_static_lib:
	ar rcs $(OBJ_DIR)/lib$(STATIC_LIB_NAME).a $(OBJ_DIR)/lib.o 

linking_shared_lib:
	gcc $(OBJ_DIR)/$(TARGET).o -L $(OBJ_DIR) -l $(SHARED_LIB_NAME) -o $(CUR_DIR)/use-shared-library

linking_static_lib:
	gcc $(OBJ_DIR)/$(TARGET).o -L $(OBJ_DIR) -l $(STATIC_LIB_NAME) -o $(CUR_DIR)/statically-linked

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(TARGET)
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(LIB_STATIC_DIR)/*.a
