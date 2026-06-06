CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

INCLUDES :=\
  ../inc

TARGET := ../out/diskcopy_ut
PROD_SRC := \
  ../src/arguments.cpp

SRC := \
  $(PROD_SRC) \
  arguments_test.cpp \
  main.cpp \
  test_class.cpp \
  test_runner.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCLUDES)) $(SRC) -o $@

clean:
	rm -f $(TARGET)
