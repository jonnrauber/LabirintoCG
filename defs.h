/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


typedef struct vetor {
  GLfloat x;
  GLfloat y;
  GLfloat z;
} vetor;

//mundo do jogo
#define FPS 30 ///alterar aqui para mudar a taxa de atualização em ms
#define MAX 160.0
#define TAM_BLOCO 20
#define TAM_MAPA 15
#define TAM_MUNDO 500

//robô
#define TAM_CABECA 4
#define LARGURA_CORPO 6
#define ALTURA_CORPO 10
#define TAM_PE 4
#define TAM_TOTAL 20
#define RAIO_PESCOCO TAM_CABECA/4.0
#define RAIO_OLHOS TAM_CABECA/8.0
#define LARGURA_SORRISO TAM_CABECA/2.0
#define ALTURA_SORRISO RAIO_OLHOS*1.5
#define COMPRIMENTO_ORELHAS TAM_CABECA/3.0
#define RAIO_ANTENA RAIO_OLHOS/2.0
#define COMPRIMENTO_BRACO ALTURA_CORPO/2.5
#define GROSSURA_BRACO ALTURA_CORPO/15.0
#define pi 3.14159
#define rad 57.2958

/* Cabeçalhos das funções */
void ReiniciaLabirinto(void);
void Timer(int a);
void move_cabeca (void);
void move (void);
void GerenciaTeclado(unsigned char key, int x, int y);
void GerenciaTecladoEspecial(int key, int x, int y);
bool verifica_venceu (int bloco_mapa_x, int bloco_mapa_z);
bool verifica_colisao_objetos (int bloco_mapa_x, int bloco_mapa_z);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Inicializa(void);
void InicializaIluminacao(void);
void GerenciaMouse(int button, int state, int x, int y);
void CriaMenu(void);
void MenuModo (int op);
void MenuCamera (int op);
void Desenha(void);
vetor calculaNormal(GLfloat *A, GLfloat *B, GLfloat *C, GLfloat *D);
void DesenhaTexto(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, char *string, int font);
void DesenhaMapa(void);
void DesenhaParedes(void);
void DesenhaObjeto1(void);
void DesenhaObjeto2(void);
void DesenhaObjeto3(void);
unsigned char* loadBMP_custom(const char *filename, unsigned int &width, unsigned int &height);
void DesenhaCuboTextura(GLfloat tam, GLuint textura);
void DesenhaParque(GLfloat* movimentoBalanco, bool* mov, GLUnurbsObj* theNurb);
void esfera(GLfloat *centro, GLfloat radius, GLfloat num, GLint texture);
