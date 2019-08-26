INC_DIR:= json/ 
#include/net/ include/threadpool/ include/cppjieba/ include/json/
SRC_DIR:= ./
SRCS:=$(wildcard *.cc) 
OBJS:= $(patsubst %.cc, %.o, $(SRCS))
#LIBS:= -lpthread

CXX:=g++

CXXFLAGS:= -w -g  $(addprefix -I , $(INC_DIR)) 
#$(LIBS) 

EXE:=client.exe

$(EXE):$(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
