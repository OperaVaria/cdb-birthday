# Makefile for the "CDbBirthday" project

# Compiler variables.
CC := gcc
CFLAGS=-I$(INC_DIR)

# OS dependent variables:
ifeq ($(OS),Windows_NT)
	OBJ_PATH := ./obj/win
    OUT_FILE := cdb_birthday.exe	
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
		OBJ_PATH := ./obj/lnx
        OUT_FILE := cdb_birthday
    endif
    ifeq ($(UNAME_S),Darwin)
		OBJ_PATH := ./obj/mac
        OUT_FILE := cdb_birthday
    endif
endif

# Path variables.
INC_DIR := ./include
SRC_DIR := ./src
OFILES := $(OBJ_PATH)/auxfunc.o $(OBJ_PATH)/date.o $(OBJ_PATH)/dbop.o $(OBJ_PATH)/dbsetup.o $(OBJ_PATH)/main.o $(OBJ_PATH)/menu.o $(OBJ_PATH)/sqlite3.o

# Make all.
all: final

# Compiling .o files with messages:

$(OBJ_PATH)/auxfunc.o: $(SRC_DIR)/auxfunc.c
	$(info Compiling auxiliary functions object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/auxfunc.c -o $(OBJ_PATH)/auxfunc.o

$(OBJ_PATH)/date.o: $(SRC_DIR)/date.c
	$(info Compiling date validation object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/date.c -o $(OBJ_PATH)/date.o

$(OBJ_PATH)/dbop.o: $(SRC_DIR)/dbop.c
	$(info Compiling database operations object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/dbop.c -o $(OBJ_PATH)/dbop.o

$(OBJ_PATH)/dbsetup.o: $(SRC_DIR)/dbsetup.c
	$(info Compiling database setup object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/dbsetup.c -o $(OBJ_PATH)/dbsetup.o

$(OBJ_PATH)/main.o: $(SRC_DIR)/main.c
	$(info Compiling main function object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/menu.o: $(SRC_DIR)/menu.c
	$(info Compiling menu object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/menu.c -o $(OBJ_PATH)/menu.o

$(OBJ_PATH)/sqlite3.o: $(SRC_DIR)/sqlite3.c
	$(info Compiling sqlite object file.)
	@$(CC) $(CFLAGS) -c $(SRC_DIR)/sqlite3.c -o $(OBJ_PATH)/sqlite3.o

# Final linking:

final: $(OFILES)
	$(info Linking and producing executable.)
	@$(CC) $(CFLAGS) $(OFILES) -o $(OUT_FILE)

# Clean:

clean: 
	$(info Removing object files.)
	@$(RM) $(OBJ_PATH)/*.o

bincl:	
	$(info Removing binary.)
	@$(RM) $(OUT_FILE)

allcl: clean bincl
