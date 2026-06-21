CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

INCLUDES :=\
  ../inc

TARGET := ../out/diskcopy_ut
PROD_SRC := \
  ../src/arguments.cpp \
  ../src/error.cpp \
  ../src/file_device.cpp \
  ../src/file_handle.cpp \

SRC := \
  $(PROD_SRC) \
  arguments_test.cpp \
  error_test.cpp \
  file_device_test.cpp \
  file_handle_test.cpp \
  main.cpp \
  test_class.cpp \
  test_context.cpp \
  test_runner.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCLUDES)) $(SRC) -o $@

clean:
	rm -f $(TARGET)
