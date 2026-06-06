CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

INCLUDES :=\
  ../inc

TARGET := ../out/diskcopy
SRC := \
	main.cpp \
	arguments.cpp

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCLUDES)) $(SRC) -o $@

clean:
	rm -f $(TARGET)
