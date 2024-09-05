SRC_DIR := ./src
INC_DIR := ./include
LIB_DIR := ./lib
TEST_DIR := ./test

# Gather all files with the specified extensions in all defined directories
FORMAT_FILES := $(shell find $(SRC_DIR) $(INC_DIR) $(LIB_DIR) $(TEST_DIR) -type f \( -name '*.cpp' -o -name '*.h' \))

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