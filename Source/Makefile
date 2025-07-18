SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)
APP ?= $(TOPDIR)/nokia_olt_sim
INC := $(TOPDIR)/Include

CFLAGS := -I$(INC)


all: $(APP)

$(APP): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(APP)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(APP)
