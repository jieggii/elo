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

.PHONY: run-debug
run-debug:
	pio run -e debug -t upload && pio device monitor

.PHONY: test-native
test-native:
	@echo "Running native tests..."
	pio test -e test-native

.PHONY: test
test: test-native