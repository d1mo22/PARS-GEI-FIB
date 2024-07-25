DUMMY_OBJ = AIDummy.o
BOARD_OBJ = Board.o

# Add here any extra .o player files you want to link to the executable
EXTRA_OBJ =

# Configuration
OPTIMIZE = 2 # Optimization level    (0 to 3)
DEBUG    = 0 # Compile for debugging (0 or 1)

# For debugging matches
# OPTIMIZE = 0, DEBUG = 1

# Flags
ifeq ($(strip $(DEBUG)),1)
	DEBUGFLAGS=-g -O0 -fno-inline
endif

CXXFLAGS = -std=c++11 -Wall -Wno-unused-variable -fPIC $(DEBUGFLAGS) -O$(strip $(OPTIMIZE))
LDFLAGS  = -std=c++11                                  $(DEBUGFLAGS) -O$(strip $(OPTIMIZE))

# The following two lines will detect all your players (files matching "AI*.cc")

PLAYERS_SRC = $(wildcard AI*.cc)
PLAYERS_OBJ = $(patsubst %.cc, %.o, $(PLAYERS_SRC)) $(EXTRA_OBJ) $(DUMMY_OBJ) $(BOARD_OBJ)

# Rules

OBJ = Structs.o Settings.o State.o Info.o Random.o Board.o Action.o Player.o Registry.o Utils.o

all: Game

clean:
	rm -rf Game  *.o *.exe Makefile.deps

Game:  $(OBJ) Game.o Main.o $(PLAYERS_OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)

: $(OBJ) SecGame.o SecMain.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lrt

%.exe: %.o $(OBJ) SecGame.o SecMain.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lrt

Makefile.deps: *.cc
	$(CXX) $(CXXFLAGS) -MM *.cc > Makefile.deps

include Makefile.deps
