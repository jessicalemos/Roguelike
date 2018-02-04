#include "estado.h"
#define SIZE 10
#define TAM 50

/**
\brief associação de um *nome ao respetivo link que contém uma a respetiva imagem.
*/
#define PLAYER "http://127.0.0.1/rato.png"
#define ENEMY "http://127.0.0.1/gato.png"
#define WALL "http://127.0.0.1/ratoeira.png"
#define GOAL "http://127.0.0.1/queijo.png"
#define SANGUE "http://127.0.0.1/blood.png"
#define GAMEOVER "http://127.0.0.1/gameover.png"
#define GO "http://127.0.0.1/go.png"
#define PATH "http://127.0.0.1/pathfinding.png"
#define POCAO "http://127.0.0.1/pocao.png"
#define RATO "http://127.0.0.1/rato_transparente.png"
#define GATO "http://127.0.0.1/gato_ataque.png"
#define FACA "http://127.0.0.1/faca.png"
#define BOMB "http://127.0.0.1/bomb.png"
#define MONSTER "http://127.0.0.1/help_button.png"
#define HELP "http://127.0.0.1/go_button.png"
#define NOVO "http://127.0.0.1/novo.png"
#define AUTO "http://127.0.0.1/auto.png"
#define BONUS1 "http://127.0.0.1/bonus1.png"
#define BONUS2 "http://127.0.0.1/bonus2.png"
#define BONUS3 "http://127.0.0.1/bonus3.png"
#define SCORE "http://127.0.0.1/score.png"

void parse();
int gera_numeros();
int gera_numeros2();
int valido(ESTADO e, int a, int b);
void print_move(ESTADO e, int dX, int dY);
int valido2(ESTADO e, int a, int b);
int scr(ESTADO e);
