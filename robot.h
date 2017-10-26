/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#ifndef ROBOT
#define ROBOT

#include <GL/glut.h>

typedef struct robot {
	GLfloat rot_perna_dir;
	GLfloat rot_perna_esq;
	GLfloat rot_braco_dir;
	GLfloat rot_braco_esq;
	GLfloat rot_cabeca;
	int movendo_pernas;	
	GLUquadricObj* quadric;
} robot;


void 	DesenhaRobot(robot *Robot);
robot* 	inicializaRobot();
void 	liberaRobot(robot *Robot);
void 	move_pernas(robot *Robot);

#endif
