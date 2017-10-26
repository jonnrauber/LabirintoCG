/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#include "defs.h"
#include "objeto1.h"

void DesenhaObjeto1() {
	glScalef(3, 3.5, 3);
	glTranslatef(-4,2,0);
	glPushMatrix();
		glTranslatef(-4,0,0);
	    glScalef(1,1,2);
		glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1,1,0);
	    glScalef(4,2,2);
		glutSolidCube(2);
	glPopMatrix();
	
	glColor3f(0.2f,0.2f,0.2f);
	glPushMatrix();
		glTranslatef(-3,-1.3,2);
        glutSolidTorus(0.5,0.8,20,20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(3,-1.3,2);
        glutSolidTorus(0.5,0.8,20,20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(3,-1.3,-2);
        glutSolidTorus(0.5,0.8,20,20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-3,-1.3,-2);
        glutSolidTorus(0.5,0.8,20,20);
	glPopMatrix();
	
	glColor3f(0.5f, 0.5f, 0.5f);
	glPushMatrix();
        GLUquadricObj *esfera = gluNewQuadric();
        glTranslatef(-1.2,1.3,2.01);
        glRotatef(45,0,0,1);
        glScalef(2.5,2.5,0);
        gluSphere(esfera, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera2 = gluNewQuadric();
        glTranslatef(2,1.3,2.01);
        glRotatef(45,0,0,1);
        glScalef(2.5,2.5,0);
        gluSphere(esfera2, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera3 = gluNewQuadric();
        glTranslatef(-1.2,1.3,-2.01);
        glRotatef(45,0,0,1);
        glScalef(2.5,2.5,0);
        gluSphere(esfera3, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera4 = gluNewQuadric();
        glTranslatef(2,1.3,-2.01);
        glRotatef(45,0,0,1);
        glScalef(2.5,2.5,0);
        gluSphere(esfera4, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera5 = gluNewQuadric();
        glTranslatef(-3.1,2,0.7);
        glRotatef(90,0,1,0);
        glRotatef(45,0,0,1);
        glScalef(2.0,2.0,0);
        gluSphere(esfera5, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera6 = gluNewQuadric();
        glTranslatef(-3.1,2,-0.7);
        glRotatef(90,0,1,0);
        glRotatef(45,0,0,1);
        glScalef(2.0,2.0,0);
        gluSphere(esfera6, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera7 = gluNewQuadric();
        glTranslatef(5.1,2,0.7);
        glRotatef(90,0,1,0);
        glRotatef(45,0,0,1);
        glScalef(2.0,2.0,0);
        gluSphere(esfera7, 0.5f, 4, 4);
	glPopMatrix();
	
	glPushMatrix();
        GLUquadricObj *esfera8 = gluNewQuadric();
        glTranslatef(5.1,2,-0.7);
        glRotatef(90,0,1,0);
        glRotatef(45,0,0,1);
        glScalef(2.0,2.0,0);
        gluSphere(esfera8, 0.5f, 4, 4);
	glPopMatrix();
	
}

