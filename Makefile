# 변수 정의
CXX = g++
# 원래 있던 -o my_app를 빼주고, 중복된 -Wall도 하나만 남깁니다.
CXXFLAGS = -g -Wall -std=c++17 -m64 -I include -MMD -MP

LDFLAGS = -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lbox2d 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

DEBUG_BIN = $(BIN_DIR)/debug/main
RELEASE_BIN = $(BIN_DIR)/release/main

# 소스 파일 및 오브젝트 파일
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPENDS = $(OBJECTS:.o=.d)

all: debug

debug: $(DEBUG_BIN)
release: $(RELEASE_BIN)

# 디버그 빌드
$(DEBUG_BIN): $(OBJECTS)
	@mkdir -p $(BIN_DIR)/debug
	$(CXX) $^ -o $@ $(LDFLAGS)

# 릴리스 빌드
$(RELEASE_BIN): $(OBJECTS)
	@mkdir -p $(BIN_DIR)/release
	$(CXX) $^ -o $@ $(LDFLAGS) -O3 -s

# 오브젝트 파일 생성
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -g -c $< -o $@

-include $(DEPENDS)

all: 
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"

# 청소 타겟
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/debug $(BIN_DIR)/release

.PHONY: all debug release clean
