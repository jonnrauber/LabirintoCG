#include "defs.h"
#include "objeto1.h"

GLfloat luz_objeto1[] = { 0.9, 0.8, 0.7, 1.0 };

void DesenhaObjeto1() {
	
	glColor3f(203.0/255, 161.0/255, 56.0/255); //cor marrom
	
	/* TAMPO DA MESA */
	glPushMatrix();
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_mesa);
		glTranslatef(0, (ALTURA_MESA+GROSSURA_MESA)/2.0, 0);
		glScalef(LARGURA_MESA, GROSSURA_MESA, COMPRIMENTO_MESA);
		glutSolidCube(1);
	glPopMatrix();
	
	/* PÉS DA MESA */
	glPushMatrix();
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_mesa);		
		glTranslatef(LARGURA_MESA/2.0 - GROSSURA_PE/2.0, 0, COMPRIMENTO_MESA/2.0 - GROSSURA_PE/2.0);
		glScalef(GROSSURA_PE, ALTURA_MESA, GROSSURA_PE);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_mesa);		
		glTranslatef(LARGURA_MESA/2.0 - GROSSURA_PE/2.0, 0, -(COMPRIMENTO_MESA/2.0 - GROSSURA_PE/2.0));
		glScalef(GROSSURA_PE, ALTURA_MESA, GROSSURA_PE);
		glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_mesa);		
		glTranslatef(-(LARGURA_MESA/2.0 - GROSSURA_PE/2.0), 0, COMPRIMENTO_MESA/2.0 - GROSSURA_PE/2.0);
		glScalef(GROSSURA_PE, ALTURA_MESA, GROSSURA_PE);
		glutSolidCube(1);
	glPopMatrix();
	
	glPushMatrix();
		//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_mesa);		
		glTranslatef(-(LARGURA_MESA/2.0 - GROSSURA_PE/2.0), 0, -(COMPRIMENTO_MESA/2.0 - GROSSURA_PE/2.0));
		glScalef(GROSSURA_PE, ALTURA_MESA, GROSSURA_PE);
		glutSolidCube(1);
	glPopMatrix();
	
	/* TEAPOT */
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_objeto1);	
		glTranslatef(0, ALTURA_MESA/2.0 + GROSSURA_MESA*1.5, 0);
		glColor3f(1, 0, 0);
		glutSolidTeapot(GROSSURA_MESA);
	glPopMatrix();
}

