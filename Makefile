CXX := g++
CXXFLAGS := -std=c++17 -g -Wall -m64 -I include -I C:/SDL2-w64/include
LDFLAGS := -L C:/SDL2-w64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)
OUT := bin/debug/main


all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(OBJ) $(OUT)
