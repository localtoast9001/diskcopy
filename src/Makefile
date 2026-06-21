CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2

INCLUDES :=\
  ../inc

TARGET := ../out/diskcopy
SRC := \
	arguments.cpp \
	copy_processor.cpp \
	error.cpp \
	file_device.cpp \
	file_handle.cpp \
	main.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCLUDES)) $(SRC) -o $@

clean:
	rm -f $(TARGET)
