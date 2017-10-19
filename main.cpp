#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include "robot.h"

#define MAX 400.0
#define FPS 30
#define TAM_BLOCO 20
#define TAM_MAPA 15
#define TAM_MUNDO 1000

GLfloat angulo = 90.0;
GLfloat posX = TAM_BLOCO*1.5, posZ = TAM_BLOCO*1.5;
GLfloat zoomAereo = 0; 

GLfloat rad = 57.2958;

enum camera {PANORAMICA = 1, ATRAS_ROBO = 2} cam;

GLfloat luz_chao[] = { 0.1, 1.0, 0.0, 1.0 };
GLfloat luz_parede[] = { 0.9, 0.8, 0.7, 1.0 };

GLfloat mapa[TAM_MAPA][TAM_MAPA] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1}, 
		{1,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,0,1,0,1,0,0,0,0,0,0,0,0,0,1},
		{0,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

robot *Robot;

void DesenhaParedes() {
	int x, z;
	int x_mun, z_mun;
	
	for (x = 0; x < TAM_MAPA; x++) {
		for (z = 0; z < TAM_MAPA; z++) {
			if (mapa[x][z]) {
				
				x_mun = x * TAM_BLOCO;
				z_mun = z * TAM_BLOCO;
				
				glPushMatrix();
					glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_parede);
					glColor3f(1.0f, 1.0f, 1.0f);
					glTranslatef(x_mun, 5.0f, z_mun);
					glutSolidCube(TAM_BLOCO);
				glPopMatrix();
			}
		}
	}
}

void DesenhaMapa() {
	glColor3f(0.5f, 1.0f, 0.5f);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_chao);
	glBegin(GL_QUADS);
		glVertex3f(-TAM_MUNDO*TAM_BLOCO, 0, -TAM_MUNDO*TAM_BLOCO);
		glVertex3f(-TAM_MUNDO*TAM_BLOCO, 0, TAM_MUNDO*TAM_BLOCO);
		glVertex3f(TAM_MUNDO*TAM_BLOCO, 0, TAM_MUNDO*TAM_BLOCO);
		glVertex3f(TAM_MUNDO*TAM_BLOCO, 0, -TAM_MUNDO*TAM_BLOCO);
	glEnd();
}

void Desenha() {	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (cam == ATRAS_ROBO) {
		gluLookAt(posX - 10, TAM_BLOCO/2 + 10, posZ - 10, 
					posX + TAM_BLOCO*sin(angulo/rad), TAM_BLOCO/2 , posZ + TAM_BLOCO*cos(angulo/rad), 
					0,1,0);
		
	} else {
		gluLookAt(TAM_MAPA*TAM_BLOCO/2.0, TAM_BLOCO*10 + zoomAereo, TAM_MAPA*TAM_BLOCO/2.0, 
					TAM_MAPA*TAM_BLOCO/2.0, -20.0, TAM_MAPA*TAM_BLOCO/2.0, 
					0.0, 0.0, 1.0);
	}
	
	glPushMatrix();
		DesenhaMapa();
	glPopMatrix();
	
	DesenhaParedes();
	
	glTranslatef(posX, TAM_BLOCO/2, posZ);
	glRotatef(angulo, 0, 1, 0);
	DesenhaRobot(Robot);
	
	glutSwapBuffers();
}

void MenuCamera (int op) {
	switch(op) {
		case 1:
			cam = PANORAMICA;
			gluPerspective(60, 800.0/600.0, 1, MAX);
			break;
		case 2:
			cam = ATRAS_ROBO;
			break;
	}
	glutPostRedisplay();
}

void MenuPrincipal(int op){}

void CriaMenu() {
	int menu, submenu1;
	submenu1 = glutCreateMenu(MenuCamera);
	glutAddMenuEntry("Panoramica", 1);
	glutAddMenuEntry("Atras do Robo", 2);
	
	menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Camera",submenu1);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * CallBack que gerencia os cliques do mouse.
 * Abre o menu em tela, caso o usuário clique com o botão direito
 * */
void GerenciaMouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) {
			CriaMenu();
			glutPostRedisplay();
		}
}

void InicializaIluminacao() {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);

	GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_shininess[] = { 5.0 };
	GLfloat light_position[] = { 50.0, 50.0, 50.0, 30.0 };

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	
}


void Inicializa() {
	cam = ATRAS_ROBO;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	InicializaIluminacao();
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
    gluPerspective(45, w/h, 1, MAX);
}

void GerenciaTecladoEspecial(int key, int x, int y) {
	if(key == GLUT_KEY_UP) {
		posX += sin(angulo/rad);
		posZ += cos(angulo/rad);
		Robot->movendo_pernas = 1;
	}
	else if(key == GLUT_KEY_DOWN) {
		posX -= sin(angulo/rad);
		posZ -= cos(angulo/rad);
		Robot->movendo_pernas = 1;
	} 
	else if (key == GLUT_KEY_RIGHT) {
		angulo -= 5;
	} 
	else if (key == GLUT_KEY_LEFT) {
		angulo += 5;
	} else return;
	
	glutPostRedisplay();
	
}

void GerenciaTeclado(unsigned char key, int x, int y) {
	if (cam == PANORAMICA) {
		if (key == '+') {
			zoomAereo -= 10;
		} else if (key == '-') {
			zoomAereo += 10;
		} else return;
	}
	glutPostRedisplay();
}

void Timer(int a) {
	if (Robot->movendo_pernas)
		move_pernas(Robot);
	glutPostRedisplay();
	glutTimerFunc(1000.0/FPS, Timer, 1);
}

/**
 * Função Main
 * */
int main(int argc, char *argv[]) {
	Robot = inicializaRobot();
	//inicialização dos módulos Glut
	glutInit(&argc, argv);
	
	//inicializa os modos de Buffer Duplo, cores RGB e profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    
    //configuração e inicialização da janela
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Labirinto");
	
	//definição da CallBack de desenho
	glutDisplayFunc(Desenha);
	//definição da CallBack de redimensionamento da janela
	glutReshapeFunc(AlteraTamanhoJanela);
	
	Inicializa();
	
	//definição da CallBack de controle do mouse
	glutMouseFunc(GerenciaMouse);
	//definição da CallBack de controle das teclas especiais
	glutSpecialFunc(GerenciaTecladoEspecial);
	//definição da CallBack de controle do teclado (ASCII)
	glutKeyboardFunc(GerenciaTeclado);
	//definição da CallBack de Timer
	glutTimerFunc(1000.0/FPS, Timer, 1);
	
	
	//laço de execução infinito
	glutMainLoop();
	
	liberaRobot(Robot);
	
	return 0;
}
