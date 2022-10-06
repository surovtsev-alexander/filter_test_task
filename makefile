print-%  : ; @echo $* = $($*)

#region: build filter

CC 		=gcc

CFLAGS 		=-c -Wall -I$(INCLUDE_DIR)

SOURCE_DIR 	=./sources
INCLUDE_DIR 	=./include
BUILD_DIR 	=./build

SOURCES 	=$(wildcard $(SOURCE_DIR)/*.c)
OBJECTS 	=$(patsubst $(SOURCE_DIR)/%.c, 	$(BUILD_DIR)/%.o, 	$(SOURCES))

EXECUTABLE 	=filter.exe

all: dir $(BUILD_DIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS): $(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) -o $@ $< $(CFLAGS)

#endregion: build filer


#region: perform tests // testing framework

TEST_DIR 			=./tests
TEST_INPUT_FILES 		=$(wildcard $(TEST_DIR)/*.input)
TEST_EXPECTED_RESULT_FILES 	=$(patsubst $(TEST_DIR)/%.input, 	$(TEST_DIR)/%.expected_result, 	$(TEST_INPUT_FILES))
TEST_ACTUAL_RESULT_FILES 	=$(patsubst $(TEST_DIR)/%.input, 	$(BUILD_DIR)/%.result, 		$(TEST_INPUT_FILES))
TEST_COMPARSION_RESULT_FILES 	=$(patsubst $(TEST_DIR)/%.input, 	$(BUILD_DIR)/%.diff, 		$(TEST_INPUT_FILES))

TEST_COMPARSION_RESULT_MERGED 	=$(BUILD_DIR)/test.merged_diff

test: all clean_test $(TEST_COMPARSION_RESULT_MERGED)
	printf "\testing results:\n\n"
	cat $(TEST_COMPARSION_RESULT_MERGED)

$(TEST_COMPARSION_RESULT_FILES): $(BUILD_DIR)/%.diff: $(TEST_DIR)/%.expected_result $(BUILD_DIR)/%.result
	diff $(word 1,$^) $(word 2,$^) > $@ || true

$(TEST_ACTUAL_RESULT_FILES): $(BUILD_DIR)/%.result: $(TEST_DIR)/%.input
	cat $< | $(BUILD_DIR)/$(EXECUTABLE) > $@

$(TEST_COMPARSION_RESULT_MERGED): $(TEST_COMPARSION_RESULT_FILES)
	tail -n +1 $(BUILD_DIR)/*.diff > $(TEST_COMPARSION_RESULT_MERGED)

clean_test:
	rm -f $(TEST_ACTUAL_RESULT_FILES) $(TEST_COMPARSION_RESULT_FILES)

#endregion: perform tests // testing framework

clean:
	rm -rf $(BUILD_DIR)

