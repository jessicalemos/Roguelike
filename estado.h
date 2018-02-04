#ifndef ___ESTADO_H___
#define ___ESTADO_H___

/**
@file estado.h
Definição do estado e das funções que convertem estados em strings e vice-versa
*/

/** \brief O nº máximo de inimigos */
#define MAX_INIMIGOS		100

/** \brief O nº máximo de obstáculos */
#define MAX_OBSTACULOS		100

/** \brief O nº máximo de ajudas */
#define MAX_AJUDAS		100

/**
\brief Estrutura que armazena uma posição
*/
typedef struct posicao {
    char x;
    char y;
} POSICAO;

/**
\brief Estrutura que armazena o estado do jogo
*/
typedef struct estado {
        /** 1- é permitido imprimir uma ajuda no tabuleiro 0- não é **/
    char existe;
        /** score */
    char score;
        /** 1-automático 0-não automático**/
    char automatico;
        /** ajuda 0-sem ajudas 1-pathfinding 2-iluminar casas atacadas por todos os monstros 3-iluminar casas atacadas por um determinado mostro 4-refresh do jogo 5-salto */
    char help;
        /** usar ajuda 0-não pode 1-pode poção 2-pode explosão 3-pode novo 4-pode faca */
    char can;
        /** formas de matar inimigo 0-sem 1-mata poção 2-mata bomba 3-mata faca */
    char matar;
        /** ação 0-jogo 1-acabei nível 2-novo jogo */
    char acao;
        /** A posição do jogador */
    POSICAO jog;
        /** A posição da ajuda */
    POSICAO ajuda;
        /** A posição da porta objetivo */
    POSICAO gol;
        /** O nº de inimigos */
    char num_inimigos;
        /** O nº de obstáculos */
    char num_obstaculos;
        /**  nº do nível */
    char nivel;
        /** Array com a posição dos inimigos */
    POSICAO inimigo[MAX_INIMIGOS];
        /** Array com a posição dos obstáculos */
    POSICAO obstaculo[MAX_OBSTACULOS];
} ESTADO;

/**
\brief Função que converte um estado numa string
@param e O estado
@returns A string correspondente ao estado e
*/
char *estado2str(ESTADO e);

/**
\brief Função que converte uma string num estado 
@param argumentos Uma string contendo os argumentos passados à CGI
@returns O estado correspondente à string dos argumentos
*/
ESTADO str2estado(char *argumentos);

#endif
