print-%  : ; @echo $* = $($*)

#region: build filter

SOURCE_DIR 	=./sources
INCLUDE_DIR 	=./include
BUILD_DIR 	=./build

CC 		=gcc

CFLAGS 		=-c -Wall -I$(INCLUDE_DIR)
LINKING_C_FLAGS =-Xlinker -Map=$(BUILD_DIR)/filter.map


SOURCES 	=$(wildcard $(SOURCE_DIR)/*.c)
OBJECTS 	=$(patsubst $(SOURCE_DIR)/%.c, 	$(BUILD_DIR)/%.o, 	$(SOURCES))

EXECUTABLE 	=filter.exe

all: dir $(BUILD_DIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LINKING_C_FLAGS)

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)

#endregion: build filter


#region: perform tests // testing framework

TEST_DIR 			=./tests
TEST_INPUT_FILES 		=$(wildcard $(TEST_DIR)/*.c)
TEST_EXPECTED_RESULT_FILES 	=$(patsubst $(TEST_DIR)/%.c, 	$(TEST_DIR)/%.expected_result, 	$(TEST_INPUT_FILES))
TEST_ACTUAL_RESULT_FILES 	=$(patsubst $(TEST_DIR)/%.c, 	$(BUILD_DIR)/%.result, 		$(TEST_INPUT_FILES))
TEST_COMPARSION_RESULT_FILES 	=$(patsubst $(TEST_DIR)/%.c, 	$(BUILD_DIR)/%.diff, 		$(TEST_INPUT_FILES))

TEST_COMPARSION_RESULT_MERGED 	=$(BUILD_DIR)/test.merged_diff

test: all clean_test $(TEST_COMPARSION_RESULT_MERGED)
	printf "\ntesting results:\n\n"
	cat $(TEST_COMPARSION_RESULT_MERGED)
	mv -f $(EXECUTABLE).stackdump $(BUILD_DIR)/$(EXECUTABLE).stackdump 2> /dev/null || true

$(TEST_COMPARSION_RESULT_MERGED): $(TEST_COMPARSION_RESULT_FILES)
	tail -n +1 $(BUILD_DIR)/*.diff > $(TEST_COMPARSION_RESULT_MERGED)

$(TEST_COMPARSION_RESULT_FILES): $(BUILD_DIR)/%.diff: $(TEST_DIR)/%.expected_result $(BUILD_DIR)/%.result
	diff --strip-trailing-cr $(word 1,$^) $(word 2,$^) > $@ || true

$(TEST_ACTUAL_RESULT_FILES): $(BUILD_DIR)/%.result: $(TEST_DIR)/%.c
	cat $< | $(BUILD_DIR)/$(EXECUTABLE) > $@ || true

clean_test:
	rm -f $(TEST_ACTUAL_RESULT_FILES) $(TEST_COMPARSION_RESULT_FILES)

#endregion: perform tests // testing framework

clean:
	rm -rf $(BUILD_DIR)

