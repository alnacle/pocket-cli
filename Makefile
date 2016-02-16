CC=cc 

CFLAGS += -std=c99 -pedantic -Wall -Os
CFLAGS += $(shell pkg-config --cflags libcurl)
CFLAGS += $(shell pkg-config --cflags json-c)

LDFLAGS += $(shell pkg-config --libs libcurl)
LDFLAGS += $(shell pkg-config --libs json-c)

OBJECTS = pocket.o utils.o string.o 
TARGETS = pocket-cli pocket-auth 

all: $(TARGETS)

pocket-cli: $(OBJECTS) pocket-cli.o
	$(CC) $^ -o $@ $(LDFLAGS)

pocket-auth: $(OBJECTS) pocket-auth.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o $(TARGETS)

