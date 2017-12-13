BINEXEC=main

all: ${BINEXEC} run

run:
	./main

${BINEXEC}: robot.o objeto1.o objeto2.o objeto3.o bmp.o main.cpp
	g++ main.cpp robot.cpp objeto1.cpp objeto2.cpp objeto3.cpp bmp.cpp -Wall -lm -lGL -lGLU -lglut -o main

robot.o: robot.cpp
	g++ -c robot.cpp -Wall -lm -lGL -lGLU -lglut

objeto1.o: objeto1.cpp
	g++ -c objeto1.cpp -Wall -lGL -lGLU -lglut

objeto2.o: objeto2.cpp
	g++ -c objeto2.cpp -Wall -lGL -lGLU -lglut

objeto3.o: objeto3.cpp
	g++ -c objeto3.cpp -Wall -lGL -lGLU -lglut

bmp.o: bmp.cpp
	g++ -c bmp.cpp -Wall -lGL -lGLU -lglut

order:
	rm -f *.o

clean:
	rm -f *.o ${BINEXEC}
