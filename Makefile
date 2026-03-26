CC  = gcc
SRC = $(wildcard src/*.c)
OUT = program

CFLAGS = -O2
LIBS   = -lraylib -lm

all:
	$(CC) $(SRC) -o	$(OUT) $(CFLAGS) $(LIBS)

clean:
	rm -f $(OUT)
