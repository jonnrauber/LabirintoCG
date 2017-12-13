/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#include "defs.h"
#include "robot.h"

GLfloat angulo = 180.0;
GLfloat anguloObj1 = 180.0;
GLfloat anguloObj2 = 270.0;
GLfloat anguloObj3 = 270.0;
GLfloat anguloParque = 310.0;
GLfloat movimentoBalanco = 0.1; bool movBalanco = true;
GLfloat movimentoBola = 85.0; bool movBola = false;
GLfloat posX = TAM_BLOCO*2, posZ = TAM_BLOCO*1.5;
GLfloat posObj1X = TAM_BLOCO*9.5, posObj1Z = TAM_BLOCO*1.5;
GLfloat posObj2X = TAM_BLOCO*8.5, posObj2Z = TAM_BLOCO*13.5;
GLfloat posObj3X = TAM_BLOCO*1.5, posObj3Z = TAM_BLOCO*3.5;
GLfloat posParqueX = TAM_BLOCO*3, posParqueZ = -TAM_BLOCO*2;
GLfloat zoomAereo = MAX;
GLfloat zoomRobot = 26;
GLfloat zoomObj1 = TAM_BLOCO*3+1;
GLfloat zoomObj2 = TAM_BLOCO*2+1;
GLfloat zoomObj3 = TAM_BLOCO*3+1;
GLfloat zoomParque = TAM_BLOCO*4+1;
GLfloat SCREEN_WIDTH = 800.0;
GLfloat SCREEN_HEIGHT = 700.0;
int aumenta = 1;
bool menu_inicial = true;
bool menu_help = false;
bool menu_venceu = false;

enum camera {PANORAMICA = 1, ATRAS_ROBO = 2, OBJETO1 = 3, OBJETO2 = 4, OBJETO3 = 5, PARQUE = 6} cam;
enum modo_jogo {MANUAL 	= 1, AUTOMATICO = 2} modo;

///textura
GLuint m_texturaParede, m_texturaChao, m_texturaFace, m_texturaBola, m_textureAreia;
///iluminação chão
GLfloat luz_chao[4] 						= {0.5f, .7f, 0.5f, 1.0f};
GLfloat luz_janela[4] 					= {0.0f, 0.5f, 1.0f, 0.3f};
GLfloat luz_paredes[4]					= {0.8f, 0.5f, 0.3f, 1.0f};
GLfloat luz_bola[4]							= {0.5f, 0.5f, 1.0f, 1.0f};

int bloco_final_x = 5, bloco_final_z = 14;
/// matriz de ocorrência de blocos no labirinto (paredes)
GLfloat mapa[TAM_MAPA][TAM_MAPA] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{2,0,0,0,1,0,1,0,0,0,1,0,0,0,1},
		{2,0,0,0,0,0,1,1,1,0,1,1,1,0,1},
		{2,0,1,1,1,0,1,0,1,0,0,0,0,0,1},
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

//parque
GLfloat escorregador[4][4][3] = {
  {{-4, 0, -3}, {-3, 2, -3}, {2, 0, -3}, {10, 16, -3}},
	{{-4, -1, -3}, {-2, 2-4, -3}, {2, 0-4, -1}, {10, 16-2, -3}},
  {{-4, -1, 3}, {-2, 2-4, 3}, {2, 0-4, 3}, {10, 16-2, 3}},
	{{-4, 0, 3}, {-3, 2, 3}, {2, 0, 3}, {10, 16, 3}}
};

GLUquadric* quad = gluNewQuadric();
GLfloat raioBalanco = 0.5f;
GLfloat alturaBalanco = TAM_BLOCO*1.5;
GLfloat raioEscada = 0.4f;
GLfloat alturaEscada = TAM_BLOCO*0.88;
GLfloat anguloMaxBalanco = 45;
GLfloat anguloMinBola = 55;
GLfloat anguloMaxBola = 85;

struct vetor calculaNormal (GLfloat *A, GLfloat *B, GLfloat *C, GLfloat *D) {
	struct vetor V1;
	V1.x = C[0]-A[0]; V1.y = C[1]-A[1]; V1.z = C[2]-A[2];
	struct vetor V2;
	V2.x = D[0]-B[0]; V2.y = D[1]-B[1]; V2.z = D[2]-B[2];
	struct vetor Normal;
	Normal.x = V1.y * V2.z - V1.z * V2.y;
	Normal.y = V2.x * V1.z - V2.z * V1.x;
	Normal.z = V1.x * V2.y - V1.y * V2.x;
	return Normal;
}

void drawSurface(GLfloat surfaceVec[10][4][3], int x, int y, int z) {
		int u, v;
		GLint un = 30;
		GLint vn = 30;

	    glMap2f(GL_MAP2_VERTEX_3, 0, 1, y*z, x, 0, 1, z, y, &surfaceVec[0][0][0]);
	    glEnable(GL_MAP2_VERTEX_3);
	    glBegin(GL_QUADS);
	    for (u = 0; u < un; u++) {
	        for (v = 0; v < vn; v++) {
	            glEvalCoord2f((GLfloat)v / vn, (GLfloat)(u+1) / un);
	            glEvalCoord2f((GLfloat)(v+1) / vn, (GLfloat)(u+1) / un);
	            glEvalCoord2f((GLfloat)(v+1) / vn, (GLfloat)u / un);
	            glEvalCoord2f((GLfloat)v / vn, (GLfloat)u / un);
	        }
	    }
	    glEnd();
}

void DesenhaParque(void){
	/* Caixa de Areia */
	glPushMatrix();
		GLfloat v[4][3] = { {-TAM_BLOCO, 0, -TAM_BLOCO*2}, {-TAM_BLOCO, 0, TAM_BLOCO*2},
												{TAM_BLOCO*1.5, 0, TAM_BLOCO*2}, {TAM_BLOCO*1.5, 0, -TAM_BLOCO*2} };
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureAreia);

		glBegin(GL_QUADS);
			struct vetor Normal = calculaNormal(v[0], v[1], v[2], v[3]);
			glNormal3f(Normal.x, Normal.y, Normal.z);
			glTexCoord2f(0, 0); 			glVertex3fv(v[0]);
			glTexCoord2f(0, 2.0f);  	glVertex3fv(v[1]);
			glTexCoord2f(2.0f, 2.0f);	glVertex3fv(v[2]);
			glTexCoord2f(2.0f, 0);		glVertex3fv(v[3]);
		glEnd();

		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

  /* Escorregador */
  glPushMatrix();
    glTranslatef(0.f, 0.f, TAM_BLOCO/4.0);
		glScalef(1.f, 1.25f, 1.1f);
    glPushMatrix(); //escada escorregador
      glTranslatef(13.f, 0.f, 0.f);
			glRotatef(10.f, 0.f, 0.f, 1.f);
			glPushMatrix();
				glTranslatef(0.f, 0.f, -2.2f);
	      glRotatef(-90.f, 1.f, 0.f, 0.f);
				gluCylinder(quad, raioEscada, raioEscada, alturaEscada, 10, 30);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.f, 0.f, 2.5f);
	      glRotatef(-90.f, 1.f, 0.f, 0.f);
				gluCylinder(quad, raioEscada, raioEscada, alturaEscada, 10, 30);
			glPopMatrix();
			for (int i = 3; i < 18; i += 3) {
				glPushMatrix();
					glTranslatef(0.f, i, -2.35f);
					gluCylinder(quad, raioEscada, raioEscada, 4.7f, 10, 30);
				glPopMatrix();
			}
    glPopMatrix();
		glPushMatrix(); //suporte menor escorregador
			glTranslatef(3.f, 0.f, 0.f);
			glRotatef(25, 0.f, 0.f, 1.f);
			glPushMatrix();
				glTranslatef(0.f, 0.f, -1.4);
	      glRotatef(-90.f, 1.f, 0.f, 0.f);
				gluCylinder(quad, raioEscada, raioEscada*0.8, alturaEscada*0.2, 10, 30);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.f, 0.f, 1.9);
	      glRotatef(-90.f, 1.f, 0.f, 0.f);
				gluCylinder(quad, raioEscada, raioEscada*0.8, alturaEscada*0.2, 10, 30);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.f, alturaEscada*0.15, -1.4f);
				gluCylinder(quad, raioEscada*0.5, raioEscada*0.5, 3.3f, 10, 30);
			glPopMatrix();
		glPopMatrix();

		glTranslatef(0.f, 2.f, 0.f);
    glColor3f(.5f, .2f, .5f);
  	drawSurface(escorregador, 4, 4, 3);
  glPopMatrix();

  /* Balanço */
	glPushMatrix();
		glTranslatef(0.f, 0.f, -TAM_BLOCO);
	  glPushMatrix();
	    glRotatef(15.0f, .0f, .0f, -1.0f);

	    glColor3f(0.f, 1.f, .5f); //cor do suporte do balanço
	    glPushMatrix();
	      glTranslatef(0, -3, TAM_BLOCO/2.0);
	      glRotatef(-90.0f, 1.0f, .0f, .0f);
	      gluCylinder(quad, raioBalanco, raioBalanco, alturaBalanco, 10, 30);
	    glPopMatrix();

	    glPushMatrix();
	      glTranslatef(0, -3, -TAM_BLOCO/2.0);
	      glRotatef(-90.0f, 1.0f, .0f, .0f);
	      gluCylinder(quad, raioBalanco, raioBalanco, alturaBalanco, 10, 30);
	    glPopMatrix();

	    glPushMatrix();
	      glTranslatef(0, -3+alturaBalanco, TAM_BLOCO/2.0);
	      gluSphere(quad, raioBalanco, 10, 30);
	    glPopMatrix();

	    glPushMatrix();
	      glTranslatef(0, -3+alturaBalanco, -TAM_BLOCO/2.0);
	      gluSphere(quad, raioBalanco, 10, 30);
	    glPopMatrix();

	    glPushMatrix();
	      glTranslatef(0, -3+alturaBalanco, -TAM_BLOCO/2.0);
	      gluCylinder(quad, raioBalanco, raioBalanco, TAM_BLOCO, 10, 30);
	    glPopMatrix();
	  glPopMatrix();

	  glPushMatrix();
	    glTranslatef(14.0f, .0f, .0f);
	    glRotatef(15.0f, .0f, .0f, 1.0f);
	    glPushMatrix();
	      glTranslatef(0.0f, -3, TAM_BLOCO/2.0);
	      glRotatef(-90.0f, 1.0f, .0f, .0f);
	      gluCylinder(quad, raioBalanco, raioBalanco, alturaBalanco, 10, 30);
	    glPopMatrix();

	    glPushMatrix();
	      glTranslatef(0.0f, -3, -TAM_BLOCO/2.0);
	      glRotatef(-90.0f, 1.0f, .0f, .0f);
	      gluCylinder(quad, raioBalanco, raioBalanco, alturaBalanco, 10, 30);
	    glPopMatrix();
	  glPopMatrix();

	  glPushMatrix();
	    glTranslatef(7.0f, alturaBalanco - alturaBalanco*sin(0.13f), .0f);
	    glRotatef(movimentoBalanco, .0f, .0f, 1.0f);
	    glPushMatrix(); //corda
	      glColor3f(216.f/255.f, 175.f/255.f, 86.f/255.f);
	      glRotatef(90.0f, 1.0f, .0f, .0f);
	      gluCylinder(quad, raioBalanco/3.0f, raioBalanco/3.0f, alturaBalanco*0.55, 10, 30);
	    glPopMatrix();

	    glPushMatrix(); //pneu
	      glColor3i(0, 0, 0);
	      glTranslatef(0.0f, -alturaBalanco/1.5f, 0.f);
	      glRotatef(90.0f, .0f, 1.0f, 0.0f);
	      glutSolidTorus(1.5, 3.5, 10, 30);
	    glPopMatrix();
	  glPopMatrix();
	glPopMatrix();

	/* Espiribol */
	glPushMatrix();
		glTranslatef(0.f, 0.f, TAM_BLOCO);
		glPushMatrix();
			glRotatef(-90.0f, 1.0f, .0f, .0f);
			glColor3f(0.9f,0.9f,0.9f);
			gluCylinder(quad, raioBalanco, raioBalanco, alturaBalanco, 10, 30);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(raioBalanco*0.9, alturaBalanco, raioBalanco*0.9);
			glRotatef(movimentoBola, 1.0f, .0f, .0f);
			glColor3f(216.f/255.f, 175.f/255.f, 86.f/255.f);
			gluCylinder(quad, .1f, .1f, alturaBalanco*0.6, 10, 30);
			glTranslatef(0.f, 0.f, alturaBalanco*0.6);
			GLfloat centroBola[3] = {0.f, 0.f, 0.f};

			glDisable(GL_COLOR_MATERIAL);
			glEnable(GL_TEXTURE_2D);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_bola);
			esfera(centroBola, 1.5f, 100, 4);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_COLOR_MATERIAL);
		glPopMatrix();
	glPopMatrix();

  if (movimentoBalanco >= anguloMaxBalanco)
    movBalanco = false;
  else if (movimentoBalanco <= -anguloMaxBalanco)
    movBalanco = true;
	if (movimentoBola >= anguloMaxBola)
    movBola = false;
  else if (movimentoBola <= anguloMinBola)
    movBola = true;
}

void DesenhaCuboTextura(GLfloat l, GLfloat c, GLfloat h, GLuint textura) {
	struct vetor Normal;
	GLfloat v[8][3] = {
			{-l, -h, c}, {l, -h, c}, {l, h*1.5f, c},
			{-l, h*1.5f, c}, {-l, -h, -c}, {l, -h, -c},
			{l, h*1.5f, -c}, {-l, h*1.5f, -c}
		};

	GLfloat coordTextura = 1.0f;

	glBindTexture(GL_TEXTURE_2D, textura);
	glBegin(GL_QUADS);
		Normal = calculaNormal(v[0], v[1], v[2], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0); 											glVertex3fv(v[0]);
		glTexCoord2f(0, coordTextura); 						glVertex3fv(v[1]);
		glTexCoord2f(coordTextura, coordTextura); glVertex3fv(v[2]);
		glTexCoord2f(coordTextura, 0); 						glVertex3fv(v[3]);

		Normal = calculaNormal(v[4], v[5], v[6], v[7]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0);												glVertex3fv(v[4]);
		glTexCoord2f(0, coordTextura); 						glVertex3fv(v[5]);
		glTexCoord2f(coordTextura, coordTextura); glVertex3fv(v[6]);
		glTexCoord2f(coordTextura, 0);						glVertex3fv(v[7]);

		Normal = calculaNormal(v[1], v[5], v[6], v[2]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0);												glVertex3fv(v[1]);
		glTexCoord2f(0, coordTextura); 						glVertex3fv(v[5]);
		glTexCoord2f(coordTextura, coordTextura); glVertex3fv(v[6]);
		glTexCoord2f(coordTextura, 0);						glVertex3fv(v[2]);

		Normal = calculaNormal(v[0], v[4], v[7], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0);												glVertex3fv(v[0]);
		glTexCoord2f(0, coordTextura);						glVertex3fv(v[4]);
		glTexCoord2f(coordTextura, coordTextura); glVertex3fv(v[7]);
		glTexCoord2f(coordTextura, 0);						glVertex3fv(v[3]);

		Normal = calculaNormal(v[2], v[6], v[7], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0); 											glVertex3fv(v[2]);
		glTexCoord2f(0, coordTextura);						glVertex3fv(v[6]);
		glTexCoord2f(coordTextura, coordTextura);	glVertex3fv(v[7]);
		glTexCoord2f(coordTextura, 0);						glVertex3fv(v[3]);

		Normal = calculaNormal(v[0], v[1], v[5], v[4]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0);												glVertex3fv(v[0]);
		glTexCoord2f(0, coordTextura);						glVertex3fv(v[1]);
		glTexCoord2f(coordTextura, coordTextura);	glVertex3fv(v[5]);
		glTexCoord2f(coordTextura, 0);						glVertex3fv(v[4]);
	glEnd();
}

/**
 * Desenha as paredes do labirinto, percorrendo a matriz de ocorrência
 * de blocos (mapa).
 * */
void DesenhaParedes(void) {
	int x, z, x_mun, z_mun;

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_paredes);
	for (x = 0; x < TAM_MAPA; x++)
		for (z = 0; z < TAM_MAPA; z++)
			if (mapa[x][z] == 1) {
				x_mun = x * TAM_BLOCO;
				z_mun = z * TAM_BLOCO;

				glPushMatrix();
					glTranslatef(x_mun + TAM_BLOCO/2.0, TAM_BLOCO/2.0, z_mun + TAM_BLOCO/2.0);
					DesenhaCuboTextura(TAM_BLOCO/2.0, TAM_BLOCO/2.0, TAM_BLOCO/2.0, m_texturaParede);
				glPopMatrix();
			}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
}

void DesenhaJanela(GLfloat tam) {
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_paredes);
	glPushMatrix();
		glTranslatef(0.f, TAM_BLOCO/2.0 + TAM_BLOCO/5.0, -TAM_BLOCO/2.0 + TAM_BLOCO/30.0);
		DesenhaCuboTextura(TAM_BLOCO/2.0, TAM_BLOCO/30.0, TAM_BLOCO/30.0, m_texturaParede);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.f, -TAM_BLOCO/2.0+TAM_BLOCO/30.0, -TAM_BLOCO/2.0 + TAM_BLOCO/30.0);
		DesenhaCuboTextura(TAM_BLOCO/2.0, TAM_BLOCO/30.0, TAM_BLOCO/30.0, m_texturaParede);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLfloat v[4][3] = {{-tam, -tam, -tam+0.1f}, {tam, -tam, -tam+0.1f}, {tam, tam*1.5f, -tam+0.1f}, {-tam, tam*1.5f, -tam+0.1f}};
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_janela);
	glBegin(GL_QUADS);
		struct vetor Normal = calculaNormal(v[0], v[1], v[2], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glVertex3fv(v[0]);
		glVertex3fv(v[1]);
		glVertex3fv(v[2]);
		glVertex3fv(v[3]);
	glEnd();
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
}

void DesenhaJanelas(void) {
	int x, z, x_mun, z_mun;
	for (x = 0; x < TAM_MAPA; x++)
		for (z = 0; z < TAM_MAPA; z++)
			if (mapa[x][z] == 2) {
				x_mun = x * TAM_BLOCO;
				z_mun = z * TAM_BLOCO;
				glPushMatrix();
					glTranslatef(x_mun + TAM_BLOCO/2.0, TAM_BLOCO/2.0, z_mun + TAM_BLOCO/2.0);
					DesenhaJanela(TAM_BLOCO/2.0);
				glPopMatrix();
			}
}

/**
 * Desenha o chão do labirinto na cor verde.
 * */
void DesenhaMapa(void) {
	GLfloat v[4][3] = { {-TAM_MUNDO, 0, -TAM_MUNDO}, {-TAM_MUNDO, 0, TAM_MUNDO},
											{TAM_MUNDO, 0, TAM_MUNDO}  , {TAM_MUNDO, 0, -TAM_MUNDO} };
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texturaChao);
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, luz_chao);
	glBegin(GL_QUADS);
		struct vetor Normal = calculaNormal(v[0], v[1], v[2], v[3]);
		glNormal3f(Normal.x, Normal.y, Normal.z);
		glTexCoord2f(0, 0); 					glVertex3fv(v[0]);
		glTexCoord2f(0, 50.0f);  		glVertex3fv(v[1]);
		glTexCoord2f(50.0f, 50.0f);	glVertex3fv(v[2]);
		glTexCoord2f(50.0f, 0);			glVertex3fv(v[3]);
	glEnd();
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
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
void Desenha(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (cam == ATRAS_ROBO) {
		gluLookAt(posX - (TAM_BLOCO+zoomRobot)*sin(angulo/rad), TAM_BLOCO*1.8, posZ - (TAM_BLOCO+zoomRobot)*cos(angulo/rad),
					posX, TAM_BLOCO/2.0 , posZ,
					0, 1, 0);
	} else if (cam == PANORAMICA) {
		gluLookAt(TAM_MAPA*TAM_BLOCO/2.0, TAM_BLOCO*14 + zoomAereo, TAM_MAPA*TAM_BLOCO/2.7,
					TAM_MAPA*TAM_BLOCO/2.0, -20.0, TAM_MAPA*TAM_BLOCO/2.7,
					0, 0, 1);
	} else if (cam == OBJETO1) {
		gluLookAt(posObj1X + zoomObj1*cos(anguloObj1/rad), TAM_BLOCO*2, posObj1Z + zoomObj1*sin(anguloObj1/rad),
					posObj1X, TAM_BLOCO/2.0, posObj1Z,
					0, 1, 0);
	} else if (cam == OBJETO2) {
		gluLookAt(posObj2X + zoomObj2*cos(anguloObj2/rad), TAM_BLOCO*2, posObj2Z + zoomObj2*sin(anguloObj2/rad),
					posObj2X, TAM_BLOCO/2.0, posObj2Z,
					0, 1, 0);
	} else if (cam == OBJETO3) {
		gluLookAt(posObj3X + zoomObj3*cos(anguloObj3/rad), TAM_BLOCO*2, posObj3Z + zoomObj3*sin(anguloObj3/rad),
					posObj3X, TAM_BLOCO/2.0, posObj3Z,
					0, 1, 0);
	}	else if (cam == PARQUE) {
		gluLookAt(posParqueX + zoomParque*cos(anguloParque/rad), TAM_BLOCO*2, posParqueZ + zoomParque*sin(anguloParque/rad),
					posParqueX, TAM_BLOCO/2.0, posParqueZ,
					0, 1, 0);
	}

	/* desenha o carro */
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glPushMatrix();
		glTranslatef(posObj1X, 2, posObj1Z);
		glRotatef(90, 0, 1, 0);
		DesenhaObjeto1();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(posParqueX, 5, posParqueZ);
		glRotatef(90, 0, 1, 0);
		DesenhaParque();
	glPopMatrix();

	/* desenha o boneco de neve */
	glPushMatrix();
		glTranslatef(posObj2X, -2, posObj2Z);
		DesenhaObjeto2();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(posObj3X, 0, posObj3Z);
		DesenhaObjeto3();
	glPopMatrix();

	glPushMatrix();
		DesenhaMapa(); //desenha o chão
	glPopMatrix();

	glPushMatrix();
		DesenhaParedes(); //desenha paredes
	glPopMatrix();

	/* desenha o robô */
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glTranslatef(posX, 0, posZ);
		glRotatef(180+angulo, 0, 1, 0);
		DesenhaRobot(Robot);
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
		DesenhaJanelas();
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
			glEnable(GL_BLEND);

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

			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);

			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	/* Desenha a janela de ajuda */
	if (menu_help && !menu_venceu) {
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

	/* Desenha a mensagem de vitória no centro da tela */
	if (menu_venceu) {
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

			if (modo == AUTOMATICO) {
				char texto_venceu[] = "FIM DO LABIRINTO, O ROBO VENCEU!!!";
				DesenhaTexto(SCREEN_WIDTH/3.2, SCREEN_HEIGHT/2.5, 1.0f, 1.0f, 1.0f, texto_venceu, 1);
			} else {
				char texto_venceu[] = "FIM DO LABIRINTO, VOCE VENCEU!!!";
				DesenhaTexto(SCREEN_WIDTH/3.2, SCREEN_HEIGHT/2.5, 1.0f, 1.0f, 1.0f, texto_venceu, 1);
			}

			char texto_reinicia[] = "tecle ENTER para reiniciar o labirinto";
			DesenhaTexto(SCREEN_WIDTH/3.2, SCREEN_HEIGHT/2.0, 1.0f, 1.0f, 1.0f, texto_reinicia, 0);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_LIGHTING);

			glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
	glutSwapBuffers();
}

/** Menu acessado após clique com o botão direito->Câmera **/
void MenuCamera (int op) {
	switch(op) {
		case 1:
			cam = PANORAMICA;
			break;
		case 2:
			cam = OBJETO1;
			break;
		case 3:
			cam = OBJETO2;
			break;
		case 4:
			cam = OBJETO3;
			break;
		case 5:
			cam = PARQUE;
			break;
		case 6:
			cam = ATRAS_ROBO;
			break;
	}
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
}

void MenuPrincipal(int op){}

/** Menu criado ao clicar com o botão direito do mouse na tela **/
void CriaMenu(void) {
	int submenu1, submenu2;
	submenu1 = glutCreateMenu(MenuCamera);
	glutAddMenuEntry("Panoramica", 1);
	glutAddMenuEntry("Objeto 1", 2);
	glutAddMenuEntry("Objeto 2", 3);
	glutAddMenuEntry("Objeto 3", 4);
	glutAddMenuEntry("Parque", 5);
	glutAddMenuEntry("Atras do Robo", 6);
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
}

/** Carregamento e configurações de textura **/
void InicializaTextura(void) {
	unsigned int parede_w = 0, parede_h = 0;
	unsigned int chao_w = 0, chao_h = 0;
	unsigned int face_w = 0, face_h = 0;
	unsigned int bola_w = 0, bola_h = 0;
	unsigned int areia_w = 0, areia_h = 0;

	unsigned char *texturaParede, *texturaChao, *texturaFace, *texturaBola, *texturaAreia;

	texturaParede = loadBMP_custom("texturas/bricks.bmp", parede_h, parede_w);
	texturaChao   = loadBMP_custom("texturas/chao.bmp", chao_h, chao_w);
	texturaFace   = loadBMP_custom("texturas/face2.bmp", face_h, face_w);
	texturaBola   = loadBMP_custom("texturas/bola.bmp", bola_h, bola_w);
	texturaAreia  = loadBMP_custom("texturas/areia.bmp", areia_h, areia_w);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	///carregar textura da parede
	glGenTextures(1, &m_texturaParede);
	glBindTexture(GL_TEXTURE_2D, m_texturaParede);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, parede_w, parede_h, 0, GL_RGB, GL_UNSIGNED_BYTE, texturaParede);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, parede_w, parede_h, GL_RGB, GL_UNSIGNED_BYTE, texturaParede);

	///carregar textura do chão
	glGenTextures(1, &m_texturaChao);
  glBindTexture(GL_TEXTURE_2D, m_texturaChao);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, chao_w, chao_h, 0, GL_RGB, GL_UNSIGNED_BYTE, texturaChao);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, chao_w, chao_h, GL_RGB, GL_UNSIGNED_BYTE, texturaChao);

  ///carregar textura da face
	glGenTextures(1, &m_texturaFace);
  glBindTexture(GL_TEXTURE_2D, m_texturaFace);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, face_w, face_h, 0, GL_RGB, GL_UNSIGNED_BYTE, texturaFace);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, face_w, face_h, GL_RGB, GL_UNSIGNED_BYTE, texturaFace);

	glGenTextures(1, &m_texturaBola);
  glBindTexture(GL_TEXTURE_2D, m_texturaBola);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, face_w, face_h, 0, GL_RGB, GL_UNSIGNED_BYTE, texturaBola);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, face_w, face_h, GL_RGB, GL_UNSIGNED_BYTE, texturaFace);

	glGenTextures(1, &m_textureAreia);
  glBindTexture(GL_TEXTURE_2D, m_textureAreia);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bola_w, bola_h, 0, GL_RGB, GL_UNSIGNED_BYTE, texturaAreia);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, face_w, face_h, GL_RGB, GL_UNSIGNED_BYTE, texturaAreia);

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/** Inicializa renderização de sombra e iluminação **/
void InicializaIluminacao(void) {
	glClearColor (0.0, 0.5, 0.8, 0.8);
	glShadeModel (GL_SMOOTH);

	GLfloat posicao0[] = { TAM_MAPA*TAM_BLOCO, TAM_MAPA*TAM_BLOCO, TAM_MAPA*TAM_BLOCO, 1.0 };
	GLfloat direcao0[] = {-TAM_MAPA*TAM_BLOCO/2.0, -1.0, -TAM_MAPA*TAM_BLOCO/2.0};
	GLfloat posicao1[] = { 0.0, TAM_MAPA*TAM_BLOCO, 0.0, 1.0 };
	GLfloat direcao1[] = {TAM_MAPA*TAM_BLOCO/2.0, -1.0, TAM_MAPA*TAM_BLOCO/2.0};
	GLfloat ambiente[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat difusa[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat modeloAmbienteGlobal[] = {0.1, 0.1, 0.1, 1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modeloAmbienteGlobal);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT0, GL_POSITION, posicao0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcao0);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT1, GL_POSITION, posicao1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direcao1);
	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);
}

/** Inicializa teste de Z-Buffer, modo de câmera e de ação **/
void Inicializa(void) {
	cam = ATRAS_ROBO;
	modo = MANUAL;
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glDepthFunc(GL_LESS);
	InicializaIluminacao();
	InicializaTextura();
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
    gluPerspective(45, SCREEN_WIDTH/SCREEN_HEIGHT, 1, MAX*3.5);
}

/** Retorna true se o movimento do robô não o fará colidir com um bloco
 * ou um objeto, e retorna false caso colida. */
bool verifica_colisao_objetos (int bloco_mapa_x, int bloco_mapa_z) {
	if (bloco_mapa_x < 0 || bloco_mapa_z < 0)
		return false;

	int bloco_objeto1_x = (int) (posObj1X / TAM_BLOCO);
	int bloco_objeto1_z = (int) (posObj1Z / TAM_BLOCO);
	int bloco_objeto2_x = (int) (posObj2X / TAM_BLOCO);
	int bloco_objeto2_z = (int) (posObj2Z / TAM_BLOCO);
	int bloco_objeto3_x = (int) (posObj3X / TAM_BLOCO);
	int bloco_objeto3_z = (int) (posObj3Z / TAM_BLOCO);

	if ((bloco_mapa_x == bloco_objeto1_x && bloco_mapa_z == bloco_objeto1_z) ||
		(bloco_mapa_x == bloco_objeto1_x && bloco_mapa_z == bloco_objeto1_z+1) ||
		(bloco_mapa_x == bloco_objeto2_x && bloco_mapa_z == bloco_objeto2_z) ||
		(bloco_mapa_x == bloco_objeto3_x && bloco_mapa_z == bloco_objeto3_z) ) {
		return false;
	}

	return true;
}

/** verifica se o robô chegou ao bloco final do labirinto */
bool verifica_venceu (int bloco_mapa_x, int bloco_mapa_z) {
	if (bloco_mapa_x == bloco_final_x && bloco_mapa_z == bloco_final_z) {
		return true;
	}
	return false;
}

/**
 * Função CallBack que monitora as interrupções de teclas especiais
**/
void GerenciaTecladoEspecial(int key, int x, int y) {
	if(!menu_inicial && !menu_venceu) {
		if(key == GLUT_KEY_UP && modo == MANUAL) {
			//anda para frente no modo manual
			int bloco_mapa_x = (int) ((posX + 7*sin(angulo/rad)) / TAM_BLOCO);
			int bloco_mapa_z = (int) ((posZ + 7*cos(angulo/rad)) / TAM_BLOCO);

			if (verifica_venceu(bloco_mapa_x, bloco_mapa_z))
				menu_venceu = true;

			if (mapa[bloco_mapa_x][bloco_mapa_z] != 1 &&
					((posX + sin(angulo/rad)) >= TAM_BLOCO/2.0) &&
					((posZ + cos(angulo/rad)) >= TAM_BLOCO/2.0) &&
					verifica_colisao_objetos(bloco_mapa_x, bloco_mapa_z)) {
				posX += sin(angulo/rad);
				posZ += cos(angulo/rad);
			}
			if (!Robot->movendo_pernas)
				Robot->movendo_pernas = 1;
		}
		else if(key == GLUT_KEY_DOWN && modo == MANUAL) {
			//anda para trás no modo manual
			int bloco_mapa_x = (int) ((posX - 7*sin(angulo/rad)) / TAM_BLOCO);
			int bloco_mapa_z = (int) ((posZ - 7*cos(angulo/rad)) / TAM_BLOCO);

			if (verifica_venceu(bloco_mapa_x, bloco_mapa_z))
				menu_venceu = true;

			if (mapa[bloco_mapa_x][bloco_mapa_z] != 1 &&
					((posX - 3*sin(angulo/rad)) >= TAM_BLOCO/2.0) &&
					((posZ - 3*cos(angulo/rad)) >= TAM_BLOCO/2.0) &&
					verifica_colisao_objetos(bloco_mapa_x, bloco_mapa_z)) {
				posX -= sin(angulo/rad);
				posZ -= cos(angulo/rad);
			}
			if (!Robot->movendo_pernas)
				Robot->movendo_pernas = 1;
		}
		else if (key == GLUT_KEY_RIGHT) {
			//muda a direção para 5 graus à direita
			switch (cam) {
				case PANORAMICA:
				case ATRAS_ROBO:
					angulo -= 5;
					if (Robot->rot_cabeca >= -30) Robot->rot_cabeca -= 3;
				break;
				case OBJETO1:
					anguloObj1 -= 5;
				break;
				case OBJETO2:
					anguloObj2 -= 5;
				break;
				case OBJETO3:
					anguloObj3 -= 5;
				break;
				case PARQUE:
					anguloParque -= 5;
				break;
			}
		}
		else if (key == GLUT_KEY_LEFT) {
			//muda a direção para 5 graus à esquerda
			switch (cam) {
				case PANORAMICA:
				case ATRAS_ROBO:
					angulo += 5;
					if (Robot->rot_cabeca <= 30) Robot->rot_cabeca += 3;
				break;
				case OBJETO1:
					anguloObj1 += 5;
				break;
				case OBJETO2:
					anguloObj2 += 5;
				break;
				case OBJETO3:
					anguloObj3 += 5;
				break;
				case PARQUE:
					anguloParque += 5;
				break;
			}
		}
	}
}

/**
 * Função CallBack que gerencia as interrupções do teclado.
 * Executa ações referentes ao zoom da câmera e troca de perspectiva.
 * */
void GerenciaTeclado(unsigned char key, int x, int y) {
	if (!menu_inicial && !menu_venceu) {
		if (cam == PANORAMICA) {
			//Controla a proximidade da câmera aérea
			if (key == '+') {
				if (zoomAereo > 10)
					zoomAereo -= 10;
			} else if (key == '-') {
				if (zoomAereo + 10 <= MAX)
					zoomAereo += 10;
			}
		} else if (cam == ATRAS_ROBO) {
			//Controla a proximidade da câmera em 3a. pessoa
			if (key == '+') {
				if(zoomRobot > -MAX)
					zoomRobot -= 5;
			} else if (key == '-') {
				if(zoomRobot < MAX)
					zoomRobot += 5;
			}
		} else if (cam == OBJETO1) {
			//Controla a proximidade do objeto 1
			if (key == '+') {
				if(zoomObj1 > -MAX)
					zoomObj1 -= 5;
			} else if (key == '-') {
				if(zoomObj1 < MAX)
					zoomObj1 += 5;
			}
		} else if (cam == OBJETO2) {
			//Controla a proximidade do objeto 2
			if (key == '+') {
				if(zoomObj2 > -MAX)
					zoomObj2 -= 5;
			} else if (key == '-') {
				if(zoomObj2 < MAX)
					zoomObj2 += 5;
			}
		} else if (cam == OBJETO3) {
			//Controla a proximidade do objeto 2
			if (key == '+') {
				if(zoomObj3 > -MAX)
					zoomObj3 -= 5;
			} else if (key == '-') {
				if(zoomObj3 < MAX)
					zoomObj3 += 5;
			}
		} else if (cam == PARQUE) {
			//Controla a proximidade do objeto 2
			if (key == '+') {
				if(zoomParque > -MAX)
					zoomParque -= 5;
			} else if (key == '-') {
				if(zoomParque < MAX)
					zoomParque += 5;
			}
		}

		if (key == 'c' || key == 'C') {
			//Troca o modo de câmera (toggle entre panorâmica e 3a. pessoa)
			if (cam == ATRAS_ROBO) {
				cam = PANORAMICA;
			} else {
				cam = ATRAS_ROBO;
			}
		} else if (key == '1') {
			cam = OBJETO1;
		}
		else if (key == '2') {
			cam = OBJETO2;
		}
		else if (key == '3') {
			cam = OBJETO3;
		}
		else if (key == '4') {
			cam = PARQUE;
		}
		else if (key == 'm' || key == 'M') {
			/* Troca o modo de ação, ou seja, se o robô se moverá automaticamente
			 * ou se é necessária controlar através do teclado. */
			if (modo == MANUAL) {
				modo = AUTOMATICO;
			} else if (modo == AUTOMATICO) {
				modo = MANUAL;
			}
		}
	} else if (!menu_inicial && menu_venceu) {
		if (key == 13) {
			// Se estiver no menu inicial e for pressionada a tecla ENTER, libera o labirinto
			menu_venceu = false;
			ReiniciaLabirinto();
		}
	} else if (menu_inicial && !menu_venceu) {
		if (key == 13) {
			// Se estiver no menu inicial e for pressionada a tecla ENTER, libera o labirinto
			menu_inicial = false;
		}
	}

	if ((key == 'h' || key == 'H') && !menu_venceu) {
		menu_help = !menu_help;
	}
}

/**
 * Move o robô automaticamente, mudando de direção aleatoriamente após uma colisão.
 * */
void move (void) {
	//Calcula para qual bloco o robô vai após o movimento para frente
	int bloco_mapa_x = (int) ((posX + 7*sin(angulo/rad)) / TAM_BLOCO);
	int bloco_mapa_z = (int) ((posZ + 7*cos(angulo/rad)) / TAM_BLOCO);

	if (verifica_venceu(bloco_mapa_x, bloco_mapa_z))
		menu_venceu = true;

	if (mapa[bloco_mapa_x][bloco_mapa_z] != 1 &&
		((posX + sin(angulo/rad)) >= TAM_BLOCO/2.0) &&
		((posZ + cos(angulo/rad)) >= TAM_BLOCO/2.0) &&
		verifica_colisao_objetos(bloco_mapa_x, bloco_mapa_z)) {
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
 * Coloca o robô de volta no início do labirinto.
 * */
void ReiniciaLabirinto(void) {
	posX = TAM_BLOCO*1.5;
	posZ = TAM_BLOCO*1.5;
	modo = MANUAL;
	cam = ATRAS_ROBO;
	angulo = 90;
	zoomAereo = MAX;
	zoomRobot = 26;
}

/**
 * Função de Timer
 * ATENÇÃO: para trocar a taxa de milissegundos ou FPS, alterar a constante FPS no arquivo defs.h
 * VALOR PADRÃO: 30fps (33ms).
 * Se o modo selecionado for "AUTOMATICO", o robô tentará encontrar o caminho para o fim do labirinto sozinho.
 * Caso contrário (modo "MANUAL") somente espera uma ação do usuário.
 * */
void Timer(int a) {
	if (!menu_inicial && !menu_venceu) {
		if (modo == AUTOMATICO)
			move();
		if (Robot->movendo_pernas) {
			move_cabeca();
			move_pernas(Robot);
		}
	}
	if (movBalanco) {
		if (movimentoBalanco/rad >= 0)
			movimentoBalanco += 2.0f*(1-sin(movimentoBalanco/rad));
		else
			movimentoBalanco += 2.0f*(1+sin(movimentoBalanco/rad));
  } else {
		if (movimentoBalanco/rad >= 0)
			movimentoBalanco -= 2.0f*(1-sin(movimentoBalanco/rad));
		else
			movimentoBalanco -= 2.0f*(1+sin(movimentoBalanco/rad));
	}
	if (movBola) movimentoBola += 1-cos(movimentoBola/rad);
  else movimentoBola -= 1-cos(movimentoBola/rad);

	glutPostRedisplay();
	glutTimerFunc(1000.0/FPS, Timer, 1);
}

/**
 * Função Main
 * */
int main(int argc, char *argv[]) {
	srand(time(NULL));
	Robot = inicializaRobot();
	glutInit(&argc, argv); //inicialização dos módulos Glut
	//inicializa os modos de Buffer Duplo, cores RGBA e profundidade
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  //configuração e inicialização da janela
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Labirinto");

	glutDisplayFunc(Desenha); //definição da CallBack de desenho
	glutReshapeFunc(AlteraTamanhoJanela); //definição da CallBack de redimensionamento da janela
	glutMouseFunc(GerenciaMouse); //definição da CallBack de controle do mouse
	glutSpecialFunc(GerenciaTecladoEspecial); //definição da CallBack de controle das teclas especiais
	glutKeyboardFunc(GerenciaTeclado); //definição da CallBack de controle do teclado (ASCII)
	glutTimerFunc(1000.0/FPS, Timer, 1); //definição da CallBack de Timer

	Inicializa(); //Inicializações de textura/iluminação
	glutMainLoop(); //laço de execução infinito

	liberaRobot(Robot);

	return 0;
}
