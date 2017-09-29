#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define MAX 300.0

#define TAM_BLOCO 10
#define TAM_MAPA 15

GLfloat angulo = 90.0;
GLfloat posX = 15, posZ = 15;
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
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

void DesenhaRobo() {
	
}

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
	glColor3f(0.0f, 1.0f, 0.0f);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_chao);
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, TAM_MAPA*TAM_BLOCO);
		glVertex3f(TAM_MAPA*TAM_BLOCO, 0, TAM_MAPA*TAM_BLOCO);
		glVertex3f(TAM_MAPA*TAM_BLOCO, 0, 0);
	glEnd();
}

void Desenha() {	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (cam == ATRAS_ROBO) {
		gluLookAt(posX,TAM_BLOCO/2,posZ, 
					posX + 10*sin(angulo/rad), 5 , posZ + 10*cos(angulo/rad), 
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
	
	if (cam == ATRAS_ROBO) {
		if (key == GLUT_KEY_UP) {
			posX += sin(angulo/rad);
			posZ += cos(angulo/rad); 
			
		} else if (key == GLUT_KEY_DOWN) {
			posX -= sin(angulo/rad);
			posZ -= cos(angulo/rad); 
			
		} else if (key == GLUT_KEY_RIGHT) {
			angulo -= 5;
		}
		else if (key == GLUT_KEY_LEFT) {
			angulo += 5;
		}
		else return;
	}
	else if (cam == PANORAMICA) {
		if (key == GLUT_KEY_UP)
			if (zoomAereo > 0)
				zoomAereo -= 1;
		if (key == GLUT_KEY_DOWN)
			if (zoomAereo < 200)
				zoomAereo += 1;
		else return;
	}
	
	glutPostRedisplay();
	
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
	
	//definição da CallBack de desenho
	glutDisplayFunc(Desenha);
	//definição da CallBack de redimensionamento da janela
	glutReshapeFunc(AlteraTamanhoJanela);
	
	Inicializa();
	
	//definição da CallBack de controle do mouse
	glutMouseFunc(GerenciaMouse);
	
	glutSpecialFunc(GerenciaTecladoEspecial);
	
	//laço de execução infinito
	glutMainLoop();
	
	return 0;
}
