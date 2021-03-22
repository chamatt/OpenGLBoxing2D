CC =g++
CFLAGS =-lGL\
		 -lGLU\
		 -lglut\

all: trabalhocg

trabalhocg: *.o
	$(CC) -o  trabalhocg *.cpp $(CFLAGS)
clean:
	rm -rf *.o trabalhocg
