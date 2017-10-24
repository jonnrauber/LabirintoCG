#include "defs.h"
#include "robot.h"

void DesenhaCorpo() {
	GLfloat v[8][3] = {
			{-LARGURA_CORPO/2.0, -ALTURA_CORPO/2.0, LARGURA_CORPO/3.5},
			{LARGURA_CORPO/2.0, -ALTURA_CORPO/2.0, LARGURA_CORPO/3.5},
			{LARGURA_CORPO/2.0, ALTURA_CORPO/2.0, LARGURA_CORPO/3.5},
			{-LARGURA_CORPO/2.0, ALTURA_CORPO/2.0, LARGURA_CORPO/3.5},
			{-LARGURA_CORPO/2.0, -ALTURA_CORPO/2.0, -LARGURA_CORPO/3.5},
			{LARGURA_CORPO/2.0, -ALTURA_CORPO/2.0, -LARGURA_CORPO/3.5},
			{LARGURA_CORPO/2.0, ALTURA_CORPO/2.0, -LARGURA_CORPO/3.5},
			{-LARGURA_CORPO/2.0, ALTURA_CORPO/2.0, -LARGURA_CORPO/3.5}
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
			{-TAM_PE/6.0, -TAM_PE/8.0, TAM_PE/2.0},
			{TAM_PE/6.0, -TAM_PE/8.0, TAM_PE/2.0},
			{TAM_PE/6.0, TAM_PE/8.0, TAM_PE/2.0},
			{-TAM_PE/6.0, TAM_PE/8.0, TAM_PE/2.0},
			{-TAM_PE/6.0, -TAM_PE/8.0, -TAM_PE/2.0},
			{TAM_PE/6.0, -TAM_PE/8.0, -TAM_PE/2.0},
			{TAM_PE/6.0, TAM_PE/8.0, -TAM_PE/2.0},
			{-TAM_PE/6.0, TAM_PE/8.0, -TAM_PE/2.0}
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
	
	glTranslatef(0.0f, 11.5, 0.0f);
	
	//desenha o corpo
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
		DesenhaCorpo();
		
		//antenas ombros
		glPushMatrix();
			glTranslatef(LARGURA_CORPO/2.5, ALTURA_CORPO/2.0, 0);
			glRotatef(-30, 0, 0, 1);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(Robot->quadric, 0.1, 0.1, ALTURA_CORPO/2.0, 20, 10);
			glutSolidSphere(RAIO_ANTENA, 30, 10);
		glPopMatrix();
		//antenas ombros
		glPushMatrix();
			glTranslatef(-LARGURA_CORPO/2.5, ALTURA_CORPO/2.0, 0);
			glRotatef(30, 0, 0, 1);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(Robot->quadric, 0.1, 0.1, ALTURA_CORPO/2.0, 20, 10);
			glutSolidSphere(RAIO_ANTENA, 30, 10);
		glPopMatrix();
		
	glPopMatrix();
	
	//desenha pescoço
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza	
		glTranslatef(0.0f, 6.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(Robot->quadric, RAIO_PESCOCO, RAIO_PESCOCO, 1.5, 20, 10);
	glPopMatrix();
	
	//desenha cabeça
	glPushMatrix();
		glColor3f(0.5, 0.5, 0.5);
		glTranslatef(0, 8.5, 0);
		glutSolidCube(TAM_CABECA);
		glColor3f(1, 0, 0);
		
		glPushMatrix();
			//glTranslatef(TAM_CABECA/2.0, 0, 0);
			//gluCylinder(Robot->quadric, COMPRIMENTO_ORELHAS/2.0, 0, COMPRIMENTO_ORELHAS, 20, 10);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0, 0, -TAM_CABECA/2.0);
			//olho esquerdo
			glPushMatrix();
				glTranslatef(-TAM_CABECA/6.0, TAM_CABECA/8.0, 0);
				glutSolidSphere(RAIO_OLHOS, 30, 10);
			glPopMatrix();
			
			//olho direito
			glPushMatrix();
				glTranslatef(TAM_CABECA/6.0, TAM_CABECA/8.0, 0);
				glutSolidSphere(RAIO_OLHOS, 30, 10);
			glPopMatrix();
			
			//sorriso
			glPushMatrix();
				glTranslatef(0, -TAM_CABECA/4.0, 0);
				glScalef(LARGURA_SORRISO, ALTURA_SORRISO, 0.25);
				glutSolidCube(1);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();	
	
	//desenha os braços
	///braco direito
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
		glTranslatef(LARGURA_CORPO/2.0, ALTURA_CORPO/2.5, 0.0f);
		gluSphere(Robot->quadric, 0.75, 20, 10);
		glRotatef(90.0f, 1.0f, 0.3f, 0.0f);
		glRotatef(Robot->rot_braco_dir, 1, 0, 0);
		gluCylinder(Robot->quadric, 0.75, 0.75, COMPRIMENTO_BRACO, 20, 10);
		glTranslatef(0, 0, COMPRIMENTO_BRACO);
		
		//cotovelo
		glPushMatrix();
			glTranslatef(0, -GROSSURA_BRACO/4.0, GROSSURA_BRACO/2.0);
			glScalef(1, 1, 0.5);
			gluSphere(Robot->quadric, GROSSURA_BRACO*1.25, 20, 10);
		glPopMatrix();
		
		glRotatef(30, 1, 0, 0);
		gluCylinder(Robot->quadric, GROSSURA_BRACO/1.1, GROSSURA_BRACO/1.5, COMPRIMENTO_BRACO, 20, 10);
	glPopMatrix();
	///braco esquerdo
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
		glTranslatef(-LARGURA_CORPO/2.0, ALTURA_CORPO/2.5, 0.0f);
		gluSphere(Robot->quadric, 0.75, 20, 10);
		glRotatef(90.0f, 1.0f, -0.3f, 0.0f);
		glRotatef(Robot->rot_braco_esq, 1, 0, 0);
		gluCylinder(Robot->quadric, GROSSURA_BRACO, GROSSURA_BRACO, COMPRIMENTO_BRACO, 20, 10);
		glTranslatef(0, 0, COMPRIMENTO_BRACO);
		
		//cotovelo
		glPushMatrix(); 
			glTranslatef(0, -GROSSURA_BRACO/4.0, GROSSURA_BRACO/2.0);
			glScalef(1, 1, 0.5);
			gluSphere(Robot->quadric, GROSSURA_BRACO*1.25, 20, 10);
		glPopMatrix();
		
		glRotatef(30, 1, 0, 0);
		gluCylinder(Robot->quadric, GROSSURA_BRACO/1.1, GROSSURA_BRACO/1.5, COMPRIMENTO_BRACO, 20, 10);
	glPopMatrix();
	
	
	/* desenha os membros inferiores */
	
	///membros direitos
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
		glRotatef(Robot->rot_perna_dir, 1, 0, 0);
		//coxa direita
		glPushMatrix();
			glTranslatef(1.5f, -5.0f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.05f, 0.0f);
			gluSphere(Robot->quadric, 1, 20, 10);
			gluCylinder(Robot->quadric, 1, 0.75, 3.5, 20, 10);
		glPopMatrix();
		//canela direita
		glPushMatrix();
			glTranslatef(1.5f, -8.5f, 0.0f);
			glRotatef(90.0f, 1.0f, -0.05f, 0.0f);
			gluSphere(Robot->quadric, 0.75, 20, 10);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.0, 20, 10);
		glPopMatrix();
		//pé direito
		glPushMatrix();
			glTranslatef(1.5f, -11.75f, -0.5f);
			DesenhaPe();
		glPopMatrix();
	glPopMatrix();
	///membros esquerdos
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
		glRotatef(Robot->rot_perna_esq, 1, 0, 0);
		//coxa esquerda
		glPushMatrix();
			glTranslatef(-1.5f, -5.0f, 0.0f);
			glRotatef(90.0f, 1.0f, -0.05f, 0.0f);
			gluSphere(Robot->quadric, 0.75, 20, 10);
			gluCylinder(Robot->quadric, 1, 0.75, 3.5, 20, 10);
		glPopMatrix();
		//canela esquerda
		glPushMatrix();
			glTranslatef(-1.5f, -8.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.05f, 0.0f);
			gluSphere(Robot->quadric, 0.75, 20, 10);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.0, 20, 10);
		glPopMatrix();
		//pé esquerdo
		glPushMatrix();
			glTranslatef(-1.5f, -11.75f, -0.5f);
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
	if (Robot->movendo_pernas) {
		
	}
	switch(Robot->movendo_pernas) {
		case 1:
		case 2:
			Robot->rot_perna_dir = 45;
			Robot->rot_perna_esq = -30;
			Robot->rot_braco_dir = -30;
			Robot->rot_braco_esq = 30;
			Robot->movendo_pernas++;
			break;
		case 3:
		case 4:
			Robot->rot_perna_dir = -30;
			Robot->rot_perna_esq = 45;
			Robot->rot_braco_dir = 45;
			Robot->rot_braco_esq = -30;
			Robot->movendo_pernas++;
			break;
		case 5:
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
