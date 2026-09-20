# ============================================
#  Makefile untuk Pseudocode Interpreter
# ============================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I src
BIN_DIR  := bin
TARGET   := $(BIN_DIR)/interpreter

# Ambil semua .cpp di src/, kecuali yang punya main sendiri kalau ada
SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $@
	@echo "[SUKSES] Binary: $@"

# Setiap .o butuh .cpp dan header terkait
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target: jalankan interpreter (butuh argumen FILE=...)
# Contoh: make run FILE=examples/faktorial.psdc
run: $(TARGET)
	./$(TARGET) $(FILE)

clean:
	rm -f src/*.o
	rm -rf $(BIN_DIR)
	@echo "[OK] Sudah dibersihkan."

# Target: jalankan semua test (asumsi tests/run_tests.sh ada)
test: $(TARGET)
	@cd tests && ./run_tests.sh