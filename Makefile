# Makefile for the "CDbBirthday" project

# Compiler.
CC := gcc

# Folder paths.
INC_PATH := ./include
SRC_PATH := ./src

#Flags.
CFLAGS=-I$(INC_PATH)

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



all: final

# Compiling .o files:

$(OBJ_PATH)/auxfunc.o: $(SRC_PATH)/auxfunc.c
	@echo "Compiling auxiliary functions object file."
	@$(CC) $(CFLAGS) -c $(SRC_PATH)/auxfunc.c -o $(OBJ_PATH)/auxfunc.o

$(OBJ_PATH)/dbop.o: $(SRC_PATH)/dbop.c
	@echo "Compiling database operations object file."
	@$(CC) $(CFLAGS) -c $(SRC_PATH)/dbop.c -o $(OBJ_PATH)/dbop.o

$(OBJ_PATH)/dbsetup.o: $(SRC_PATH)/dbsetup.c
	@echo "Compiling database setup object file."
	@$(CC) $(CFLAGS) -c $(SRC_PATH)/dbsetup.c -o $(OBJ_PATH)/dbsetup.o

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.c
	@echo "Compiling main object file."
	@$(CC) $(CFLAGS) -c $(SRC_PATH)/main.c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/menu.o: $(SRC_PATH)/menu.c
	@echo "Compiling menu object file."
	@$(CC) $(CFLAGS) -c $(SRC_PATH)/menu.c -o $(OBJ_PATH)/menu.o

$(OBJ_PATH)/sqlite3.o: $(SRC_PATH)/sqlite3.c
	@echo "Compiling sqlite object file."
	@$(CC) $(CFLAGS) -c $(SRC_PATH)/sqlite3.c -o $(OBJ_PATH)/sqlite3.o

# Linking:

final: $(OBJ_PATH)/auxfunc.o $(OBJ_PATH)/dbop.o $(OBJ_PATH)/dbsetup.o $(OBJ_PATH)/main.o $(OBJ_PATH)/menu.o $(OBJ_PATH)/sqlite3.o
	@echo "Checking prerequisite files."
	@echo "Linking and producing executable."
	@$(CC) $(CFLAGS) $(OBJ_PATH)/auxfunc.o $(OBJ_PATH)/dbop.o $(OBJ_PATH)/dbsetup.o $(OBJ_PATH)/main.o $(OBJ_PATH)/menu.o $(OBJ_PATH)/sqlite3.o -o $(OUT_FILE)

# Clean:

clean: 
	@echo "Removing object files."
	@rm $(OBJ_PATH)/*
