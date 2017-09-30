#include <GL/glut.h>
#define MAX 100
#define TAM_VISUALIZACAO 30

#define TAM_CABECA 4


GLUquadricObj* quadric = gluNewQuadric();

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


void DesenhaRobot() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	gluLookAt(5.0, 5.0, -50.0, 
				0.0, 0.0, 0.0, 
				0.0, 1.0, 0.0);
	
	glColor3f(0.9f, 0.9f, 0.9f);
	
	
	//desenha o corpo
	glPushMatrix();
		DesenhaCorpo();
	glPopMatrix();
	
	//desenha pescoço
	glPushMatrix();
		glTranslatef(0.0f, 6.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 1.5, 20, 10);
	glPopMatrix();
	
	//desenha cabeça
	glPushMatrix();
		glTranslatef(0.0f, 8.5f, 0.0f);
		glutSolidCube(TAM_CABECA);
	glPopMatrix();	
	
	//desenha os braços
	glPushMatrix();
		glTranslatef(3.5f, 4.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.3f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 7.0, 20, 10);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-3.5f, 4.0f, 0.0f);
		glRotatef(90.0f, 1.0f, -0.3f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 7.0, 20, 10);
	glPopMatrix();
	
	
	/* desenha os membros inferiores */
	
	//coxas
	glPushMatrix();
		glTranslatef(1.5f, -5.0f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.05f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 3.5, 20, 10);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.5f, -5.0f, 0.0f);
		glRotatef(90.0f, 1.0f, -0.05f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 3.5, 20, 10);
	glPopMatrix();
	
	//canelas
	glPushMatrix();
		glTranslatef(1.5f, -8.5f, 0.0f);
		glRotatef(90.0f, 1.0f, -0.05f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 3.0, 20, 10);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.5f, -8.5f, 0.0f);
		glRotatef(90.0f, 1.0f, 0.05f, 0.0f);
		gluCylinder(quadric, 0.75, 0.75, 3.0, 20, 10);
	glPopMatrix();
	
	//pés
	glPushMatrix();
		glTranslatef(1.5f, -11.75f, 0.0f);
		DesenhaPe();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-1.5f, -11.75f, 0.0f);
		DesenhaPe();
	glPopMatrix();
	
	glutSwapBuffers();
}


void AlteraTamanhoJanela(GLsizei w, GLsizei h) { 
    // Especifica as dimensões da Viewport
    if (h == 0) h=1;
    
    glViewport(0, 0, w, h);
    //W = w;
    //H = h;                   

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
	// Estabelece a janela de sele��o (left, right, bottom, top)
	//if (w <= h)
		//glOrtho(-TAM_VISUALIZACAO, TAM_VISUALIZACAO, -TAM_VISUALIZACAO, TAM_VISUALIZACAO*h / w, -TAM_VISUALIZACAO, TAM_VISUALIZACAO);
	//else
		//glOrtho(-TAM_VISUALIZACAO, TAM_VISUALIZACAO*w / h, -TAM_VISUALIZACAO, TAM_VISUALIZACAO, -TAM_VISUALIZACAO, TAM_VISUALIZACAO);
		
	gluPerspective(45, w/h, 1, 100);
}

void Inicializa() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

/**
 * Função Main
 * */
int main(int argc, char *argv[]) {
	//inicialização dos módulos Glut
	glutInit(&argc, argv);
	
	//inicializa os modos de Buffer Duplo, cores RGB e profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    
    //configuração e inicialização da janela
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Labirinto");
	
	Inicializa();
	
	//definição da CallBack de desenho
	glutDisplayFunc(DesenhaRobot);
	//definição da CallBack de redimensionamento da janela
	glutReshapeFunc(AlteraTamanhoJanela);
	
	//laço de execução infinito
	glutMainLoop();
	
	return 0;
}
