APP = trabalhocg

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
 
# Name of the project
PROJ_NAME=trabalhocg
 
# .c files
C_SOURCE=$(wildcard *.cpp)
 
# .h files
H_SOURCE=$(wildcard *.h)
 
# Object files
OBJ=$(C_SOURCE:.c=.o)
 
# Compiler
CC=gcc

LIBS=-framework GLUT	\
	 -framework OpenGL	\
	 -Wno-deprecated    \
	 -lc++				\
	 -std=c++11
 
#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) $(LIBS) -o $@ $^
 
%.o: %.cpp %.h
	$(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.cpp $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)
 
clean:
	rm -rf *.o $(PROJ_NAME) *~

run: $(PROJ_NAME)
	./$(PROJ_NAME) $(ARGS)
