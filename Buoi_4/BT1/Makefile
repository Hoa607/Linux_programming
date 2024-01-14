.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra 
TARGET = myprogram

CUR_DIR := .
OBJ_DIR := $(CUR_DIR)/obj

OBJS = $(OBJ_DIR)/%.o

all: $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)/$(TARGET).o $(CUR_DIR)/main.c
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_DIR)/$(TARGET).o

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -f $(TARGET)
