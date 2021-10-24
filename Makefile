CC = gcc
TARGET = seed lea

all: $(TARGET)

T: T.c
	$(CC) -o $@ $^ -g

clean:
	rm $(TARGET)

# EOF
