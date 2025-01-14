CC = gcc
CFLAGS = -Wall -g

SRC = myFunctionsShell.c myShell.c
HDR = myFunctionsShell.h myShell.h

TARGET = myShell


all: $(TARGET)


$(TARGET): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
