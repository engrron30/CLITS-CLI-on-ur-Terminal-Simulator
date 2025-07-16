SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
APP ?= $(TOPDIR)/nokia_olt_sim

all: $(APP)

$(APP):
	gcc $(SRC) -o $(APP)

clean:
	rm -f $(OBJ) $(APP)
