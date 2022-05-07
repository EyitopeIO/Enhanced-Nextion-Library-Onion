# Today:	7-MAY-2022
# Name:		Eyitope Adelowo (adeyitope.io@gmail.com)

CXX			:= /home/eyi/OpenWRT/source/staging_dir/toolchain-mipsel_24kc_gcc-7.3.0_musl/bin/mipsel-openwrt-linux-g++
OBJ			:= ./obj
SRC			:= ./src
SRCS		:= $(wildcard $(SRC)/*.cpp)
OBJS		:= $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
INC			:= ./include
BIN			:= ./bin
EXE			:= $(BIN)/nxexe
CXXFLAGS	:= -I$(INC) -Wall -w -Wfatal-errors -std=c++11 -pthread # -frtti 


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
