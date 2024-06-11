# Compilador
CXX   := g++
# Diretorios
SOURCES_DIR := ./src
INCLUDE_DIR := ./include
TARGET_DIR  := ./bin
BUILD_DIR   := ./build
# Flags
FLAGS := -I$(INCLUDE_DIR) $(shell pkg-config raylib --cflags) -Werror -Wall -Wextra
# -fsanitize=address
LIBS  := $(shell pkg-config raylib --libs)
# Arquivos
SRCEXT := .cpp
HDREXT := .hpp
SRCS := $(wildcard $(SOURCES_DIR)/*$(SRCEXT))
OBJS := $(patsubst $(SOURCES_DIR)/%$(SRCEXT),$(BUILD_DIR)/%.o,$(SRCS))
TARGET := $(TARGET_DIR)/Pendulos

# Compilação
$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SOURCES_DIR)/%$(SRCEXT)
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR)/*

rebuild: clean $(TARGET)
	$(MAKE)

.PHONY: run clean rebuild