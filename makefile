# Compilador
CXX   := g++

# Diretorios
SOURCES_DIR := ./src
INCLUDE_DIR := ./include
TARGET_DIR  := ./bin
BUILD_DIR   := ./build
TEST_DIR    := ./test

# Flags
FLAGS := -I$(INCLUDE_DIR) $(shell pkg-config raylib --cflags) -Werror -Wall -Wextra
LIBS  := $(shell pkg-config raylib --libs)
# -fsanitize=address

# Arquivos
SRCEXT := .cpp
HDREXT := .hpp
OBJEXT := .o

SRCS := $(wildcard $(SOURCES_DIR)/*$(SRCEXT))
OBJS := $(patsubst $(SOURCES_DIR)/%$(SRCEXT),$(BUILD_DIR)/%$(OBJEXT),$(SRCS))
TESTS := $(wildcard $(TEST_DIR)/*$(SRCEXT))

TARGET := $(TARGET_DIR)/Pendulos
TESTAPP := $(TARGET_DIR)/test

# Compilação
$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%$(OBJEXT): $(SOURCES_DIR)/%$(SRCEXT)
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

test:
	$(CXX) $(FLAGS) -o $(TESTAPP) $(TESTS) $(LIBS)

runtest:
	$(TESTAPP)

clean:
	@echo "Removendo executáveis de $(TARGET_DIR)..."
	@find $(TARGET_DIR) -type f -executable -exec rm -fv {} \;
	@echo "Removendo objetos de $(BUILD_DIR)..."
	@rm -rfv $(BUILD_DIR)/*$(OBJEXT)

rebuild: clean $(TARGET)
	$(MAKE)

.PHONY: run test runtest clean rebuild