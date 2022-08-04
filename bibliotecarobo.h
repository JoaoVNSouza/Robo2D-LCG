/*
 * Arquivo utilizado para armazenar:
 * - Protótipos de funções.
 * - Variáveis globais.
 * - Constantes.
 */

#ifndef BIBLIOTECAROBO_H_INCLUDED
#define BIBLIOTECAROBO_H_INCLUDED

// Constantes.
#define win 100         // Variável que armazena o valor de coordenadas para cada orientação da janela (x e y).
#define PI 3.14159      // Constante PI.

// Variáveis globais.
GLfloat width, height;  // Armazena o tamanho da janela, para eventos de redimensionar a janela.
GLint translada[2];     // Variável para fazer a translação da base e todos os membros.
GLint rotaciona;        // Variável para fazer a rotação da palma e mãos.
GLint X, Y;             // Variável para armazenar as coordenadas para transladar os elementos da mão.

// Protótipos de funções/procedimentos.

/* Diversos */
void inicializa();
void calcXY();

/* Primitivas */
void draw_ret();
void draw_circle(int, float);
void draw_cartesiane();

/* Rotinas Callbacks*/
static void resize(int, int);
static void display();
static void key(unsigned char, int, int);

/* Procedimentos de desenhar */
void draw_base();
void draw_junta0();
void draw_membro1();
void draw_junta1();
void draw_membro2();
void draw_junta2();
void draw_membro3();
void draw_junta3();
void draw_palma();
void draw_dedoDireito();
void draw_dedoEsquerdo();

#endif // BIBLIOTECAROBO_H_INCLUDED
