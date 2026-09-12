#very crappy

C := cc
CFLAGS := -Wall -Wextra -Werror -g -O0 -march=native

SRC := ./main.c
OUT := ./passmgr

all: $(SRC)
	$(C) $(CFLAGS) -o $(OUT) $(SRC)
clean: 
	rm -rf $(OUT)
run:
	$(OUT)
.PHONY: all clean run
