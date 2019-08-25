INC_DIR1:= include/
INC_DIR2:= include/ include/net/ include/threadpool/ include/cppjieba

SRC_DIR1:= src/ src/offline
SRC_DIR2:= src/net src/

SRCS1:=$(wildcard src/offline/*.cc) $(wildcard src/Configuration.cc)
SRCS2:=$(wildcard src/*.cc) $(wildcard src/net/*.cc) $(wildcard src/threadpool/*.cc) 

OBJS1:= $(patsubst %.cc, %.o, $(SRCS1))
OBJS2:= $(patsubst %.cc, %.o, $(SRCS2))

LIBS:= -lpthread

CXX:=g++

CXXFLAGS1:= -w -g  $(addprefix -I, $(INC_DIR1)) $(LIBS) 
CXXFLAGS2:= -w -g  $(addprefix -I , $(INC_DIR2)) $(LIBS) 

EXE1:=bin/offline.exe
EXE2:=bin/SpellCorrectServer.exe

$(EXE1):$(OBJS1)
	$(CXX) -o $(EXE1) $(OBJS1) $(CXXFLAGS1)

$(EXE2):$(OBJS2)
	$(CXX) -o $(EXE2) $(OBJS2) $(CXXFLAGS2)


clean:
	rm -rf $(EXE1)
	rm -rf $(OBJS1)
	rm -rf $(EXE2)
	rm -rf $(OBJS2)
