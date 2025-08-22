PROJECT_NAME = libyou
MODULES = huffman trees

CXX = g++
DEBUGGER = gdb
MEMCHECK = valgrind --fair-sched=try --leak-check=full

CFLAGS = -O2 -Wall -Werror -std=c++17
TFLAGS = -O0 -g3 -Wall -std=c++17 -DLY_DEBUG

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = target
TEST_DIR = tests
OBJ_DIR = $(BUILD_DIR)/obj
TEST_BUILD_DIR = $(BUILD_DIR)/tests

# Recursive wildcard search
rwildcard = $(wildcard $1$2) \
	    $(foreach dir, \
	    	$(wildcard $1*), \
	    	$(call rwildcard,$(dir)/,$2))


# Module shared object build rules
# ---------------------------------------------------------------------------
define module_build_rules

LIB_$1 = $$(BUILD_DIR)/lib$1

INCLUDE_DIR_$1 = $1/$$(INCLUDE_DIR)/
SRC_DIR_$1 = $1/$$(SRC_DIR)
OBJ_DIR_$1 = $$(OBJ_DIR)/$1
TEST_DIR_$1 = $1/$$(TEST_DIR)

SRCS_$1 = $$(call rwildcard,$$(SRC_DIR_$1)/,*.cpp)

OBJS_$1 = $$(patsubst $$(SRC_DIR_$1)/%.cpp, \
	$$(OBJ_DIR_$1)/%.o, \
	$$(SRCS_$1))

DEBUG_OBJS_$1 = $$(patsubst $$(SRC_DIR_$1)/%.cpp, \
	$$(OBJ_DIR_$1)/%.debug.o, \
	$$(SRCS_$1))

TEST_BUILD_DIR_$1 = $$(TEST_BUILD_DIR)/$1

# Pattern rules for source files
$$(OBJ_DIR_$1)/%.o: $$(SRC_DIR_$1)/%.cpp | $$(OBJ_DIR_$1)/%.d
	$$(CXX) -fPIC -c $$(CFLAGS) -I$$(INCLUDE_DIR_$1) $$< -o $$@

$$(OBJ_DIR_$1)/%.debug.o: $$(SRC_DIR_$1)/%.cpp | $$(OBJ_DIR_$1)/%.d
	$$(CXX) -fPIC -c $$(TFLAGS) -I$$(INCLUDE_DIR_$1) $$< -o $$@

$$(LIB_$1).so: $$(OBJS_$1) | $$(BUILD_DIR)
	$$(CXX) -fPIC -shared $$(CFLAGS) -I$$(INCLUDE_DIR_$1) $$^ -o $$@

$$(LIB_$1)-debug.so: $$(DEBUG_OBJS_$1) | $$(BUILD_DIR)
	$$(CXX) -fPIC -shared $$(TFLAGS) -I$$(INCLUDE_DIR_$1) $$^ -o $$@

# Pattern rules for integration tests
$$(TEST_BUILD_DIR_$1)/%: $$(TEST_DIR_$1)/%.cpp $$(LIB_$1)-debug.so \
	| $$(TEST_BUILD_DIR_$1)/%.d
	$$(CXX) $$(TFLAGS) -I$$(INCLUDE_DIR_$1) $$^ -o $$@

build/$1: $$(LIB_$1).so
	@echo $$<

build/$1/debug: $$(LIB_$1)-debug.so
	@echo $$<

build/$1/tests/%: $$(TEST_BUILD_DIR_$1)/%
	@echo $$<

run/$1/tests/%: $$(TEST_BUILD_DIR_$1)/%
	$$<

debug/$1/tests/%: $$(TEST_BUILD_DIR_$1)/%
	$$(DEBUGGER) $$<

memcheck/$1/tests/%: $$(TEST_BUILD_DIR_$1)/%
	$$(MEMCHECK) $$<

.PHONY += build/$1 build/$1/debug

endef

$(foreach module, \
	$(MODULES), \
	$(eval $(call module_build_rules,$(module))))
# ===========================================================================

build/all: $(foreach module,$(MODULES),build/$(module))
	@echo $^

build/all/debug: $(foreach module,$(MODULES),build/$(module)/debug)
	@echo $^

# Directory creation
.SECONDARY:
$(BUILD_DIR)/%.d:
	mkdir -p $(dir $@)
	touch $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY += clean compile_comands docs

docs: | $(BUILD_DIR)
	doxygen

clean:
	rm -rf $(BUILD_DIR)

compile_commands: clean
	bear -- make build/all/debug
