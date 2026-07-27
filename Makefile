CC      = cc
SOURCES = csixtyfour.c
OBJECTS = $(SOURCES:.c=.o)
TARGET  = csixtyfour

CFLAGS  = -g
LDFLAGS = 

.PHONY: all clean 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

