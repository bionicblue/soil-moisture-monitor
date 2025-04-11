# Phony targets
.PHONY: all clean run tests run-tests lint format

# Compiler and flags
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
TESTS_DIR = tests

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Test files and test executables
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_BINS = $(patsubst $(TESTS_DIR)/%.cpp, $(BUILD_DIR)/%, $(TEST_SRCS))

# Add Google Test paths
GTEST_DIR = /opt/homebrew/opt/googletest
GTEST_LIB = $(GTEST_DIR)/lib
GTEST_INCLUDE = $(GTEST_DIR)/include

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build all test executables
tests: $(BUILD_DIR) $(TEST_BINS)

# Build each test executable
$(BUILD_DIR)/%: $(TESTS_DIR)/%.cpp $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -I$(GTEST_INCLUDE) $^ -o $@ -L$(GTEST_LIB) -lgtest -lgtest_main -pthread

# Run all tests
run-tests: tests
	@for test in $(TEST_BINS); do \
		echo "Running $$test..."; \
			$$test || exit 1; \
	done

# Lint the source and header files
lint:
	pio check --environment esp32dev

# Format the source and header files
format:
	clang-format -i $(SRCS) $(wildcard $(INCLUDE_DIR)/*.h) $(TEST_SRCS)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
