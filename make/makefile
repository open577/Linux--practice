BIN=proc.exe
CC=gcc
#SRC=$(shell ls *.c)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
LFLAGS=-o
FLAGS=-c
RM=rm -f

$(BIN):$(OBJ)
	@$(CC) $(LFLAGS) $@ $^
	@echo "linking ... $^ to $@"

%.o:%.c
	@$(CC) $(FLAGS) $<
	@echo "compiling ... $< to $@"

.PHONY:clean
clean:
	$(RM) $(OBJ) $(BIN)

.PHONY:test
test:
	@echo $(SRC)
	@echo $(OBJ)
