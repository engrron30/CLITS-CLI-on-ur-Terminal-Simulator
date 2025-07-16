SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
APP ?= $(TOPDIR)/nokia_olt_sim
INC := $(TOPDIR)/Include

CFLAGS := -I$(INC)


all: $(APP)

$(APP):
	gcc $(CFLAGS) $(SRC) -o $(APP)

clean:
	rm -f $(OBJ) $(APP)
