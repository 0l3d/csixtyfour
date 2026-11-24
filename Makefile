CC      = cc
SOURCES = csixtyfour.c
OBJECTS = $(SOURCES:.c=.o)
TARGET  = csixtyfour

TEST_FILE = test.bin
TEST_SRC  = test.s
TEST_OBJ  = test.o

CFLAGS  = -g
LDFLAGS =

.PHONY: all clean run ctest

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

ctest:
	ca65 -g $(TEST_SRC) -o $(TEST_OBJ)
	ld65 -C test.cfg $(TEST_OBJ) -o $(TEST_FILE)

run: all ctest
	./$(TARGET) $(TEST_FILE)

clean:
	rm -f $(OBJECTS) $(TARGET) $(TEST_FILE) $(TEST_OBJ)
