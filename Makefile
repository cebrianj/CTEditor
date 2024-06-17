BIN_DIR=bin

CC = gcc                    
CFLAGS = -Wall -ggdb -pedantic -std=c99

TARGET: main
all: clean TARGET
build_run:  all run


main:  src/main.c  $(BIN_DIR) 
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/$@

run:
	@clear
	@$(BIN_DIR)/main


$(BIN_DIR):
	mkdir $(BIN_DIR)



ifeq ($(OS),Windows_NT)
    RMDIR = rmdir /S /Q
else
    RMDIR = rm -rf
endif

clean:
	$(RMDIR) $(BIN_DIR)

.PHONY: clean