
MAINSRC =game.cpp
MAINLIB = -framework GLUT -framework OpenGL -pthread
SRC = $(MAINSRC) imageloader.cpp draw.cpp mat_matr.cpp mat_vect.cpp  load_bmp.cpp object.cpp load_3ds.cpp game.cpp   

OBJ = $(SRC:.c=.o)

OPT = -O3
CC = g++ $(OPT) -Wall

# You might have to change GLU to MesaGLU depending on your Mesa version
GLLIBS = $(MAINLIB)
LIBS = $(GLLIBS) -lm

all:chess

.c.o:
	$(CC) -c $<

chess: $(OBJ)
	g++ -o $@ -g $^ $(LIBS)

clean:
	rm -f chess *.o
