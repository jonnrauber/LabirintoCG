/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * Implementação da função de desenho do objeto pinheirinho, chamado no arquivo main.cpp
 * */

#include "defs.h"

GLUquadric* quad1 = gluNewQuadric();
GLUquadric* bolas = gluNewQuadric();

GLfloat altura = TAM_BLOCO*0.9;
GLfloat largura = TAM_BLOCO/4.0;
GLfloat larguraTronco = largura*0.2;
GLfloat tamPresente1 = altura*0.3;
GLfloat tamPresente2 = altura*0.15;
GLfloat tamPresente3 = altura*0.2;
void DesenhaObjeto3() {
	glPushMatrix();
		glRotatef(-90.f, 1.f, 0.f, 0.f);
		glPushMatrix();
			glTranslatef(0.f, 0.f, .1f);
			glColor3f(102.f/255.f, 62.f/255.f, 9.f/255.f);
			gluDisk(quad1, 0, larguraTronco*5, 10, 30);
			glColor3f(0.7, 0.2, 0);
			gluDisk(quad1, larguraTronco*4, larguraTronco*8, 30, 30);
		glPopMatrix();
		gluCylinder(quad1, larguraTronco, larguraTronco, altura/3.0, 30, 30);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.f, altura/3.0, 0.f);
		glRotatef(-90.0f, 1.f, 0.f, 0.f);
		glColor3f(0.1f, 1.f, 0.2f);
		glPushMatrix();
			gluCylinder(quad1, largura, 0, altura, 30, 30);
			glTranslatef(0.f, 0.f, altura/3.0);
			gluCylinder(quad1, largura*0.8, 0, altura*0.8, 30, 30);
			glTranslatef(0.f, 0.f, altura/3.0);
			gluCylinder(quad1, largura*0.6, 0, altura*0.6, 30, 30);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glColor3f(1.f, .5f, .1f);
		glTranslatef(tamPresente1, tamPresente1*0.5, -tamPresente1);
		glutSolidCube(tamPresente1);
	glPopMatrix();
	glPushMatrix();
		glColor3f(.7f, 1.f, .3f);
		glTranslatef(0.f, tamPresente2*0.5, -tamPresente1*1.25);
		glutSolidCube(tamPresente2);
	glPopMatrix();
	glPushMatrix();
		glColor3f(.5f, .1f, 1.f);
		glTranslatef(-tamPresente3, tamPresente3*0.5, -tamPresente3);
		glutSolidCube(tamPresente3);
	glPopMatrix();
	
	//nivel 1
	glPushMatrix();
		glColor3f(1.f, 0.0f, 0.0f);
		glTranslatef(1.5,22,0);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 1.0f);
		glTranslatef(-1.5,22,0);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	
	//nivel2
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 1.0f);
		glTranslatef(0,15,3);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.f, 0.0f, 0.0f);
		glTranslatef(0,15,-3);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(3,15,0);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.2f, 0.0f, 1.0f);
		glTranslatef(-3,15,0);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	
	//nivel3
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 0.0f);
		glTranslatef(1.75,9,-3.5);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.0f, 0.5f, 0.5f);
		glTranslatef(-1.75,9,-3.5);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.0f, 0.0f, 1.0f);
		glTranslatef(1.75,9,3.5);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1.f, 0.0f, 0.0f);
		glTranslatef(-1.75,9,3.5);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.2f, 0.0f, 1.0f);
		glTranslatef(4,9,0);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.3f, 0.4f, 0.2f);
		glTranslatef(-4,9,0);
        gluSphere(bolas, 1, 30, 30);
	glPopMatrix();
}
