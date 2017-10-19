BINEXEC=main

all: ${BINEXEC}

${BINEXEC}: robot.o main.cpp
	g++ main.cpp robot.cpp -Wall -lm -lGL -lGLU -lglut -o main

robot.o: robot.cpp
	g++ -c robot.cpp -Wall -lm -lGL -lGLU -lglut
        
order: 
	rm -f *.o

clean:
	rm -f *.o ${BINEXEC}
