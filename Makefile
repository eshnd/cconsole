SRC = src/main.c
END = cconsole

COMP = gcc
FLAGS = -lreadline -lncurses

all: $(END)

$(END): $(SRC)
	$(COMP) $(SRC) -o $(END) $(FLAGS)

clean:
	rm $(END)

.PHONY: all clean
