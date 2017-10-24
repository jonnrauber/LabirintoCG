BINEXEC=main

all: ${BINEXEC} run

run:
	./main

${BINEXEC}: robot.o objeto1.o main.cpp
	g++ main.cpp robot.cpp objeto1.cpp -Wall -lm -lGL -lGLU -lglut -o main

robot.o: robot.cpp
	g++ -c robot.cpp -Wall -lm -lGL -lGLU -lglut

objeto1.o: objeto1.cpp
	g++ -c objeto1.cpp -Wall -lGL -lGLU -lglut        

order: 
	rm -f *.o

clean:
	rm -f *.o ${BINEXEC}
