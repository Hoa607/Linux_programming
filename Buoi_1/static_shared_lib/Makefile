SHARED_LIB_NAME := math
STATIC_LIB_NAME := math

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/obj
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

create_obj:
	gcc -c -fPIC $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o -I $(INC_DIR)
	gcc -c -fPIC $(SRC_DIR)/version.c -o $(OBJ_DIR)/version.o -I $(INC_DIR)

create_shared_lib:
	gcc -shared $(OBJ_DIR)/math.o $(OBJ_DIR)/version.o -o $(LIB_SHARED_DIR)/lib$(SHARED_LIB_NAME).so

create_static_lib:
	ar rcs $(LIB_STATIC_DIR)/lib$(STATIC_LIB_NAME).a $(OBJ_DIR)/math.o $(OBJ_DIR)/version.o

linking_shared_lib:
	gcc $(OBJ_DIR)/main.o -L $(LIB_SHARED_DIR) -l $(SHARED_LIB_NAME) -o $(BIN_DIR)/use-shared-library

linking_static_lib:
	gcc $(OBJ_DIR)/main.o -L $(LIB_STATIC_DIR) -l $(STATIC_LIB_NAME) -o $(BIN_DIR)/statically-linked

clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(LIB_STATIC_DIR)/*.a