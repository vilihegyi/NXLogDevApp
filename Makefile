CC = gcc
CFLAGS = -Wall
LDLIBS = -lstdc++

all: app

app:
	mkdir -p build
	$(CC) $(CFLAGS) main.cpp json/JsonParser.cpp tlv/Tlv.cpp -o build/mainApp $(LDLIBS)

clean:
	rm -rf build
