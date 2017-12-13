/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#include "defs.h"
#include "robot.h"

GLfloat luz_robo_ambiente[4] = {0.9f, 0.9f, 0.9f, 1.0f};

void DesenhaPe() {
	struct vetor Normal;
	glColor3f(0, 0, 1);
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
		Normal = calculaNormal(v[0], v[1], v[2], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[2]); glVertex3fv(v[3]);

		Normal = calculaNormal(v[4], v[5], v[6], v[7]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[4]); glVertex3fv(v[5]); glVertex3fv(v[6]); glVertex3fv(v[7]);

		Normal = calculaNormal(v[1], v[5], v[6], v[2]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[1]); glVertex3fv(v[5]); glVertex3fv(v[6]); glVertex3fv(v[2]);

		Normal = calculaNormal(v[0], v[4], v[7], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[0]); glVertex3fv(v[4]); glVertex3fv(v[7]); glVertex3fv(v[3]);

		Normal = calculaNormal(v[2], v[6], v[7], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[2]); glVertex3fv(v[6]); glVertex3fv(v[7]); glVertex3fv(v[3]);

		Normal = calculaNormal(v[0], v[1], v[5], v[4]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[5]); glVertex3fv(v[4]);
	glEnd();
}

void esfera(GLfloat *centro, GLfloat radius, GLfloat num, GLint texture) {
	GLfloat c, x, y, z, s1, s2, t1, t2;
	GLfloat phi1, theta1, phi2, theta2;
	GLfloat senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
					 passo;

	GLfloat ctex_fx = 1, ctex_fy = 1;
	GLfloat ctex_ix = 0, ctex_iy = 0;

	GLfloat dx = ctex_fx - ctex_ix;
	GLfloat dy = ctex_fy - ctex_iy;
	c = pi / 180;
	passo = 180 / num * c;

	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	phi1 = 0;
	senphi1 = sin(phi1);
	cosphi1 = cos(phi1);
	int i,j;
	for (i=0; i < num; i++) {
		phi2 = phi1 + passo;
		senphi2 = sin(phi2);
		cosphi2 = cos(phi2);
		theta1 = 0;
		sentheta1 = sin(theta1);
		costheta1 = cos(theta1);
		for (j=0; j < 2 * num; j++) {
			theta2 = theta1 + passo;
			sentheta2 = sin(theta2);
			costheta2 = cos(theta2);
			s1 = ctex_ix + theta1 / (2 * pi) * dx;
			s2 = ctex_ix + theta2 / (2 * pi) * dx;
			t1 = ctex_iy + phi1 / pi * dy;
			t2 = ctex_iy + phi2 / pi * dy;
			// Faz x <- -y, y <- x e  z <- -z  o que equivale a uma rotação de 90
			// sobre z e 180 sobre x
			x = centro[0] + radius * senphi1 * costheta1;
			y = centro[1] + radius * senphi1 * sentheta1;
			z = centro[2] + radius * cosphi1;
			glTexCoord2f(s1, t1);
			glVertex3d(-y, x, -z);
			x = centro[0] + radius * senphi2 * costheta1;
			y = centro[1] + radius * senphi2 * sentheta1;
			z = centro[2] + radius * cosphi2;
			glTexCoord2f(s1, t2);
			glVertex3d(-y,x, -z);
			x = centro[0] + radius * senphi2 * costheta2;
			y = centro[1] + radius * senphi2 * sentheta2;
			z = centro[2] + radius * cosphi2;
			glTexCoord2f(s2, t2);
			glVertex3d(-y,x, -z);
			x = centro[0] + radius * senphi1 * costheta2;
			y = centro[1] + radius * senphi1 * sentheta2;
			z = centro[2] + radius * cosphi1;
			glTexCoord2f(s2, t1);
			glVertex3d(-y,x, -z);
			theta1 = theta2;
			sentheta1 = sentheta2;
			costheta1 = costheta2;
		}
		phi1 = phi2;
		senphi1 = senphi2;
		cosphi1 = cosphi2;
	}
	glEnd();
}



void DesenhaRobot(robot *Robot) {
	glTranslatef(0.0f, 11.5, 0.0f);
	glDisable(GL_COLOR_MATERIAL);
	//desenha o corpo
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_robo_ambiente);
		glPushMatrix();
			glScalef(LARGURA_CORPO, ALTURA_CORPO, LARGURA_CORPO/1.75);
			glutSolidCube(1);
		glPopMatrix();

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
		glTranslatef(0.0f, 6.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(Robot->quadric, RAIO_PESCOCO, RAIO_PESCOCO, 1.5, 20, 10);
	glPopMatrix();

	//desenha cabeça
	glPushMatrix();
		//glColor3f(0.5, 0.5, 0.5);
		glTranslatef(0, 8.5, 0);
		glRotatef(Robot->rot_cabeca, 0, 1, 0);
		GLfloat centroCabeca[3] = {0, 0, 0};
		glPushMatrix();
			glScalef(1, 1.5, 1);
			esfera(centroCabeca, TAM_CABECA/2.0, 100, 3);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 0, -TAM_CABECA/2.3);
			//olho esquerdo
			glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslatef(-TAM_CABECA/6.0, -0.2, 0);
				glutSolidSphere(RAIO_OLHOS/1.5, 30, 10);
			glPopMatrix();

			//olho direito
			glPushMatrix();
				glColor3f(1, 0, 0);
				glTranslatef(TAM_CABECA/6.0, -0.2, 0);
				glutSolidSphere(RAIO_OLHOS/1.5, 30, 10);
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

		glPushMatrix();
			glTranslatef(0, 0, COMPRIMENTO_BRACO);
			glColor3f(0, 0, 1);
			glScalef(1, 0.75, 0.75);
			gluSphere(Robot->quadric, GROSSURA_BRACO/1.1*1.25, 20, 10);
		glPopMatrix();
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

		glPushMatrix();
			glTranslatef(0, 0, COMPRIMENTO_BRACO);
			glColor3f(0, 0, 1);
			glScalef(1, 0.75, 0.75);
			gluSphere(Robot->quadric, GROSSURA_BRACO/1.1*1.25, 20, 10);
		glPopMatrix();
	glPopMatrix();

	/* desenha os membros inferiores */
	///membros direitos
	glPushMatrix();
		glColor3f(0.9f, 0.9f, 0.9f); //cor cinza
		glRotatef(Robot->rot_perna_dir, 1, 0, 0);
		//coxa direita
		glPushMatrix();
			glTranslatef(1.5f, -5.0f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.02f, 0.0f);
			gluSphere(Robot->quadric, 1, 20, 10);
			gluCylinder(Robot->quadric, 1, 0.75, 3.5, 20, 10);
		glPopMatrix();
		//joelho direito
		glPushMatrix();
			glTranslatef(1.5, -8.5, 0);
			glScalef(1, 0.75, 1);
			gluSphere(Robot->quadric, 1, 20, 10);
		glPopMatrix();
		//canela direita
		glPushMatrix();
			glTranslatef(1.5f, -8.5f, 0.0f);
			glRotatef(90.0f, 1.0f, -0.02f, 0.0f);
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
			glRotatef(90.0f, 1.0f, -0.02f, 0.0f);
			gluSphere(Robot->quadric, 0.75, 20, 10);
			gluCylinder(Robot->quadric, 1, 0.75, 3.5, 20, 10);
		glPopMatrix();
		//joelho esquerdo
		glPushMatrix();
			glTranslatef(-1.5, -8.5, 0);
			glScalef(1, 0.75, 1);
			gluSphere(Robot->quadric, 1, 20, 10);
		glPopMatrix();
		//canela esquerda
		glPushMatrix();
			glTranslatef(-1.5f, -8.5f, 0.0f);
			glRotatef(90.0f, 1.0f, 0.02f, 0.0f);
			gluSphere(Robot->quadric, 0.75, 20, 10);
			gluCylinder(Robot->quadric, 0.75, 0.75, 3.0, 20, 10);
		glPopMatrix();
		//pé esquerdo
		glPushMatrix();
			glTranslatef(-1.5f, -11.75f, -0.5f);
			DesenhaPe();
		glPopMatrix();
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
}

robot* inicializaRobot() {
	robot* Robot = (robot *)malloc(sizeof(robot *));
	Robot->rot_perna_dir = 0;
	Robot->rot_perna_esq = 0;
	Robot->rot_braco_dir = 0;
	Robot->rot_braco_esq = 0;
	Robot->rot_cabeca = 0;
	Robot->movendo_pernas = 0;
	Robot->quadric = gluNewQuadric();

	return Robot;
}

void liberaRobot(robot *Robot) {
	free(Robot);
}

/**
 * Função que executa o movimento das pernas e dos bracos do robô
 * */
void move_pernas(robot *Robot) {
	if (Robot->movendo_pernas) {
		if (Robot->movendo_pernas >= 1 && Robot->movendo_pernas <= 5) {
			Robot->rot_perna_dir = Robot->movendo_pernas * 9;
			Robot->rot_braco_esq = Robot->rot_perna_dir;
			Robot->rot_perna_esq = Robot->movendo_pernas * -6;
			Robot->rot_braco_dir = Robot->rot_perna_esq;
		} else if (Robot->movendo_pernas >= 6 && Robot->movendo_pernas <= 10) {
			Robot->rot_perna_dir = (Robot->movendo_pernas - 5) * -6;
			Robot->rot_braco_esq = Robot->rot_perna_dir;
			Robot->rot_perna_esq = (Robot->movendo_pernas - 5) * 9;
			Robot->rot_braco_dir = Robot->rot_perna_esq;
		} else if (Robot->movendo_pernas == 11) {
			Robot->rot_perna_dir = 0;
			Robot->rot_perna_esq = 0;
			Robot->rot_braco_dir = 0;
			Robot->rot_braco_esq = 0;
		} else {
			Robot->movendo_pernas = -1;
		}
		Robot->movendo_pernas++;
	}
	glutPostRedisplay();
}
