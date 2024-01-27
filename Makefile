GTEST_DIR = ../googletest
GTEST_LIB = $(GTEST_DIR)/googlemock/gtest/libgtest.a
GTEST_INCLUDE = -I$(GTEST_DIR)/googletest/include
CPPFLAGS = -g -Wall -std=c++17 $(GTEST_INCLUDE)
LDFLAGS = -L$(GTEST_DIR)/googlemock/gtest
LDLIBS = -lgtest -lpthread

# Targets
all: main test

main: main.o
	$(CXX) $(CPPFLAGS) -o $@ $^

test: main.test.o main.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	$(RM) *.o main test

.PHONY: all clean