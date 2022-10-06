CC 		=gcc

CFLAGS 		=-c -Wall -I$(INCLUDE_DIR)

SOURCE_DIR 	=./sources
INCLUDE_DIR 	=./include
BUILD_DIR 	=./build

SOURCES 	=$(wildcard $(SOURCE_DIR)/*.c)
OBJECTS 	=$(patsubst $(SOURCE_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

EXECUTABLE 	=filter.exe

all: dir $(BUILD_DIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)


clean:
	rm -rf $(BUILD_DIR)

print-%  : ; @echo $* = $($*)

