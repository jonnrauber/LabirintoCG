#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "defs.h"
#include "robot.h"
#include "objeto1.h"
#include "objeto2.h"

GLfloat angulo = 90.0;
GLfloat posX = TAM_BLOCO*1.5, posZ = TAM_BLOCO*1.5;
GLfloat zoomAereo = MAX/2.5;
GLfloat zoomRobot = 26; 

GLfloat rad = 57.2958;
int aumenta = 1;

enum camera {PANORAMICA = 1, ATRAS_ROBO = 2} cam;
enum modo_jogo {MANUAL 	= 1, AUTOMATICO = 2} modo;

GLfloat luz_chao[] = { 0.1, 1.0, 0.0, 1.0 };
GLfloat luz_parede[] = { 0.9, 0.9, 0.8, 1.0 };
GLfloat luz_robot[] = { 0.9, 0.8, 0.7, 1.0 };

GLfloat mapa[TAM_MAPA][TAM_MAPA] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, 
		{1,0,1,0,1,0,1,0,0,0,1,0,0,0,1}, 
		{1,0,1,0,0,0,1,1,1,0,1,1,1,0,1},
		{1,0,0,0,1,0,1,0,1,0,0,0,0,0,1},
		{1,1,1,0,1,0,1,0,0,0,1,0,1,1,1},
		{1,0,0,0,1,0,1,1,1,0,1,0,1,0,0},
		{1,0,1,1,1,0,0,0,1,0,1,0,0,0,1},
		{1,0,1,0,1,1,1,0,0,0,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,1,1,1,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,0,0,1,1,1},
		{1,1,1,0,1,0,1,0,1,1,1,0,0,0,1},
		{1,0,0,0,1,0,1,1,1,0,0,0,1,0,1},
		{1,0,1,1,1,0,0,0,1,1,0,1,1,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
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
					glColor3f(75/255.0, 54/255.0, 1/255.0);
					glTranslatef(x_mun + TAM_BLOCO/2.0, TAM_BLOCO/2.0, z_mun + TAM_BLOCO/2.0);
					glutSolidCube(TAM_BLOCO);
				glPopMatrix();
			}
		}
	}
}

void DesenhaMapa() {
	glColor3f(0.5f, 1.0f, 0.5f);
	
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_chao);
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
		gluLookAt(posX - (TAM_BLOCO+zoomRobot)*sin(angulo/rad), TAM_BLOCO*2, posZ - (TAM_BLOCO+zoomRobot)*cos(angulo/rad), 
					posX, TAM_BLOCO/2 , posZ, 
					0,1,0);
		
	} else {
		gluLookAt(TAM_MAPA*TAM_BLOCO/2.0, TAM_BLOCO*10 + zoomAereo, TAM_MAPA*TAM_BLOCO/2.0, 
					TAM_MAPA*TAM_BLOCO/2.0, -20.0, TAM_MAPA*TAM_BLOCO/2.0, 
					0.0, 0.0, 1.0);
	}
	
	glPushMatrix();
		DesenhaMapa();
	glPopMatrix();
	
	glPushMatrix();
		DesenhaParedes();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(posX, 0, posZ);
		glRotatef(180+angulo, 0, 1, 0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_parede);
		DesenhaRobot(Robot);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(TAM_BLOCO*9.5, 0, TAM_BLOCO*1.5);
		glRotatef(90, 0, 1, 0);
		DesenhaObjeto2();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(TAM_BLOCO*8.5, 0, TAM_BLOCO*12.5);
		glRotatef(90, 0, 1, 0);
		DesenhaObjeto1();
	glPopMatrix();
	
	glutSwapBuffers();
	glFlush();
}

void MenuCamera (int op) {
	switch(op) {
		case 1:
			cam = PANORAMICA;
			gluPerspective(45, 800.0/600.0, -2, MAX);
			break;
		case 2:
			cam = ATRAS_ROBO;
			break;
	}
	glutPostRedisplay();
}

void MenuModo (int op) {
	switch(op) {
		case 1:
			modo = MANUAL;
			break;
		case 2:
			modo = AUTOMATICO;
			break;
	}
	glutPostRedisplay();
}

void MenuPrincipal(int op){}

void CriaMenu() {
	int submenu1, submenu2;
	submenu1 = glutCreateMenu(MenuCamera);
	glutAddMenuEntry("Panoramica", 1);
	glutAddMenuEntry("Atras do Robo", 2);
	submenu2 = glutCreateMenu(MenuModo);
	glutAddMenuEntry("Manual", 1);
	glutAddMenuEntry("Automatico", 2);
	
	glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Camera",submenu1);
	glutAddSubMenu("Modo de Acao",submenu2);
	
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
	glClearColor (0.0, 0.5, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
	
	GLfloat light_position[] = { 50.0, 50.0, 50.0, 30.0 };
	GLfloat light_direction[] = { 0.0, -1.0, 0.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}


void Inicializa() {
	cam = ATRAS_ROBO;
	modo = AUTOMATICO;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	InicializaIluminacao();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) { 
    // Especifica as dimensões da Viewport
    if (h == 0) h=1;
    
    glViewport(0, 0, w, h);       

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, w/h, 1, MAX);
}

void GerenciaTecladoEspecial(int key, int x, int y) {
	if(key == GLUT_KEY_UP && modo == MANUAL) {
		int bloco_mapa_x = (int) ((posX + 7*sin(angulo/rad)) / TAM_BLOCO);
		int bloco_mapa_z = (int) ((posZ + 7*cos(angulo/rad)) / TAM_BLOCO);
		if (mapa[bloco_mapa_x][bloco_mapa_z] != 1) {
			posX += sin(angulo/rad);
			posZ += cos(angulo/rad);
		}
		if (!Robot->movendo_pernas)
			Robot->movendo_pernas = 1;
	}
	if(key == GLUT_KEY_DOWN && modo == MANUAL) {
		int bloco_mapa_x = (int) ((posX - 7*sin(angulo/rad)) / TAM_BLOCO);
		int bloco_mapa_z = (int) ((posZ - 7*cos(angulo/rad)) / TAM_BLOCO);
		if (mapa[bloco_mapa_x][bloco_mapa_z] != 1) {
			posX -= sin(angulo/rad);
			posZ -= cos(angulo/rad);
		}
		if (!Robot->movendo_pernas)
			Robot->movendo_pernas = 1;
	} 
	if (key == GLUT_KEY_RIGHT) {
		angulo -= 5;
		if (Robot->rot_cabeca >= -30)
			Robot->rot_cabeca -= 3;
	} 
	if (key == GLUT_KEY_LEFT) {
		angulo += 5;
		if (Robot->rot_cabeca <= 30)
			Robot->rot_cabeca += 3;
	}
	
	glutPostRedisplay();
	
}

/**
 * Função CallBack que gerencia as interrupções do teclado.
 * Executa ações referentes ao zoom da câmera e troca de perspectiva.
 * */
void GerenciaTeclado(unsigned char key, int x, int y) {
	if (cam == PANORAMICA) {
		if (key == '+') {
			zoomAereo -= 10;
		} else if (key == '-') {
			zoomAereo += 10;
		}
	} else {
		if (key == '+') {
			zoomRobot -= 5;
		} else if (key == '-') {
			zoomRobot += 5;
		}
	}
	
	if (key == 'c' || key == 'C') {
		if (cam == PANORAMICA) {
			cam = ATRAS_ROBO;			
		} else if (cam == ATRAS_ROBO) {
			cam = PANORAMICA;
		}
	}
	
	if (key == 'm' || key == 'M') {
		if (modo == MANUAL) {
			modo = AUTOMATICO;			
		} else if (modo == AUTOMATICO) {
			modo = MANUAL;
		}
	}
	
	glutPostRedisplay();
}

/**
 * Move o robô automaticamente de acordo com o algoritmo DFS (BUSCA EM PROFUNDIDADE).
 * */
void move (void) {
	int bloco_mapa_x = (int) ((posX + 7*sin(angulo/rad)) / TAM_BLOCO);
	int bloco_mapa_z = (int) ((posZ + 7*cos(angulo/rad)) / TAM_BLOCO);
	if (mapa[bloco_mapa_x][bloco_mapa_z] != 1) {
		posX += sin(angulo/rad);
		posZ += cos(angulo/rad);
		if (!Robot->movendo_pernas)
			Robot->movendo_pernas = 1;
	} else {
		angulo += (rand() % 4) * 90;
	}
}

void move_cabeca() {
	if (Robot->rot_cabeca <= -30) {
		aumenta = 1;
	} else if (Robot->rot_cabeca >= 30) {
		aumenta = 0;
	}
	if (aumenta) Robot->rot_cabeca += 3;
	else Robot->rot_cabeca -= 3;
}

/**
 * Função de Timer
 * Se o modo selecionado for "AUTOMATICO", o robô tentará encontrar o caminho para o fim do labirinto sozinho.
 * Caso contrário (modo "MANUAL") somente espera uma ação do usuário.
 * */
void Timer(int a) {
	if (modo == AUTOMATICO)
		move();
	if (Robot->movendo_pernas) {
		move_cabeca();
		move_pernas(Robot);
	}
		
	glutPostRedisplay();
	glutTimerFunc(1000.0/FPS, Timer, 1);
}

/**
 * Função Main
 * */
int main(int argc, char *argv[]) {
	srand(time(NULL));
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
