/*
 * Universidade Federal da Grande Dourados - UFGD.
 * Faculdade de Ciências Exatas e Tecnologia - FACET.
 * Bacharelado em Engenharia de Computação.
 *
 * Disciplina: Laboratório de Computação Gráfica - LCG.
 * Professor: Adailton José Alves da Cruz.
 * Período: semestre 2022.1 || ocorrência no 2º semestre do ano de 2022.
 *
 * Programa: main.cpp
 * Desenvolvido por: João Vitor Nascimento De Souza.
 *
 * Objetivo:
 * - Desenhar uma braço robô utilizando primitivas e transformações geométricas.
 * Referência: Autoria própria.
 */

// Bibliotecas utilizadas.
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <math.h>
#include "bibliotecarobo.h"

// Constantes.
#define win 100    // Variável que armazena o valor de coordenadas para cada orientação da janela (x e y).
#define PI 3.14159 // Constante PI.

// Variáveis globais
GLfloat width = 1024, height = 768; // Armazena o tamanho da janela, para eventos de redimensionar a janela.
GLint rotaciona = 0;

// protótipos de funções/procedimentos.
void inicializa();

void draw_cartesiane();

void draw_ret();

void draw_circle(int, int);

void draw_base();

void draw_junta0();

void draw_membro1();

void draw_junta1();

void draw_membro2();

void draw_junta2();

void draw_membro3();

void draw_junta3();

void draw_mao();

static void resize(int, int);

static void display();

static void key(unsigned char, int, int);

/*
 * Função principal: responsável pela execução do programa do início ao fim.
 * Entrada: argumentos passados pelos prompt de comando.
 * Saída:
 * - EXIT_SUCESS: finalizado corretamente.
 * - Outros valors: ocorrência de erros na execução.
 */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                       // Inicicializa com os argumentos passados no prompt de comando.
    glutInitWindowSize(width, height);           // Define o tamanho da janela em pixels.
    glutInitWindowPosition(250, 10);             // Define a posição do canto superior esquerda da janela.
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); // Descreve as configurações da janela (cores suportadas e suas características).
    glutCreateWindow("Braco robo");              // Cria a janela e inseri um título.

    inicializa(); // Define a cor de fundo.

    /*
     * Rotinas callback:
     *  Se ocorrer um evento de sistema devido a interação com a janela criada
     *  aciona uma dessas rotinas, executando suas funções internas.
     */
    glutReshapeFunc(resize);  // Executa o procedimento resize.
    glutDisplayFunc(display); // Executa o procedimento display.
    glutKeyboardFunc(key);    // Executa o procedimento key.

    glutMainLoop(); // Mantém o programa executando em loop, aguardando a ocorrência de novos eventos com a janela.

    return EXIT_SUCCESS;
}

// Funções/Procedimentos.
void inicializa()
{
    glClearColor(0, 0, 0, 0); // Seleciona a cor de fundo para limpeza da tela (R, G, B, A).
}

// Funções/Procedimentos das rotinas callback.

/*
 * Função responsável por adaptar a janela de visualização (Viewport) e os elementos contidos na janela (Projeção),
 * caso ocorra um evento de redimensionamento de janela.
 * Entrada:
 *  - w: nova largura.
 *  - h: nova altura.
 */
static void resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, width, height); // Porta de visualização, onde será feitos os desenhos dos elementos.
    glMatrixMode(GL_PROJECTION);     // Inicializa os valores de visualização.
    glLoadIdentity();                // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    // Se ocorrer de altura ser 0, altera para pelo menos 1.
    if (height == 0)
        height = 1;

    // Difine o limites para as coordenadas da janela (RANGE em 2D).
    if (width <= height)
        gluOrtho2D(-win, win, -win * height / width, win * height / width);
    else
        gluOrtho2D(-win * width / height, win * width / height, -win, win);
}

/*
 * Procedimento responsável por atualizar o display da janela.
 * Mostra todos os desenhos.
 */
static void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpa o buffer de cores atual da janela.

    glMatrixMode(GL_MODELVIEW); // Matriz corrente, contendo todas as transformações geométricas em um determinado momento.
    glLoadIdentity();           // Faz com que a matriz corrente seja inicializada com a matriz identidade.

    draw_cartesiane(); // Desenha o plano cartesiano.

    draw_base();

    draw_membro1();
    draw_junta0();

    draw_membro2();
    draw_junta1();

    draw_membro3();
    draw_junta2();

    draw_mao();
    draw_junta3();

    glFlush(); // Faz os comandos não executados serem executados.
}

/*
 * Desnha um retângulo de largura 20 e comprimento 60.
 */
void draw_ret()
{
    glBegin(GL_QUADS);
    // x varia 60.
    // y varia 16.
    glVertex2f(0, -8);
    glVertex2f(0, 8);
    glVertex2f(60, 8);
    glVertex2f(60, -8);
    glEnd();
}

/*
 * Procedimento que desenha um círculo baseada em informações passadas, algumas características:
 * Entrada:
 *  -- r = é o raio.
 *  -- pts = são os pontos para formar o círculo. De preferência utilize números pares.
 * Saída: Desenha uma círculo.
 */
void draw_circle(int r, int pts)
{
    int i;
    float angulo = 0, radiano, aumento = float(360) / float(pts);

    // Desenha circle.
    glColor3f(0, 0, 1);
    glBegin(GL_POLYGON);
    for (i = 0; i < pts; i++)
    {
        radiano = angulo * (PI / 180); // Conversão angulo para radiano.
        glVertex2f(r * cos(radiano), r * sin(radiano));
        angulo += aumento;
    }
    glEnd();

    // Desenha sinal de mais no centro do circle.
    glColor3f(1, 1, 0); // Cor amarelo.
    glLineWidth(r / 2); // Tamanho da linha é proporcional ao tamanho do raio.

    glBegin(GL_LINES);
    glVertex2f(-r / 2, 0);
    glVertex2f(r / 2, 0);
    glVertex2f(0, -r / 2);
    glVertex2f(0, r / 2);
    glEnd();
}

void draw_base()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(-90, -80, 0);
    glColor3f(1, 0.46, 0.1); // Cor laranja.
    draw_ret();
}

void draw_junta0()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(-60, -72, 0);
    // glRotatef(rotaciona, 0, 0, 1);
    draw_circle(8, 360);
}

void draw_membro1()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(-60, -72, 0);
    // glRotatef(rotaciona, 0, 0, 1);
    glScalef(1, 1.2, 1); // Um pouco mais comprido.
    glRotatef(90, 0, 0, 1);
    glColor3f(1, 0, 1); // Cor rosa.
    draw_ret();
}

void draw_junta1()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(-60, 0, 0);
    // glRotatef(rotaciona, 0, 0, 1);
    draw_circle(8, 360);
}

void draw_membro2()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(-60, 0, 0);
    // glRotatef(rotaciona, 0, 0, 1);
    glScalef(1.1, 0.8, 1);
    glColor3f(1, 1, 0); // Cor amarelo.
    draw_ret();
}

void draw_junta2()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(6, 0, 0);
    // glRotatef(rotaciona, 0, 0, 1);
    draw_circle(8, 360);
}

void draw_membro3()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(6, 0, 0);
    // glRotatef(rotaciona, 0, 0, 1);
    glScalef(1, 0.6, 1);
    glColor3f(0, 1, 1); // Cor verde.
    draw_ret();
}

void draw_junta3()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(65, 0, 0);
    glRotatef(rotaciona, 0, 0, 1);
    draw_circle(5, 360);
}

void draw_mao()
{
    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glTranslatef(65, 0, 0);
    glRotatef(rotaciona, 0, 0, 1);

    glTranslatef(5, -15, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(0.5, 0.4, 0);
    glColor3f(0.5, 0.5, 0); //
    draw_ret();
}

/*
 * Desenha as retas x e y do plano cartesiano.
 */
void draw_cartesiane()
{
    GLfloat ar;

    glLoadIdentity(); // Limpa a matriz corrente de transformações geométricas.

    glColor3f(0.9, 0.9, 0.9); // Cor cinza.
    glLineWidth(1);           // Tamanho da linha.
    glBegin(GL_LINES);
    if (width <= height)
    {
        ar = height / width;
        // Eixo x.
        glVertex2f(-win, 0);
        glVertex2f(win, 0);
        // Eixo y.
        glVertex2f(0, -win * ar);
        glVertex2f(0, win * ar);
    }
    else
    {
        ar = width / height;
        // Eixo x.
        glVertex2f(-win * ar, 0);
        glVertex2f(win * ar, 0);
        // Eixo y.
        glVertex2f(0, -win);
        glVertex2f(0, win);
    }
    glEnd();
}

/*
 * Procedimento responsável por executar instruções caso ocorra o pressionamento
 * de teclas na janela exibida.
 * Entrada: uma tecla digitada.
 * Saída: Executa uma instrução.
 */
static void key(unsigned char letra, int x, int y)
{
    switch (letra)
    {
    case 27:
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'j':
    case 'J':
        rotaciona += 5;
        break;
    case 'l':
    case 'L':
        rotaciona -= 5;
        break;
    case 'o':
    case 'O':
        rotaciona = 0;
        break;
    }
    glutPostRedisplay(); // Atualiza o display a cada evento do teclado.
}
