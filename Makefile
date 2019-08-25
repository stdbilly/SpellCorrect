INC_DIR:= include/ 
#include/net/ include/threadpool/ include/cppjieba/ include/json/
SRC_DIR:= src/net src/
SRCS:=$(wildcard src/*.cc) $(wildcard src/net/*.cc) $(wildcard src/threadpool/*.cc) 
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -w -g  $(addprefix -I , $(INC_DIR)) $(LIBS) 

EXE:=bin/SpellCorrectServer.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
