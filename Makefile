CC=gcc
W=-Wall -Wextra -Wpedantic -Wno-unused-result
CFLAGS=-O2 -march=native -s -fno-stack-protector -fno-plt -no-pie -pipe -o
TARGET=gentoofetch
static:
	$(CC) $(W) -static $(CFLAGS) $(TARGET) $(TARGET).c
	strip -s $(TARGET)
edit:
	$(EDITOR) $(TARGET).c
install:
	mv gentoofetch /usr/bin/
uninstall:
	rm /usr/bin/gentoofetch
clean:
	rm gentoofetch
