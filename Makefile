# # src/Makefile
#
# ## REQUIREMENTS
#
#   * gcc
#   * clang-format
#   * ccheck
#
# ## HOW TO USE
#
# make all    # builds all lib
# make test   # builds and runs all unittests
# make tests  # builds all unittests
#
# make lint   # runs linters on all sources: ccheck clang-format (in check mode)
# make format # (make fmt) formats all sources
#
# make clean  # removes all binaries
#
# 
# ## ADDITIONAL BUILD OPTIONS
#
# 1) DEBUG_MODE
#
# If you what to build something with debug info enabled, add BUILD_CONFIG=DEBUG environment variable:
#
# make BUILD_CONFIG=DEBUG all         # builds lib with debug info enabled
# make BUILD_CONFIG=DEBUG test        # builds tests and run them with debug info enabled
#
# 2) SANITIZE
#
# If you what to build with sanitizers, add SANITIZE=yes environment variable:
#
# make SANITIZE=yes all               # builds lib with address, leak and ub sanitizer
# make SANITIZE=yes test              # builds tests and run them with address, leak and ub sanitizer
# 
# 
# P.S. you can combine build options together, for example:
# 
# make SANITIZE=yes GTEST=FAILS test  # builds tests with UB sanitizer and run them showing only test failures

PHONY := \
	default all build \
	format fmt lint \
	test tests \
	gcov_report \
	clean

ALL   :=
CLEAN :=

RM      := rm -rf
SRCROOT := .

default: all

# ============== [ COMPILATION FLAGS ] ==============
#

CC      := gcc
CFLAGS  := -Wall -Wextra -pedantic -std=c11
LDFLAGS := -lncurses
AR      := ar
ARFLAGS := rcs

ifeq ($(BUILD_CONFIG), DEBUG)
    CFLAGS += -O0 -g -D CONFIG_DEBUG
else
    CFLAGS += -Werror -O2 -D CONFIG_RELEASE
endif

ifeq ($(SANITIZE), yes)
    CFLAGS += -fsanitize=address,leak,undefined
endif

ifeq ($(WITH_COVERAGE), yes)
    CFLAGS  += -fprofile-arcs
    CFLAGS  += -ftest-coverage
endif

# include $(SRCROOT)/make/os.mk
include $(SRCROOT)/make/tools.mk

# ================== [ STATIC LIB TARGET ] ===================
#

LIB_TARGET_NAME := backend
LIB_TARGET      := $(LIB_TARGET_NAME).a

BACKEND_DIR     := $(SRCROOT)/brick_game/tetris

LIB_SRC   := $(wildcard $(BACKEND_DIR)/*.c)
LIB_OBJS  := $(patsubst $(SRCROOT)/%.c, $(SRCROOT)/%.o, $(LIB_SRC))

$(LIB_TARGET): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^ $(LDFLAGS) 

$(BACKEND_DIR)/%.o: $(BACKEND_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

ALL   += $(LIB_TARGET)
CLEAN += $(LIB_OBJS) $(LIB_TARGET)

# ================== [ APP TARGET ] ===================
# 

BUILD_DIR    := build
STATIC_DIR   := static
FRONTEND_DIR := $(SRCROOT)/gui/cli

TARGET       := $(BUILD_DIR)/tetris

SRC   := $(wildcard $(FRONTEND_DIR)/*.c $(SRCROOT)/*.c)
OBJS  := $(patsubst $(SRCROOT)/%.c, $(SRCROOT)/%.o, $(SRC))

$(TARGET): $(OBJS) $(LIB_TARGET)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(FRONTEND_DIR)/%.o: $(FRONTEND_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@ 

ALL   += $(TARGET)
CLEAN += $(OBJS) $(TARGET)

install: $(TARGET)

uninstall: 
	$(RM) $(TARGET)

run: install
	./$(TARGET)

# ================== [ UNIT TESTING ] ===================
#

TEST_DIR  := $(SRCROOT)/tests

TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(TEST_DIR)/%.bin, $(TEST_SRCS))

CLEAN += $(TEST_OBJS)

TEST_LDFLAGS := $(shell pkg-config --cflags --libs check)

$(TEST_DIR)/%.bin: $(TEST_DIR)/%.c $(LIB_TARGET)
	$(CC) $(CFLAGS) $^ -o $@ $(TEST_LDFLAGS) $(LDFLAGS)

all: $(ALL)

tests: $(TEST_OBJS)

test: $(TEST_OBJS)
	@for test in $(TEST_OBJS); do $$test ; done

# ================== [ LCOV REPORT ] ===================
#

LCOV_REPORT  := $(SRCROOT)/$(LIB_TARGET_NAME).lcov_report
COV_HTML_OUT := $(SRCROOT)/out

CLEAN += \
	$(wildcard $(SRCROOT)/*.gcov $(TEST_DIR)/*.gcov $(BACKEND_DIR)/*.gcov) \
	$(wildcard $(SRCROOT)/*.gcda $(TEST_DIR)/*.gcda $(BACKEND_DIR)/*.gcda) \
	$(wildcard $(SRCROOT)/*.gcno $(TEST_DIR)/*.gcno $(BACKEND_DIR)/*.gcno) \
	$(COV_HTML_OUT) \
	$(LCOV_REPORT)

LCOV_EXCLUDE := 

gcov_report:
	$(MAKE) clean
	$(MAKE) WITH_COVERAGE=yes all tests
	$(MAKE) test
	lcov -t $(LIB_TARGET_NAME) -o $(LCOV_REPORT) -c -d .
	lcov --remove $(LCOV_REPORT) -o $(LCOV_REPORT) $(LCOV_EXCLUDE)

	genhtml -o $(COV_HTML_OUT) $(LCOV_REPORT)
	xdg-open out/index.html

# ================== [ EXTRA ] ===================
#

clean:
	$(RM) $(CLEAN)

lint: run-clang-format run-ccheck

format fmt: run-clang-reformat

all: $(ALL)

build: $(TARGET)

.PHONY: $(PHONY)
