BIN_DIR=bin
INCLUDES_DIR=include
OBJ_DIR=obj
SRC_DIR=src

CC = gcc                    
CFLAGS = -Wall -ggdb -pedantic -std=c99


SRCS := $(wildcard src/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET: main
all: clean TARGET
build_run:  all run


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

main:  $(BIN_DIR) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@  $(OBJS)

run:
	@clear
	@$(BIN_DIR)/main


$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)


ifeq ($(OS),Windows_NT)
    RMDIR = rmdir /S /Q
else
    RMDIR = rm -rf
endif

clean:
	$(RMDIR) $(BIN_DIR)
	$(RMDIR) $(OBJ_DIR)

.PHONY: clean