TARGET=ct9
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:%.cpp=%.o)
#FLAGS= #-Wall -Wextra -Werror -Wfatal-errors
FLAGS= -I/usr/include/freetype2 -std=c++11
CCLIBS= -lGL -lglfw -lftgl #-lglut -lGLU -lGL

all: $(OBJS)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJS) $(CCLIBS)

.cpp.o:
	$(CXX) $(FLAGS) -c -o $*.o $<

clean:
	$(RM) $(TARGET) *.o *~ core*
