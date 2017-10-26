/**
 * @author JEFFERSON A. COPPINI, JONATHAN T. RAUBER
 * */

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//mundo do jogo
#define FPS 30 ///alterar aqui para mudar a taxa de atualização em ms
#define MAX 160.0
#define TAM_BLOCO 20
#define TAM_MAPA 15
#define TAM_MUNDO 1000

//objeto1
#define LARGURA_MESA TAM_BLOCO
#define ALTURA_MESA LARGURA_MESA/2.0
#define COMPRIMENTO_MESA LARGURA_MESA/2.0
#define GROSSURA_MESA LARGURA_MESA/10.0
#define GROSSURA_PE GROSSURA_MESA/2.0

//robô
#define TAM_CABECA 4
#define LARGURA_CORPO 6
#define ALTURA_CORPO 10	
#define TAM_PE 4
#define TAM_TOTAL 20
#define RAIO_PESCOCO TAM_CABECA/3.0
#define RAIO_OLHOS TAM_CABECA/8.0
#define LARGURA_SORRISO TAM_CABECA/2.0
#define ALTURA_SORRISO RAIO_OLHOS*1.5
#define COMPRIMENTO_ORELHAS TAM_CABECA/3.0
#define RAIO_ANTENA RAIO_OLHOS/2.0
#define COMPRIMENTO_BRACO ALTURA_CORPO/2.5
#define GROSSURA_BRACO ALTURA_CORPO/15.0

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
void DesenhaTexto(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, char *string, int font);
void DesenhaMapa(void);
void DesenhaParedes(void);
void DesenhaObjeto1(void);
void DesenhaObjeto2(void);
