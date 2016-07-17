TARGET=ct9
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:%.cpp=%.o)
#FLAGS= #-Wall -Wextra -Werror -Wfatal-errors
FLAGS= -I/usr/include/freetype2 -std=c++11
CCLIBS= -lGL -lglfw -lftgl #-lglut -lGLU -lGL

all: version.h $(OBJS)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJS) $(CCLIBS)

version.h:
	sh version.sh

.cpp.o:
	$(CXX) $(FLAGS) -c -o $*.o $<

clean:
	$(RM) $(TARGET) *.o *~ core* version.h
