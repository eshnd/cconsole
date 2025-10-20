SRC = src/main.c
END = cshell

COMP = gcc

all: $(END)

$(END): $(SRC)
	$(COMP) $(SRC) -o $(END)

clean:
	rm $(END)

.PHONY: all clean
