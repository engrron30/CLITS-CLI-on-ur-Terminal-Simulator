SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
APP := nokia_olt_sim

all: APP

APP:
	gcc $(SRC) -o $(OBJ)
