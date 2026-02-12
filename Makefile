# force macs to use g++-15 to avoid clang mapped to g++
ifeq ($(OS),Windows_NT)
	CXX = g++
else
	# unnecessary with Nix

	#OS_NAME := $(shell uname -s)
	#ifeq ($(OS_NAME),Darwin)
	#	CXX = g++-15
	#else
	#	CXX = g++
	#endif

	CXX = "c++"
endif

# compiler options
CXXFLAGS = -g -Wall -Wextra
# -fmodules-ts was renamed to -fmodules in Clang
CXXFLAGS += -std=c++20 -fmodules -pedantic -pedantic-errors
CXXFLAGS += -Wfloat-equal -Wredundant-decls -Wshadow -Wconversion -Wuninitialized
# uncomment the following lines to enable address sanitizer on non-Windows platforms
# ifneq ($(OS),Windows_NT)
# 	CXXFLAGS += -fsanitize=address
# endif

# list .h files here
HEADERS =

# list .cpp files here
TEST_FILES = tests.cpp
SHARED_FILES =

.PHONY: all
all: tests.exe

.PHONY: tests.exe # Always force rebuild of tests
tests.exe:  $(SHARED_FILES) $(TEST_FILES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SHARED_FILES) $(TEST_FILES) -o $@

.PHONY: clean
clean:
	rm -vf tests.exe
