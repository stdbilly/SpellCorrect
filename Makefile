INC_DIR:= include/
SRC_DIR:= src/net src/
SRCS:=$(wildcard src/*.cc) $(wildcard src/net/*.cc) $(wildcard src/threadpool/*.cc) 
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -w -g  $(addprefix -I , $(INC_DIR)) $(LIBS) 

EXE:=bin/server.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
