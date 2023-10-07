# Today:	7-MAY-2022
# Name:		Eyitope Adelowo (adeyitope.io@gmail.com)

OBJ:=./obj
SRC:=./src
SRCS:= $(wildcard $(SRC)/*.cpp)
OBJS:= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
INC:= ./include
BIN:= ./bin
EXE:= $(BIN)/knemesis
CFLAGS:= -I$(INC) -Wall -w -Wfatal-errors -std=c++11 -pthread # -frtti
CXXFLAGS:= $(CFLAGS) -std=gnu99

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp | $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	mkdir $@

run: $(EXE)
	$<

clean:
	rm -rf $(OBJ) $(BIN)
