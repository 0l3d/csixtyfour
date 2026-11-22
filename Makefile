CC      = cc
SOURCES = csixtyfour.c
OBJECTS = $(SOURCES:.c=.o)
TARGET  = csixtyfour

# TEST
TEST_FILE = test.bin
TEST_SRC = test.s
TEST_OBJ = test.o

CFLAGS  = -g
LDFLAGS = 

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
	
ctest:
	ca65 -g $(TEST_SRC)
	ld65 -C none.cfg $(TEST_OBJ) -o $(TEST_FILE)
	
run: all ctest
	./$(TARGET) $(TEST_FILE)
	

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_FILE) $(TEST_OBJ)

