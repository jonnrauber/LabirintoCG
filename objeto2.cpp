/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * Implementação da função de desenho do objeto boneco de neve, chamado no arquivo main.cpp
 * */

#include "defs.h"

void DesenhaObjeto2() {
	glTranslatef(0,7,0);
	glRotatef(180,0,1,0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		GLUquadricObj *corpo = gluNewQuadric();
        gluSphere(corpo, 4, 30, 30);
	glPopMatrix();

	glPushMatrix();
		GLUquadricObj *corpo2 = gluNewQuadric();
		glTranslatef(0,4,0);
        gluSphere(corpo2, 3, 30, 30);
	glPopMatrix();

	glPushMatrix();
		GLUquadricObj *cabeca = gluNewQuadric();
		glTranslatef(0,7,0);
        gluSphere(cabeca, 2, 30, 30);
	glPopMatrix();

	glColor3f(0.647f, 0.1647f, 0.1647f);
	glPushMatrix();
	    GLUquadricObj *braco = gluNewQuadric();
	    glTranslatef(-2,5,0);
	    glRotatef(90,1,0,0);
	    glRotatef(-45,0,1,0);
		gluCylinder(braco, 0.3, 0.3, 5, 20, 20);
	glPopMatrix();

	glPushMatrix();
	    GLUquadricObj *braco2 = gluNewQuadric();
	    glTranslatef(2,5,0);
	    glRotatef(90,1,0,0);
	    glRotatef(45,0,1,0);
		gluCylinder(braco2, 0.3, 0.3, 5, 20, 20);
	glPopMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		GLUquadricObj *botao = gluNewQuadric();
	    glTranslatef(0,6,2.5);
        gluSphere(botao, 0.3, 30, 30);
	glPopMatrix();

	glPushMatrix();
		GLUquadricObj *botao2 = gluNewQuadric();
	    glTranslatef(0,5,2.8);
        gluSphere(botao2, 0.3, 30, 30);
	glPopMatrix();

	glPushMatrix();
		GLUquadricObj *botao3 = gluNewQuadric();
	    glTranslatef(0,4,3);
        gluSphere(botao3, 0.3, 30, 30);
	glPopMatrix();

	glColor3f(0.0f, 0.5f, 0.0f);
	glPushMatrix();
		glTranslatef(0.75,8.5,1.3);
		gluSphere(botao3, 0.3, 30, 30);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.75,8.5,1.3);
		gluSphere(botao3, 0.3, 30, 30);
	glPopMatrix();

	glColor3f(1.0f, 0.5f, 0.0f);
	glPushMatrix();
		glTranslatef(0,8,1.5);
		glutSolidCone(0.5,2,30,30);
	glPopMatrix();

	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
		glTranslatef(0,9,0);
		glRotatef(-90,1,0,0);
		glutSolidCone(1.5,4,30,30);
	glPopMatrix();

}
