CC      = gcc
CFLAGS  = -Wall -Wextra -Iinclude
SRC     = $(wildcard src/*.c)
TARGET  = build/vm

$(TARGET): $(SRC) $(wildcard include/*.h)
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build

.PHONY: run clean
