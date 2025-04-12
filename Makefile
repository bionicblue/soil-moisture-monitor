.PHONY: format lint build test

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDE_DIR = include

format:
	clang-format -i $(SRCS) $(wildcard $(INCLUDE_DIR)/*.h) $(TEST_SRCS)

lint:
	platformio check -e esp32dev

build:
	platformio run -e esp32dev

