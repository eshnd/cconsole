SRC = src/main.c
END = cshell

COMP = gcc
FLAGS = -lreadline -lncurses

all: $(END)

$(END): $(SRC)
	$(COMP) $(SRC) -o $(END) $(FLAGS)

clean:
	rm $(END)

.PHONY: all clean
