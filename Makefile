CC = gcc               # Compiler
CFLAGS = -Wall          # Compilation flags (show warnings)
TARGET = testing.c     # Output program name

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o $(TARGET)
