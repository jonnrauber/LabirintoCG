/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "defs.h"
#include "robot.h"
#include "objeto1.h"
#include "objeto2.h"

GLfloat angulo = 90.0;
GLfloat posX = TAM_BLOCO*1.5, posZ = TAM_BLOCO*1.5;
GLfloat posObj1X = TAM_BLOCO*9.5, posObj1Z = TAM_BLOCO*1.5;
GLfloat posObj2X = TAM_BLOCO*8.5, posObj2Z = TAM_BLOCO*13.5;
GLfloat zoomAereo = MAX;
GLfloat zoomRobot = 26; 
GLfloat SCREEN_WIDTH = 800.0;
GLfloat SCREEN_HEIGHT = 700.0;
GLfloat rad = 57.2958;
int aumenta = 1;
bool menu_inicial = true;
bool menu_help = false;

enum camera {PANORAMICA = 1, ATRAS_ROBO = 2} cam;
enum modo_jogo {MANUAL 	= 1, AUTOMATICO = 2} modo;

GLfloat luz_chao[] = { 0.1, 1.0, 0.0, 1.0 };
GLfloat luz_parede[] = { 0.9, 0.9, 0.8, 1.0 };
GLfloat luz_robot[] = { 0.9, 0.8, 0.7, 1.0 };

/// matriz de ocorrência de blocos no labirinto (paredes)
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

/**
 * Desenha as paredes do labirinto, percorrendo a matriz de ocorrência
 * de blocos (mapa).
 * */
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

/**
 * Desenha o chão do labirinto na cor verde.
 * */
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

/** Desenha texto na tela **/
void DesenhaTexto(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, char *string, int font) {
	int j = strlen(string);
 
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {
		if (font == 0)
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
		else if (font == 1)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

/**
 * Função CallBack de Desenho.
 * */
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
		glTranslatef(posObj1X, 2, posObj1Z);
		glRotatef(90, 0, 1, 0);
		DesenhaObjeto1();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(posObj2X, -2, posObj2Z);
		DesenhaObjeto2();
	glPopMatrix();
	
	/* Desenha o menu inicial na tela até o usuário digitar ENTER */
	if (menu_inicial) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 10.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glDisable(GL_LIGHTING); //desabilita a luz e coloca o texto
			glDisable(GL_DEPTH_TEST);
			
			glColor3f(0, 0, 0);
			glBegin(GL_QUADS);
				glVertex2f(SCREEN_WIDTH/6.0, SCREEN_HEIGHT/4.0);
				glVertex2f(SCREEN_WIDTH/6.0, SCREEN_HEIGHT - SCREEN_HEIGHT/2.5);
				glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH/6.0, SCREEN_HEIGHT - SCREEN_HEIGHT/2.5);
				glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH/6.0, SCREEN_HEIGHT/4.0);
			glEnd();			
			
			char texto1[] = "LABIRINTO - Jefferson A. Coppini, Jonathan T. Rauber";
			DesenhaTexto(SCREEN_WIDTH/5.0, SCREEN_HEIGHT/3.0, 0.9f, 0.9f, 0.9f, texto1, 0);
			char texto_inicial[] = "TECLE ENTER OU CLIQUE COM O MOUSE";
			DesenhaTexto(SCREEN_WIDTH/3.7, SCREEN_HEIGHT/2.3, 1.0f, 1.0f, 1.0f, texto_inicial, 1);
			char texto_help[] = "Tecle H para instrucoes de jogo";
			DesenhaTexto(SCREEN_WIDTH/3.0, SCREEN_HEIGHT/1.8, 1.0f, 1.0f, 1.0f, texto_help, 0);
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	
	if (menu_help) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, -1.0, 10.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			
			glDisable(GL_LIGHTING); //desabilita a luz e coloca o texto
			glDisable(GL_DEPTH_TEST);
			
			glColor3f(0, 0, 0);
			glBegin(GL_QUADS);
				glVertex2f(SCREEN_WIDTH/6.0, SCREEN_HEIGHT/4.0);
				glVertex2f(SCREEN_WIDTH/6.0, SCREEN_HEIGHT - SCREEN_HEIGHT/2.5);
				glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH/6.0, SCREEN_HEIGHT - SCREEN_HEIGHT/2.5);
				glVertex2f(SCREEN_WIDTH - SCREEN_WIDTH/6.0, SCREEN_HEIGHT/4.0);
			glEnd();			
			
			char texto1[] = "AJUDA";
			DesenhaTexto(SCREEN_WIDTH/2.1, SCREEN_HEIGHT/3.0, 1.0f, 1.0f, 1.0f, texto1, 1);
			char texto2[] = "UP, DOWN -> MOVIMENTAM O ROBO";
			DesenhaTexto(SCREEN_WIDTH/5.0, SCREEN_HEIGHT/2.5, 1.0f, 1.0f, 1.0f, texto2, 0);
			char texto3[] = "LEFT, RIGHT -> MUDAM A DIRECAO DO ROBO";
			DesenhaTexto(SCREEN_WIDTH/5.0, SCREEN_HEIGHT/2.3, 1.0f, 1.0f, 1.0f, texto3, 0);
			char texto4[] = "M -> TROCA O MODO DE ACAO";
			DesenhaTexto(SCREEN_WIDTH/5.0, SCREEN_HEIGHT/2.1, 1.0f, 1.0f, 1.0f, texto4, 0);
			char texto5[] = "C -> TROCA A CAMERA";
			DesenhaTexto(SCREEN_WIDTH/5.0, SCREEN_HEIGHT/1.9, 1.0f, 1.0f, 1.0f, texto5, 0);
			char texto6[] = "tecle H para sair";
			DesenhaTexto(SCREEN_WIDTH/2.5, SCREEN_HEIGHT/1.7, 1.0f, 1.0f, 1.0f, texto6, 0);
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);
			
			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	
	glutSwapBuffers();
	glFlush();
}

/** Menu acessado após clique com o botão direito->Câmera **/
void MenuCamera (int op) {
	switch(op) {
		case 1:
			cam = PANORAMICA;
			gluPerspective(45, 800.0/600.0, -2, MAX*2.5);
			break;
		case 2:
			cam = ATRAS_ROBO;
			break;
	}
	glutPostRedisplay();
}

/** Menu acessado após clique com o botão direito->Modo de ação **/
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

/** Menu criado ao clicar com o botão direito do mouse na tela **/
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
	if (button == GLUT_LEFT_BUTTON && menu_inicial) {
		if (state == GLUT_DOWN) {
			menu_inicial = false;
		}
	} else if (button == GLUT_RIGHT_BUTTON && !menu_inicial) {
    if (state == GLUT_DOWN) {
			CriaMenu();
		}
	}
	glutPostRedisplay();
}

/** Inicializa renderização de sombra e iluminação **/
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

/** Inicializa teste de Z-Buffer, modo de câmera e de ação **/
void Inicializa() {
	cam = ATRAS_ROBO;
	modo = MANUAL;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	InicializaIluminacao();
}

/** 
 * Função CallBack de redimensionamento de tela 
**/
void AlteraTamanhoJanela(GLsizei w, GLsizei h) { 
    // Especifica as dimensões da Viewport
    if (h == 0) h=1;
    SCREEN_HEIGHT = h;
    SCREEN_WIDTH = w;
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);       

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, SCREEN_WIDTH/SCREEN_HEIGHT, 1, MAX*2.5);
}

/** Retorna true se o movimento do robô não o fará colidir com um bloco
 * ou um objeto, e retorna false caso colida. */
bool verifica_colisao_objetos (int bloco_mapa_x, int bloco_mapa_z) {
	int bloco_objeto1_x = (int) (posObj1X / TAM_BLOCO);
	int bloco_objeto1_z = (int) (posObj1Z / TAM_BLOCO);
	int bloco_objeto2_x = (int) (posObj2X / TAM_BLOCO);
	int bloco_objeto2_z = (int) (posObj2Z / TAM_BLOCO);
	
	if ((bloco_mapa_x == bloco_objeto1_x && bloco_mapa_z == bloco_objeto1_z) ||
		(bloco_mapa_x == bloco_objeto2_x && bloco_mapa_z == bloco_objeto2_z) ||
		(bloco_mapa_x == bloco_objeto1_x && bloco_mapa_z == bloco_objeto1_z+1)) {
		return false;
	}
		
	return true;
}

/** 
 * Função CallBack que monitora as interrupções de teclas especiais 
**/
void GerenciaTecladoEspecial(int key, int x, int y) {
	if(!menu_inicial) {
		/* Se já passou do menu inicial */
		if(key == GLUT_KEY_UP && modo == MANUAL) {
			//anda para frente no modo manual
			int bloco_mapa_x = (int) ((posX + 7*sin(angulo/rad)) / TAM_BLOCO);
			int bloco_mapa_z = (int) ((posZ + 7*cos(angulo/rad)) / TAM_BLOCO);
			if (mapa[bloco_mapa_x][bloco_mapa_z] != 1 && verifica_colisao_objetos(bloco_mapa_x, bloco_mapa_z)) {
				posX += sin(angulo/rad);
				posZ += cos(angulo/rad);
			}
			if (!Robot->movendo_pernas)
				Robot->movendo_pernas = 1;
		}
		if(key == GLUT_KEY_DOWN && modo == MANUAL) {
			//anda para trás no modo manual
			int bloco_mapa_x = (int) ((posX - 7*sin(angulo/rad)) / TAM_BLOCO);
			int bloco_mapa_z = (int) ((posZ - 7*cos(angulo/rad)) / TAM_BLOCO);
			if (mapa[bloco_mapa_x][bloco_mapa_z] != 1 && verifica_colisao_objetos(bloco_mapa_x, bloco_mapa_z)) {
				posX -= sin(angulo/rad);
				posZ -= cos(angulo/rad);
			}
			if (!Robot->movendo_pernas)
				Robot->movendo_pernas = 1;
		} 
		if (key == GLUT_KEY_RIGHT) {
			//muda a direção para 5 graus à direita
			angulo -= 5;
			if (Robot->rot_cabeca >= -30)
				Robot->rot_cabeca -= 3;
		} 
		if (key == GLUT_KEY_LEFT) {
			//muda a direção para 5 graus à esquerda
			angulo += 5;
			if (Robot->rot_cabeca <= 30)
				Robot->rot_cabeca += 3;
		}
		
	}
	
	glutPostRedisplay();
	
}

/**
 * Função CallBack que gerencia as interrupções do teclado.
 * Executa ações referentes ao zoom da câmera e troca de perspectiva.
 * */
void GerenciaTeclado(unsigned char key, int x, int y) {
	if (!menu_inicial) {
		if (cam == PANORAMICA) {
			//Controla a proximidade da câmera aérea
			if (key == '+') {
				if (zoomAereo > 10)
					zoomAereo -= 10;
			} else if (key == '-') {
				if (zoomAereo + 10 <= MAX)
					zoomAereo += 10;
			}
		} else {
			//Controla a proximidade da câmera em 3a. pessoa
			if (key == '+') {
				if(zoomRobot > -MAX)
					zoomRobot -= 5;
			} else if (key == '-') {
				if(zoomRobot < MAX)
					zoomRobot += 5;
			}
		}
		if (key == 'c' || key == 'C') {
			//Troca o modo de câmera (toggle entre panorâmica e 3a. pessoa)
			if (cam == PANORAMICA) {
				cam = ATRAS_ROBO;			
			} else if (cam == ATRAS_ROBO) {
				cam = PANORAMICA;
			}
		}
		if (key == 'm' || key == 'M') {
			/* Troca o modo de ação, ou seja, se o robô se moverá automaticamente
			 * ou se é necessária controlar através do teclado. */
			if (modo == MANUAL) {
				modo = AUTOMATICO;			
			} else if (modo == AUTOMATICO) {
				modo = MANUAL;
			}
		}
	} else {
		if (key == 13) {
			// Se estiver no menu inicial e for pressionada a tecla ENTER, libera o labirinto
			menu_inicial = false;
		}
	}
	
	if (key == 'h' || key == 'H') {
		menu_help = !menu_help;
	}
	
	glutPostRedisplay();
}

/**
 * Move o robô automaticamente, mudando de direção aleatoriamente após uma colisão.
 * */
void move (void) {
	//Calcula para qual bloco o robô vai após o movimento para frente
	int bloco_mapa_x = (int) ((posX + 7*sin(angulo/rad)) / TAM_BLOCO);
	int bloco_mapa_z = (int) ((posZ + 7*cos(angulo/rad)) / TAM_BLOCO);
	
	if (mapa[bloco_mapa_x][bloco_mapa_z] != 1 && verifica_colisao_objetos(bloco_mapa_x, bloco_mapa_z)) {
		/* Se não colidir com algum bloco de parede ou com algum objeto,
		 * faz o movimento do robô para frente. */
		posX += sin(angulo/rad);
		posZ += cos(angulo/rad);
		if (!Robot->movendo_pernas) // Inicia o movimento das pernas e braços do robô
			Robot->movendo_pernas = 1;
	} else {
		// Caso colidiu com um bloco, troca aleatoriamente para uma outra direção
		angulo += (rand() % 4) * 90;
	}
}

/** 
 * Controla o ângulo de rotação horizontal da cabeça do robô.
 * Faz uma rotação de 60 graus, entre -30 e 30 graus.
 * Incrementa a rotação de 3 em 3 graus por frame.
 * */
void move_cabeca (void) {
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
 * ATENÇÃO: para trocar a taxa de milissegundos ou FPS, alterar a constante FPS no arquivo defs.h
 * VALOR PADRÃO: 30fps (33ms).
 * Se o modo selecionado for "AUTOMATICO", o robô tentará encontrar o caminho para o fim do labirinto sozinho.
 * Caso contrário (modo "MANUAL") somente espera uma ação do usuário.
 * */
void Timer(int a) {
	if (!menu_inicial) {
		if (modo == AUTOMATICO)
			move();
		if (Robot->movendo_pernas) {
			move_cabeca();
			move_pernas(Robot);
		}
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
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
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
