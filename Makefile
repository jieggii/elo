SRC_DIR := ./src
INC_DIR := ./include
LIB_DIR := ./lib
TEST_DIR := ./test

.PHONY: help
help:
	@echo "hello there!"

.PHONY: fmt
fmt:
	@find $(SRC_DIR) $(INC_DIR) $(LIB_DIR) $(TEST_DIR) -type f \( -name '*.cpp' -o -name '*.h' \) | while read file; do \
		echo "Format $$file"; \
		clang-format -style=file -i $$file; \
	done
	@echo "Done!"

.PHONY: build-debug
build-debug:
	@echo "Building debug release..."
	pio run -e debug -t size

.PHONY: run-debug
run-debug:
	@echo "Building debug release and uploading to the board..."
	pio run -e debug -t upload

	@echo "Starting serial monitor..."
	pio device monitor

.PHONY: test-native
test-native:
	@echo "Running native tests..."
	pio test -e test-native

.PHONY: test
test: test-native