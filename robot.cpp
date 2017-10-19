#include "robot.h"

#define TAM_CABECA 4	

void DesenhaCorpo() {
	GLfloat v[8][3] = {
			{-3.5, -5, 2},
			{3.5, -5, 2},
			{3.5, 5, 2},
			{-3.5, 5, 2},
			{-3.5, -5, -2},
			{3.5, -5, -2},
			{3.5, 5, -2},
			{-3.5, 5, -2}
		};	
		
	glBegin(GL_QUADS);
		glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[2]); glVertex3fv(v[3]);
		
		glVertex3fv(v[4]); glVertex3fv(v[5]); glVertex3fv(v[6]); glVertex3fv(v[7]);
		
		glVertex3fv(v[1]); glVertex3fv(v[5]); glVertex3fv(v[6]); glVertex3fv(v[2]);
				
		glVertex3fv(v[0]); glVertex3fv(v[4]); glVertex3fv(v[7]); glVertex3fv(v[3]);
		
		glVertex3fv(v[2]); glVertex3fv(v[6]); glVertex3fv(v[7]); glVertex3fv(v[3]);
		
		glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[5]); glVertex3fv(v[4]);
	glEnd();
}

void DesenhaPe() {
	GLfloat v[8][3] = {
			{-0.75, -0.25, 2},
			{0.75, -0.25, 2},
			{0.75, 0.25, 2},
			{-0.75, 0.25, 2},
			{-0.75, -0.25, -2},
			{0.75, -0.25, -2},
			{0.75, 0.25, -2},
			{-0.75, 0.25, -2}
		};	
		
	glBegin(GL_QUADS);
		glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[2]); glVertex3fv(v[3]);
		
		glVertex3fv(v[4]); glVertex3fv(v[5]); glVertex3fv(v[6]); glVertex3fv(v[7]);
		
		glVertex3fv(v[1]); glVertex3fv(v[5]); glVertex3fv(v[6]); glVertex3fv(v[2]);
				
		glVertex3fv(v[0]); glVertex3fv(v[4]); glVertex3fv(v[7]); glVertex3fv(v[3]);
		
		glVertex3fv(v[2]); glVertex3fv(v[6]); glVertex3fv(v[7]); glVertex3fv(v[3]);
		
		glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[5]); glVertex3fv(v[4]);
	glEnd();
}

void DesenhaRobot(robot *Robot) {
	glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
	
	//desenha o corpo
	glPushMatrix();
		DesenhaCorpo();
	glPopMatrix();
	
	//desenha pescoço
	glPushMatrix();
		glTranslatef(0.0f, 6.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(Robot->quadric, 0.75, 0.75, 1.5, 20, 10);
	glPopMatrix();
	
	//desenha cabeça
	glPushMatrix();
		glTranslatef(0.0f, 8.5f, 0.0f);
		glutSolidCube(TAM_CABECA);
	glPopMatrix();	
	
	//desenha os braços
	///braco direito
	glPushMatrix();
		glRotatef(Robot->rot_braco_dir, 1, 0, 0);
		glTranslatef(3.5f, 4.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.3f, 0.0f);
		gluCylinder(Robot->quadric, 0.75, 0.75, 7.0, 20, 10);
	glPopMatrix();
	///braco esquerdo
	glPushMatrix();
		glRotatef(Robot->rot_braco_esq, 1, 0, 0);
		glTranslatef(-3.5f, 4.0f, 0.0f);
		glRotatef(90.0f, 1.0f, -0.3f, 0.0f);
		gluCylinder(Robot->quadric, 0.75, 0.75, 7.0, 20, 10);
	glPopMatrix();
	
	
	/* desenha os membros inferiores */
	
	///membros direitos
	glPushMatrix();
		glRotatef(Robot->rot_perna_dir, 1, 0, 0);
		//coxa direita
		glPushMatrix();
			glTranslatef(1.5f, -5.0f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.05f, 0.0f);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.5, 20, 10);
		glPopMatrix();
		//canela direita
		glPushMatrix();
			glTranslatef(1.5f, -8.5f, 0.0f);
			glRotatef(90.0f, 1.0f, -0.05f, 0.0f);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.0, 20, 10);
		glPopMatrix();
		//pé direito
		glPushMatrix();
			glTranslatef(1.5f, -11.75f, 0.0f);
			DesenhaPe();
		glPopMatrix();
	glPopMatrix();
	///membros esquerdos
	glPushMatrix();
		glRotatef(Robot->rot_perna_esq, 1, 0, 0);
		//coxa esquerda
		glPushMatrix();
			glTranslatef(-1.5f, -5.0f, 0.0f);
			glRotatef(90.0f, 1.0f, -0.05f, 0.0f);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.5, 20, 10);
		glPopMatrix();
		//canela esquerda
		glPushMatrix();
			glTranslatef(-1.5f, -8.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.05f, 0.0f);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.0, 20, 10);
		glPopMatrix();
		//pé esquerdo
		glPushMatrix();
			glTranslatef(-1.5f, -11.75f, 0.0f);
			DesenhaPe();
		glPopMatrix();
	glPopMatrix();
}

robot* inicializaRobot() {
	robot* Robot = (robot *)malloc(sizeof(robot *));
	Robot->rot_perna_dir = 0;
	Robot->rot_perna_esq = 0;
	Robot->rot_braco_dir = 0;
	Robot->rot_braco_esq = 0;
	Robot->movendo_pernas = 0;
	Robot->quadric = gluNewQuadric();
	
	return Robot;	
}

void liberaRobot(robot *Robot) {
	free(Robot);
}

void DesenhaRobot2() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	gluLookAt(5.0, 5.0, -50.0, 
				0.0, 0.0, 0.0, 
				0.0, 1.0, 0.0);
	
	//DesenhaRobot(Robot);
	
	glutSwapBuffers();
}

void Inicializa1() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void move_pernas(robot *Robot) {
	switch(Robot->movendo_pernas) {
		case 1:
		case 2:
			Robot->rot_perna_dir = 30;
			Robot->rot_perna_esq = -15;
			Robot->rot_braco_dir = -15;
			Robot->rot_braco_esq = 30;
			Robot->movendo_pernas++;
			break;
		case 3:
		case 4:
			Robot->rot_perna_dir = -15;
			Robot->rot_perna_esq = 30;
			Robot->rot_braco_dir = 30;
			Robot->rot_braco_esq = -15;
			Robot->movendo_pernas++;
			break;
		case 5:
		case 6:
			Robot->rot_perna_dir = 0;
			Robot->rot_perna_esq = 0;
			Robot->rot_braco_dir = 0;
			Robot->rot_braco_esq = 0;
			Robot->movendo_pernas++;
			break;
		default:
			Robot->movendo_pernas = 0;
			break;		
	}
	glutPostRedisplay();
}