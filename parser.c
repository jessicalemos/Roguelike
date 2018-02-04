#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parser.h"
#include "estado.h"

/**
\brief Função que inicializa o jogo.
Esta define as posicões iniciais do jogador, do objetivo, dos inimigos, dos obstáculos e das ajudas, sendo que estes três últimos são gerados aleatoriamente, para obtermos tabuleiros diferentes. Também fica estipulado que todas as restantes características se iniciam a zero, dado que são alteradas pelo decorrer do jogo. É importante realçar o facto de o número de obstáculos e inimigos aumentar com o nível, que corresponde ao parâmetro n.
@param n, inteiro que indica o nível em que se encontra o jogo.
@return e, estado do jogo.
*/
ESTADO inicializar(int n)
{
    ESTADO e = { 0 };
    int a, b, i = 0, j = 0;
    e.can = 0;
    e.existe = 1;
    e.help = 0;
    e.matar = 0;
    e.automatico = 0;
    e.acao = 0;
    e.score = 0;
    e.jog.x = 5;
    e.jog.y = 9;
    e.gol.x = 5;
    e.gol.y = 0;
    e.nivel = n;
    e.num_inimigos = 10 + n;
    while (i < e.num_inimigos) {
        a = gera_numeros();
        b = gera_numeros();
        if (valido(e, a, b)) {
            e.inimigo[i].x = a;
            e.inimigo[i].y = b;
            i++;
        }
    }
    e.num_obstaculos = 20 + n;
    while (j < e.num_obstaculos) {
        a = gera_numeros();
        b = gera_numeros();
        if (valido(e, a, b)) {
            e.obstaculo[j].x = a;
            e.obstaculo[j].y = b;
            j++;
        }
    }
    a = gera_numeros();
    b = gera_numeros();
    while (valido(e, a, b) == 0) {
        a = gera_numeros();
        b = gera_numeros();
    }
    e.ajuda.x = a;
    e.ajuda.y = b;
    return e;
}

/**
\brief Função para obter o score.
@param e, estado, para adquirir a informação do score.
@return r, inteiro, que contém o valor do score.
*/
int scr(ESTADO e)
{
    int r;
    r = e.score;
    return r;
}

/**
\brief Função que permite verificar se a casa do tabuleiro não está ocupada, de modo a poder lá colocar um inimigo ou um obstáculo ou uma ajuda.
O movimento é considerado válido se a posição para a qual o jogador pretende deslocar-se não estiver ocupada por um inimigo, um obstáculo, o objetivo ou corresponder ao posicionamento atual do jogador.
@param e, estado do jogo, que possibilita conhecer as posições das componentes do tabuleiro.
@param a, coordenada x aleatória, para averiguar se é possível alocar algum do elementos referidos anteriormente, no entanto, para tal é necessário complementar com a informação do parâmetro b.
@param b, coordenada y aleatória.
@return 0 se a posição não for válido ou 1 caso contrário.
*/
int valido(ESTADO e, int a, int b)
{
    int i;
    for (i = 0; i < e.num_inimigos; i++) {
        if (e.inimigo[i].x == a && e.inimigo[i].y == b)
            return 0;
    }
    for (i = 0; i < e.num_obstaculos; i++) {
        if (e.obstaculo[i].x == a && e.obstaculo[i].y == b)
            return 0;
    }
    if (e.jog.x == a && e.jog.y == b)
        return 0;
    if (e.gol.x == a && e.gol.y == b)
        return 0;
    return 1;
}

/**
\brief Função que permite verificar se o jogador se pode movimentar.
O movimento é considerado válido se a posição para a qual o jogador pretende deslocar-se não estiver ocupada por um inimigo, um obstáculo, ou corresponder ao posicionamento atual do jogador.
@param e, estado do jogo, que possibilita conhecer as posições das componentes do tabuleiro.
@param a, coordenada x para onde o jogador pretende ir, para averiguar se é válido o movimento, no entanto, para tal é necessário complementar com a informação do parâmetro b.
@param b, coordenada y para onde o jogador pretende ir.
@return 0 se a posição não for válida ou 1 caso contrário.
*/
int valido2(ESTADO e, int a, int b)
{
    int i;
    for (i = 0; i < e.num_inimigos; i++) {
        if (e.inimigo[i].x == a && e.inimigo[i].y == b)
            return 0;
    }
    for (i = 0; i < e.num_obstaculos; i++) {
        if (e.obstaculo[i].x == a && e.obstaculo[i].y == b)
            return 0;
    }
    if (e.jog.x == a && e.jog.y == b)
        return 0;
    return 1;
}

/**
\brief Função que conclui se o movimento dos inimigos é possível.
É considerado realizável caso na posição para onde pretende movimentar-se não se encontre um obstáculo, o jogador, o objetivo, uma ajuda ou um inimigo. 
@param e, estado do jogo, possibilita conhecer as posições das componentes do tabuleiro.
@param a, coordenada x para onde o inimigo pretende ir, para averiguar se é válido o movimento, no entanto, para tal é necessário complementar com a informação do parâmetro b.
@param b, coordenada y para onde o inimigo pretende dirigir-se.
@return 0 se o movimento não for concebível ou 1 caso contrário.
*/
int valido3(ESTADO e, int a, int b)
{
    int i;
    for (i = 0; i < e.num_inimigos; i++) {
        if (e.inimigo[i].x == a && e.inimigo[i].y == b)
            return 0;
    }
    for (i = 0; i < e.num_obstaculos; i++) {
        if (e.obstaculo[i].x == a && e.obstaculo[i].y == b)
            return 0;
    }
    if (e.jog.x == a && e.jog.y == b)
        return 0;
    if (e.gol.x == a && e.gol.y == b)
        return 0;
    if (e.ajuda.x == a && e.ajuda.y == b)
        return 0;
    return 1;
}

/**
\brief Função que apura se o deslocamento do jogador é possível e também se nenhum inimigo se irá mover para o mesmo local.
É admissível caso não pretenda deslocar-se para um local onde se encontre um inimigo, um obstáculo, uma ajuda, o objetivo ou o um inimgo pretenda movimentar-se para a mesma casa.
@param e, estado do jogo, possibilita conhecer as posições das componentes do tabuleiro.
@param dx, coordenada dx para onde o jogador pretende ir, para averiguar se é válido o movimento, no entanto, para tal é necessário complementar com a informação do parâmetro dx.
@param dy, coordenada dy para onde o jogador pretende ir.
@return 0 caso a posição não seja válido ou 1 caso contrário.
*/
int valido4(ESTADO e, int dx, int dy)
{
    int i;
    for (i = 0; i < e.num_obstaculos; i++) {
        if (e.obstaculo[i].x == dx && e.obstaculo[i].y == dy)
            return 0;
    }
    if (e.ajuda.x == dx && e.ajuda.y == dy)
        return 0;
    if (e.gol.x == dx && e.gol.y == dy)
        return 0;
    for (i = 0; i < e.num_inimigos; i++) {
        int a = e.inimigo[i].x + 1;
        int b = e.inimigo[i].y - 1;
        int c = e.inimigo[i].x - 1;
        int f = e.inimigo[i].y + 1;
        if (e.inimigo[i].y == 0 && e.inimigo[i].x > 4) {
            if (valido3(e, c, 0) && (c >= 0 && c < SIZE) && dx == c
                && dy == 0)
                return 0;
        }
        if (e.inimigo[i].y == 0 && e.inimigo[i].x < 5) {
            if (valido3(e, a, 0) && (a >= 0 && c < SIZE) && dx == a
                && dy == 0)
                return 0;
        }
        if ((e.inimigo[i].y) < 5 && (e.inimigo[i].x) < 5
            && e.jog.y <= SIZE - 5) {
            if (valido3(e, a, b)
                && (a >= 0 && b >= 0 && a < SIZE && b < SIZE) && dx == a
                && dy == b)
                return 0;
        }
        if (e.inimigo[i].y < 5 && e.inimigo[i].x > 4
            && e.jog.y <= SIZE - 5) {
            if (valido3(e, c, b)
                && (c >= 0 && b >= 0 && c < SIZE && b < SIZE) && dx == c
                && dy == b)
                return 0;
        }
        if (e.inimigo[i].y == (SIZE - 1) && e.inimigo[i].x > 4
            && e.jog.y > SIZE - 5) {
            if (valido3(e, c, b)
                && (c >= 0 && b >= 0 && c < SIZE && b < SIZE) && dx == c
                && dy == b)
                return 0;
        }
        if (e.inimigo[i].y == (SIZE - 1) && e.inimigo[i].x < 5
            && e.jog.y > SIZE - 5) {
            if (valido3(e, a, b)
                && (a >= 0 && b >= 0 && a < SIZE && b < SIZE) && dx == a
                && dy == b)
                return 0;
        }
        if (e.inimigo[i].y > 4 && e.inimigo[i].x > 4 && e.jog.y > SIZE - 5) {
            if (valido3(e, c, f)
                && (c >= 0 && f >= 0 && c < SIZE && f < SIZE) && dx == c
                && dy == f)
                return 0;
        }
        if (e.inimigo[i].y > 4 && e.inimigo[i].x < 5 && e.jog.y > SIZE - 5) {
            if (valido3(e, a, f)
                && (a >= 0 && f >= 0 && a < SIZE && f < SIZE) && dx == a
                && dy == f)
                return 0;
        }
    }
    return 1;
}

/**
\brief Função para imprimir os quadrados do tabuleiro do jogo.
@param X, coluna.
@param Y, linha.
@param tam, tamanho de cada quadrado.
*/
void print_square(int X, int Y, int tam)
{
    char *color[] = { "#696969", "#009ACD" };
    int idx = (X + Y) % 2;
    printf("<rect x=%d y=%d width=%d height=%d fill=\"%s\"/>\n", tam * X,
           tam * Y, tam, tam, color[idx]);
}

/**
\brief Função para imprimir o tabuleiro do jogo.
Tal é possível através da impressão de todos os quadrados por cada linha.
*/
void print_board()
{
    int X, Y;
    for (Y = 0; Y < SIZE; Y++)
        for (X = 0; X < SIZE; X++)
            print_square(X, Y, TAM);
}

/**
\brief Função para imprimir as imagens.
@param x, coluna em que vai ficar.
@param y, linha em que vai ficar.
@param tam, é o tamanho máximo que a imagem vai ter.
@param *name, nome da imagem, que permite obter o link da imagem a imprimir.
*/
void print_image(int x, int y, int tam, char *name)
{
    printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n",
           x * tam, y * tam, tam, tam, name);
}


/**
\brief Função para imprimir a porta de saída que dá acesso ao nível seguinte.
@param e, estado do jogo, para dispor as coordenadas do objetivo.
*/
void print_goal(ESTADO e)
{
    print_image(e.gol.x, e.gol.y, TAM, GOAL);
}

/**
\brief Função para mover os inimigos.
O movimento dos inimigos segue a seguinte estratégia: caso estes se encontrem na linha do objetivo estes deslocam-se no sentido do queijo; sempre que estejam no canto superior esquerdo efetuam o movimento diagonal no sentido do queijo, no entanto, apenas iniciam o deslocamento quando o jogador se encontra cinco linhas acima da posição inicial; na hipótese de o inimigo se apresentar no canto superior direito e o jogador a cinco linhas acima do início efetuam o movimento diagonal no sentido do queijo; se estiverem na última linha do tabuleiro e o jogador na parte inferior do tabuleiro iram mover-se na diagonal no sentido da coluna do jogador; quando os inimigos estão no canto inferior esquerdo e o jogador nas ultimas cinco linhas, dirigem-se na diagonal no sentido da coluna do rato; por último, estes deslocam-se na diagonal no sentido da coluna do jogador.
@param e, estado do jogo, possibilita conhecer as posições das componentes do tabuleiro.
@return ne, novo estado do jogo, que apenas são alteradas as coordenadas dos inimigos relativamente ao estado anterior.
*/
ESTADO move_monster(ESTADO e)
{
    ESTADO ne = e;
    int i;
    for (i = 0; i < e.num_inimigos; i++) {
        int a = e.inimigo[i].x + 1;
        int b = e.inimigo[i].y - 1;
        int c = e.inimigo[i].x - 1;
        int f = e.inimigo[i].y + 1;

        if (e.inimigo[i].y == 0 && e.inimigo[i].x > 4) {
            if (valido3(e, c, 0) && (c >= 0 && c < SIZE)) {
                ne.inimigo[i].x = c;
                ne.inimigo[i].y = 0;
            }
        }
        if (e.inimigo[i].y == 0 && e.inimigo[i].x < 5) {
            if (valido3(e, a, 0) && (a >= 0 && a < SIZE)) {
                ne.inimigo[i].x = a;
                ne.inimigo[i].y = 0;
            }
        }
        if ((e.inimigo[i].y) < 5 && (e.inimigo[i].x) < 5
            && e.jog.y <= SIZE - 5) {
            if (valido3(e, a, b)
                && (a >= 0 && b >= 0 && a < SIZE && b < SIZE)) {
                ne.inimigo[i].x = a;
                ne.inimigo[i].y = b;
            }
        }
        if (e.inimigo[i].y < 5 && e.inimigo[i].x > 4
            && e.jog.y <= SIZE - 5) {
            if (valido3(e, c, b)
                && (c >= 0 && b >= 0 && c < SIZE && b < SIZE)) {
                ne.inimigo[i].x = c;
                ne.inimigo[i].y = b;
            }
        }
        if (e.inimigo[i].y == (SIZE - 1) && e.inimigo[i].x > 4
            && e.jog.y > SIZE - 5) {
            if (valido3(e, c, b)
                && (c >= 0 && b >= 0 && c < SIZE && b < SIZE)) {
                ne.inimigo[i].x = c;
                ne.inimigo[i].y = b;
            }
        }
        if (e.inimigo[i].y == (SIZE - 1) && e.inimigo[i].x < 5
            && e.jog.y > SIZE - 5) {
            if (valido3(e, a, b)
                && (a >= 0 && b >= 0 && a < SIZE && b < SIZE)) {
                ne.inimigo[i].x = a;
                ne.inimigo[i].y = b;
            }
        }
        if (e.inimigo[i].y > 4 && e.inimigo[i].x > 4 && e.jog.y > SIZE - 5) {
            if (valido3(e, c, f)
                && (c >= 0 && f >= 0 && c < SIZE && f < SIZE)) {
                ne.inimigo[i].x = c;
                ne.inimigo[i].y = f;
            }
        }
        if (e.inimigo[i].y > 4 && e.inimigo[i].x < 5 && e.jog.y > SIZE - 5) {
            if (valido3(e, a, f)
                && (a >= 0 && f >= 0 && a < SIZE && f < SIZE)) {
                ne.inimigo[i].x = a;
                ne.inimigo[i].y = f;
            }
        }
    }
    return ne;
}

/**
\brief Função que vê se nas coordenadas para onde o jogador pretende ir se encontra um inimigo.
@param e, estado do jogo, para obter as posições dos inimigos.
@param a, coordenada x para a qual o rato pretende movimentar-se, para verificar se há um inimigo nesse local, no entanto, para tal é necessário complementar com a informação do parâmetro y.
@param b, coordenada y, para a qual o rato pretende movimentar-se.
@return 1 se estiver um inimigo ou 0 se não estiver.
*/
int ocupado(ESTADO e, int a, int b)
{
    int i;
    for (i = 0; i < e.num_inimigos; i++) {
        if (a == e.inimigo[i].x && b == e.inimigo[i].y)
            return 1;
    }
    return 0;
}

/**
\brief Função que mata os monstros sem recorrer a ajudas.
Esta percorre o array dos inimigos e verifica se algum se encontra na posição para onde o rato pretende ir. Se tal se suceder, irá eliminá-lo do array e consequentemente diminuir o número de inimigos existentes. 
@param e, estado do jogo, para adquirir a informação relativa aos inimigos.
@param a, coordenada x para onde o jogador se pretende movimentar.
@param b, coordenada y para onde o jogador pretende ir.
@return ne, novo estado, que elimina do estado anterior o inimigo que foi morto pelo jogador.
*/
ESTADO mata_monster(ESTADO e, int a, int b)
{
    ESTADO ne = e;
    int i, j;
    for (i = 0; i < e.num_inimigos; i++) {
        if (a == e.inimigo[i].x && b == e.inimigo[i].y) {
            for (j = i; j < e.num_inimigos; j++) {
                ne.inimigo[j].x = e.inimigo[j + 1].x;
                ne.inimigo[j].y = e.inimigo[j + 1].y;
            }
            ne.num_inimigos = e.num_inimigos - 1;
        }
    }
    return ne;
}

/**
\brief Função para fazer o pathfinding.
A estratégia utilizada para mover o jogador segundo o melhor caminho é a seguinte: inicialmente, verifica-se se é possível o movimento de duas casas para cima e na hipótese de o ser, averigua-se se há inimigos nesse local, se houver é necessário eliminá-lo. Caso não haja, efetua-se o movimento do jogador e dos inimigos. Caso não seja possível o movimento, implementamos a estratégia anterior para os seguintes deslocamentos: vertical de uma casa, diagonal de uma casa no sentido da esquerda, diagonal de uma casa no sentido da direita, uma casa horizontal para a direita e uma casa na horizontal para a esquerda, por esta ordem.
@param e, estado do jogo, possibilita conhecer as posições das componentes do tabuleiro.
*/
void path(ESTADO e)
{
    ESTADO ne = e;
    int dx = e.jog.x, dy = e.jog.y;
    if (valido4(e, dx, dy - 2)) {
        if (ocupado(e, dx, dy - 2)) {
            ne = mata_monster(e, dx, dy - 2);
            printf
                ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                 estado2str(ne));
            print_image(dx, dy - 2, TAM, RATO);
            printf("</a>\n");
        } else {
            ne = move_monster(e);
            ne.jog.x = dx;
            ne.jog.y = dy - 2;
            printf
                ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                 estado2str(ne));
            print_image(dx, dy - 2, TAM, RATO);
            printf("</a>\n");
        }
    } else {
        if (valido4(e, dx, dy - 1)) {
            if (ocupado(e, dx, dy - 1)) {
                ne = mata_monster(e, dx, dy - 1);
                printf
                    ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                     estado2str(ne));
                print_image(dx, dy - 1, TAM, RATO);
                printf("</a>\n");
            } else {
                ne = move_monster(e);
                ne.jog.x = dx;
                ne.jog.y = dy - 1;
                printf
                    ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                     estado2str(ne));
                print_image(dx, dy - 1, TAM, RATO);
                printf("</a>\n");
            }
        } else {
            if (valido4(e, dx - 1, dy - 1)) {
                if (ocupado(e, dx - 1, dy - 1)) {
                    ne = mata_monster(e, dx - 1, dy - 1);
                    printf
                        ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                         estado2str(ne));
                    print_image(dx - 1, dy - 1, TAM, RATO);
                    printf("</a>\n");

                } else {
                    ne = move_monster(e);
                    ne.jog.x = dx - 1;
                    ne.jog.y = dy - 1;
                    printf
                        ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                         estado2str(ne));
                    print_image(dx - 1, dy - 1, TAM, RATO);
                    printf("</a>\n");
                }
            } else {
                if (valido4(e, dx + 1, dy - 1)) {
                    if (ocupado(e, dx + 1, dy - 1)) {
                        ne = mata_monster(e, dx + 1, dy - 1);
                        printf
                            ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                             estado2str(ne));
                        print_image(dx + 1, dy - 1, TAM, RATO);
                        printf("</a>\n");

                    } else {
                        ne = move_monster(e);
                        ne.jog.x = dx + 1;
                        ne.jog.y = dy - 1;
                        printf
                            ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                             estado2str(ne));
                        print_image(dx + 1, dy - 1, TAM, RATO);
                        printf("</a>\n");
                    }
                } else {
                    if (valido4(e, dx + 1, dy)) {
                        if (ocupado(e, dx + 1, dy)) {
                            ne = mata_monster(e, dx + 1, dy);
                            printf
                                ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                                 estado2str(ne));
                            print_image(dx + 1, dy, TAM, RATO);
                            printf("</a>\n");

                        } else {
                            ne = move_monster(e);
                            ne.jog.x = dx + 1;
                            ne.jog.y = dy;
                            printf
                                ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                                 estado2str(ne));
                            print_image(dx + 1, dy, TAM, RATO);
                            printf("</a>\n");

                        }
                    } else {
                        if (valido4(e, dx - 1, dy)) {
                            if (ocupado(e, dx - 1, dy)) {
                                ne = mata_monster(e, dx - 1, dy);
                                printf
                                    ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                                     estado2str(ne));
                                print_image(dx - 1, dy, TAM, RATO);
                                printf("</a>\n");

                            } else {
                                ne = move_monster(e);
                                ne.jog.x = dx - 1;
                                ne.jog.y = dy;
                                printf
                                    ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                                     estado2str(ne));
                                print_image(dx - 1, dy, TAM, RATO);
                                printf("</a>\n");
                            }
                        }
                    }
                }
            }
        }
    }
}


/**
\brief Função para imprimir o botão do pathfinding.
Este botão faz com que seja ativada a ajuda do pathfinding.
@param e, estado do jogo, para o atualizar.
*/
void print_pathfinding(ESTADO e)
{
    ESTADO ne = e;
    ne.help = 1;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(12, 8, TAM, PATH);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão da poção.
Este botão faz com que seja ativada a possibilidade de matar com a poção.
@param e, estado do jogo, para o atualizar.
*/
void print_button_pocao(ESTADO e)
{
    ESTADO ne = e;
    ne.matar = 1;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(11, 6, TAM, POCAO);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão do jogador automático.
Este botão faz com que seja ativada a ajuda do jagador automático.
@param e, estado do jogo, para o atualizar.
*/
void print_button_auto(ESTADO e)
{
    ESTADO ne = e;
    ne.automatico = 1;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(14, 8, TAM, AUTO);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão da faca.
Este botão faz com que seja ativada a possibilidade de matar com a faca.
@param e, estado do jogo, para o atualizar.
*/
void print_button_faca(ESTADO e)
{
    ESTADO ne = e;
    ne.matar = 3;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(12, 6, TAM, FACA);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão da bomba.
Este botão faz com que seja ativada a possibilidade de matar com a bomba.
@param e, estado do jogo, para o atualizar.
*/
void print_button_explosao(ESTADO e)
{
    ESTADO ne = e;
    ne.matar = 2;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(13, 6, TAM, BOMB);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão de iluminar as casas atacadas pelos monstros.
Este botão faz com que seja ativada a ajuda de iluminar as casas atacadas pelos monstros.
@param e, estado do jogo, para o atualizar.
*/
void print_button_monstro(ESTADO e)
{
    ESTADO ne = e;
    ne.help = 2;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(13, 8, TAM, MONSTER);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão de começar o mesmo nível.
Este botão faz com que seja ativada a ajuda de começar o mesmo nível.
@param e, estado do jogo, para o atualizar.
*/
void print_button_novo(ESTADO e)
{
    ESTADO ne = e;
    ne.help = 4;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(14, 6, TAM, NOVO);
    printf("</a>\n");
}

/**
\brief Função para imprimir o botão de começar o jogo de novo.
Este botão faz com que seja inicializado o jogo.
@param e, estado do jogo, para o atualizar.
*/
void print_button_novo_jogo(ESTADO e)
{
    ESTADO ne = e;
    ne.acao = 2;
    printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
           estado2str(ne));
    print_image(11, 8, TAM, GO);
    printf("</a>\n");
}

/**
\brief Função que mata os inimigos recorrendo à ajuda da faca e da poção.
A função faz o link a todos os inimigos para que o jogador possa escolher o que pretende matar. Esta percorre o array dos inimigos e elimina o escolhido do array e consequentemente diminui o número de inimigos existentes. 
@param e, estado do jogo, para adquirir a informação relativa aos inimigos.
*/
void mata(ESTADO e)
{
    int i, j;
    for (i = 0; i < e.num_inimigos; i++) {
        ESTADO ne = e;
        for (j = i; j < e.num_inimigos; j++) {
            ne.inimigo[j].x = e.inimigo[j + 1].x;
            ne.inimigo[j].y = e.inimigo[j + 1].y;
        }
        ne.num_inimigos = e.num_inimigos - 1;
        ne.can = 0;
        printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
               estado2str(ne));
        print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY);
        printf("</a>\n");
    }
}

/**
\brief Função que vê se há inimigos à distância de duas casas do jogador.
@param a, coordenada x do jogador.
@param b, coordenada y do jogador.
@param c, coordenada x do inimigo. 
@param d, coordenada y do inimigo.
@return 1 se existir ou 0 se não existir.
*/
int no_raio(int a, int b, int c, int d)
{
    if (c == a && d == b - 2)
        return 1;
    if (c == a + 2 && d == b - 2)
        return 1;
    if (c == a + 2 && d == b)
        return 1;
    if (c == a + 2 && d == b + 2)
        return 1;
    if (c == a && d == b + 2)
        return 1;
    if (c == a - 2 && d == b + 2)
        return 1;
    if (c == a - 2 && d == b)
        return 1;
    if (c == a - 2 && d == b - 2)
        return 1;
    return 0;
}

/**
\brief Função que mata os inimigos com a bomba.
A função mata os inimigos que se encontram no raio de ação da bomba. Esta percorre o array dos inimigos e elimina-os do array e consequentemente diminui o número de inimigos existentes. De seguida, retiramos a possibilidade de se voltar a usar a bomba.
@param e, estado do jogo, para adquirir a informação relativa aos inimigos e ao jogador.
@return e, estado, resultante de matar os inimigos no raio de ação da bomba.
*/
ESTADO mata_bomba(ESTADO e)
{
    int a = e.jog.x, b = e.jog.y, i = 0, j;
    for (i = 0; i < e.num_inimigos; i++) {
        if (no_raio(a, b, e.inimigo[i].x, e.inimigo[i].y)) {
            for (j = i; j < e.num_inimigos; j++) {
                e.inimigo[j].x = e.inimigo[j + 1].x;
                e.inimigo[j].y = e.inimigo[j + 1].y;
            }
            e.num_inimigos = e.num_inimigos - 1;
            i--;
        }
    }
    e.can = 0;
    return e;
}

/**
\brief Função que prevê para onde vão os inimigos na jogada seguinte e imprime-os.
De acordo com a estratégia definida para o movimento dos inimigos na função move_monster, imprime o seu movimento.
@param e, estado do jogo, para obtermos a informação relativa aos inimigos.
*/
void ilumina(ESTADO e)
{
    int i;
    for (i = 0; i < e.num_inimigos; i++) {
        int a = e.inimigo[i].x + 1;
        int b = e.inimigo[i].y - 1;
        int c = e.inimigo[i].x - 1;
        int f = e.inimigo[i].y + 1;
        if (e.inimigo[i].y == 0 && e.inimigo[i].x > 4) {
            if (valido3(e, c, 0) && (c >= 0 && c < SIZE))
                print_image(c, 0, TAM, GATO);
        }
        if (e.inimigo[i].y == 0 && e.inimigo[i].x < 5) {
            if (valido3(e, a, 0) && (a >= 0 && c < SIZE))
                print_image(a, 0, TAM, GATO);
        }
        if ((e.inimigo[i].y) < 5 && (e.inimigo[i].x) < 5
            && e.jog.y <= SIZE - 5) {
            if (valido3(e, a, b)
                && (a >= 0 && b >= 0 && a < SIZE && b < SIZE))
                print_image(a, b, TAM, GATO);
        }
        if (e.inimigo[i].y < 5 && e.inimigo[i].x > 4
            && e.jog.y <= SIZE - 5) {
            if (valido3(e, c, b)
                && (c >= 0 && b >= 0 && c < SIZE && b < SIZE))
                print_image(c, b, TAM, GATO);
        }
        if (e.inimigo[i].y == (SIZE - 1) && e.inimigo[i].x > 4
            && e.jog.y > SIZE - 5) {
            if (valido3(e, c, b)
                && (c >= 0 && b >= 0 && c < SIZE && b < SIZE))
                print_image(c, b, TAM, GATO);
        }
        if (e.inimigo[i].y == (SIZE - 1) && e.inimigo[i].x < 5
            && e.jog.y > SIZE - 5) {
            if (valido3(e, a, b)
                && (a >= 0 && b >= 0 && a < SIZE && b < SIZE))
                print_image(a, b, TAM, GATO);
        }
        if (e.inimigo[i].y > 4 && e.inimigo[i].x > 4 && e.jog.y > SIZE - 5) {
            if (valido3(e, c, f)
                && (c >= 0 && f >= 0 && c < SIZE && f < SIZE))
                print_image(c, f, TAM, GATO);
        }
        if (e.inimigo[i].y > 4 && e.inimigo[i].x < 5 && e.jog.y > SIZE - 5) {
            if (valido3(e, a, f)
                && (a >= 0 && f >= 0 && a < SIZE && f < SIZE))
                print_image(a, f, TAM, GATO);
        }
    }
}

/**
\brief Função que vê se o jogador, na posição em que se encontra, consegue chegar ao objetivo, que é a porta que dá acesso ao nível seguinte.
@param e, estado do jogo, para obter a informação do objetivo.
@param a, coordenada x onde está o jogador.
@param b, coordenada y onde está o jogador.
@return 1 se alcançar o objetivo ou 0 caso contrário.
*/
int zona_goal(ESTADO e, int a, int b)
{
    if ((a == e.gol.x - 1 || a == e.gol.x - 2) && e.gol.y == b)
        return 1;
    if ((a == e.gol.x + 1 || a == e.gol.x + 2) && e.gol.y == b)
        return 1;
    if (a == e.gol.x && (b == e.gol.y + 1 || b == e.gol.y + 2))
        return 1;
    if (a == e.gol.x - 1 && b == e.gol.y + 1)
        return 1;
    if (a == e.gol.x + 1 && b == e.gol.y + 1)
        return 1;
    if (a == e.gol.x - 2 && b == e.gol.y + 2)
        return 1;
    if (a == e.gol.x + 2 && b == e.gol.y + 2)
        return 1;
    return 0;
}

/**
\brief Função que permite que o jogador seja automático, isto é, jogue sozinho.
A estratégia utilizada para mover o jogador automaticamente é a seguinte: inicialmente, verifica-se se é possível o movimento de duas casas para cima e na hipótese de o ser, averigua-se se há inimigos nesse local, se houver é necessário eliminá-lo. Caso não haja, efetua-se o movimento do jogador e dos inimigos. Caso não seja possível o movimento, implementamos a estratégia anterior para os seguintes deslocamentos: vertical de uma casa, diagonal de uma casa no sentido da esquerda, diagonal de uma casa no sentido da direita, uma casa na horizontal para a direita e uma casa na horizontal para a esquerda, por esta ordem. Caso o jogador se encontre numa posição que o permita movimentar-se diretamente para o objetivo, este efetua a passagem de nível.
@param e, estado do jogo, possibilita conhecer as posições das componentes do tabuleiro.
@return ne, novo estado, resultante do movimento automático do jogador.
*/
ESTADO jogauto(ESTADO e)
{
    ESTADO ne = e;
    int dx = e.jog.x, dy = e.jog.y;
    if (valido4(e, dx, dy - 2)) {
        if (ocupado(e, dx, dy - 2))
            ne = mata_monster(e, dx, dy - 2);
        else {
            ne = move_monster(e);
            ne.jog.x = dx;
            ne.jog.y = dy - 2;
            ne.automatico = 0;
        }
    } else {
        if (valido4(e, dx, dy - 1)) {
            if (ocupado(e, dx, dy - 1))
                ne = mata_monster(e, dx, dy - 1);
            else {
                ne = move_monster(e);
                ne.jog.x = dx;
                ne.jog.y = dy - 1;
                ne.automatico = 0;
            }
        } else {
            if (valido4(e, dx - 1, dy - 1)) {
                if (ocupado(e, dx - 1, dy - 1))
                    ne = mata_monster(e, dx - 1, dy - 1);
                else {
                    ne = move_monster(e);
                    ne.jog.x = dx - 1;
                    ne.jog.y = dy - 1;
                    ne.automatico = 0;
                }

            } else {
                if (valido4(e, dx + 1, dy - 1)) {
                    if (ocupado(e, dx + 1, dy - 1))
                        ne = mata_monster(e, dx + 1, dy - 1);
                    else {
                        ne = move_monster(e);
                        ne.jog.x = dx + 1;
                        ne.jog.y = dy - 1;
                        ne.automatico = 0;
                    }
                } else {
                    if (valido4(e, dx + 1, dy)) {
                        if (ocupado(e, dx + 1, dy))
                            ne = mata_monster(e, dx + 1, dy);
                        else {
                            ne = move_monster(e);
                            ne.jog.x = dx + 1;
                            ne.jog.y = dy;
                            ne.automatico = 0;
                        }
                    } else {
                        if (valido4(e, dx - 1, dy)) {
                            if (ocupado(e, dx - 1, dy))
                                ne = mata_monster(e, dx - 1, dy);
                            else {
                                ne = move_monster(e);
                                ne.jog.x = dx - 1;
                                ne.jog.y = dy;
                                ne.automatico = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    if (zona_goal(e, dx, dy) == 1) {
        ne = inicializar(++e.nivel);
        ne.score = e.score + 1;
    }
    return ne;
}

/**
\brief Função que imprime o sangue em cima do jogador quando este morre.
@param e, estado do jogo, permita obter a informação relativa ao jogador.
*/
void print_sangue(ESTADO e)
{
    print_image(e.jog.x, e.jog.y, TAM, SANGUE);
}

/**
\brief Função que imprime a faca no tabuleiro.
@param e, estado do jogo, para possuir a informação relativa à ajuda.
*/
void print_faca(ESTADO e)
{
    if (e.existe == 1)
        print_image(e.ajuda.x, e.ajuda.y, TAM, FACA);
}

/**
\brief Função que imprime a bomba no tabuleiro.
@param e, estado do jogo, para possuir a informação relativa à ajuda.
*/
void print_explosao(ESTADO e)
{
    if (e.existe == 1)
        print_image(e.ajuda.x, e.ajuda.y, TAM, BOMB);
}

/**
\brief Função que imprime a pocao no tabuleiro.
@param e, estado do jogo, para possuir a informação relativa à ajuda.
*/
void print_pocao(ESTADO e)
{
    if (e.existe == 1)
        print_image(e.ajuda.x, e.ajuda.y, TAM, POCAO);
}

/**
\brief Função que imprime a ajuda, que consiste em iniciar de novo o mesmo nível, no tabuleiro.
@param e, estado do jogo, para possuir a informação relativa à ajuda.
*/
void print_novo(ESTADO e)
{
    if (e.existe == 1)
        print_image(e.ajuda.x, e.ajuda.y, TAM, NOVO);
}

/**
\brief Função coordena as ações do jogo.
Inicialmente verifica se a ajuda que ilumina as casas atacadas pelos inimigos está ativa e se o seu score é múltiplo de 5, se tal se suceder invoca a função ilumina. Se a ajuda requerida for a de pathfinding e o valor do score for divisível por 8, então recorre à função path. Na hipótese do jogador ter conquistado um ataque à distância e ter apelado à ajuda relativa, é acionada a função mata. Caso o rato pretenda movimentar-se para o queijo, é iniciado um novo nível. Sempre que o jogador pretende mover-se para uma casa que contém uma ajuda, este passa a adquiri-la. Dependendo do nível em que este se encontra, a ajuda é diferente. Caso o jogador pretenda se movimentar para um local com um inimigo, esse é morto e consequentemente eliminado do array. Note-se que o jogador apenas efetua um movimento se este for válido, dentro do tabuleiro. E além disso, dá-se o movimento dos inimigos, segundo a função move_monster, aquando do movimento do jogador. Se o jogador e um inimigo se movimentarem para a mesma posição, dá-se a morte do jogador e termina o jogo.
@param e, estado do jogo, que possibilita conhecer as posições das componentes do tabuleiro.
@param dX, um inteiro, indica o número de casas a movimentar-se e o sentido do movimento, relativamente à coordenada x do jogador.
@param dY, um inteiro, indica o número de casas a movimentar-se e o sentido do movimento, relativamente à coordenada y do jogador.
*/
void print_move(ESTADO e, int dX, int dY)
{
    ESTADO ne = e;
    int x = e.jog.x + dX;
    int y = e.jog.y + dY;
    int i, j;
    if (e.help == 2 && e.score % 5 == 0 && e.score != 0)
        ilumina(e);
    if (e.help == 1 && e.score % 8 == 0 && e.score != 0)
        path(e);
    if (e.can == 1 && e.matar == 1)
        mata(e);
    if (e.can == 4 && e.matar == 3)
        mata(e);
    if (x == e.gol.x && y == e.gol.y) {
        ne.acao = 1;
        ne.score = e.score + 2;
        printf("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
               estado2str(ne));
        print_goal(ne);
        printf("</a>\n");
    } else {
        if (x == e.ajuda.x && y == e.ajuda.y) {
            if (e.nivel % 4 == 0) {
                ne.can = 1;
                ne.existe = 0;
                ne.score = e.score + 1;
            } else if (e.nivel % 3 == 0) {
                ne.can = 2;
                ne.existe = 0;
                ne.score = e.score + 1;
            } else if (e.nivel % 5 == 0) {
                ne.can = 3;
                ne.existe = 0;
                ne.score = e.score + 1;
            } else if (e.nivel % 7 == 0) {
                ne.can = 4;
                ne.existe = 0;
                ne.score = e.score + 2;
            }
            printf
                ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                 estado2str(ne));
            if (e.nivel % 4 == 0)
                print_pocao(e);
            else if (e.nivel % 3 == 0)
                print_explosao(e);
            else if (e.nivel % 5 == 0)
                print_novo(e);
            else if (e.nivel % 7 == 0)
                print_faca(e);
            printf("</a>\n");
        } else {
            for (i = 0; i < e.num_inimigos; i++) {
                if (x == e.inimigo[i].x && y == e.inimigo[i].y) {
                    for (j = i; j < e.num_inimigos; j++) {
                        ne.inimigo[j].x = e.inimigo[j + 1].x;
                        ne.inimigo[j].y = e.inimigo[j + 1].y;
                    }
                    ne.num_inimigos = e.num_inimigos - 1;
                    printf
                        ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                         estado2str(ne));
                    print_image(e.inimigo[i].x, e.inimigo[i].y, TAM,
                                ENEMY);
                    printf("</a>\n");
                }
            }
            if (x < 0 || y < 0 || x >= SIZE || y >= SIZE
                || valido2(e, x, y) == 0)
                return;
            ne = move_monster(e);
            for (i = 0; i < e.num_inimigos; i++) {
                if (e.jog.x == e.inimigo[i].x && e.jog.y == e.inimigo[i].y) {
                    print_sangue(e);
                    printf
                        ("<image x=0 y=0 height=500 width=500 xlink:href=http://127.0.0.1/gameover.png>\n");

                    printf
                        ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                         estado2str(ne));
                    printf("</a>\n");
                }
            }
            ne.jog.x = x;
            ne.jog.y = y;
            printf
                ("<a xlink:href=\"http://127.0.0.1/cgi-bin/mec?%s\">\n",
                 estado2str(ne));
            print_square(x, y, TAM);
            printf("</a>\n");
        }
    }

}

/**
\brief Função que permite ao jogador deslocar-se uma casa.
@param e,estado do jogo, para obtermos a informação relativa ao jogador.
*/
void print_player(ESTADO e)
{
    print_image(e.jog.x, e.jog.y, TAM, PLAYER);
    print_move(e, -1, 0);
    print_move(e, +1, 0);
    print_move(e, 0, -1);
    print_move(e, 0, +1);
    print_move(e, -1, -1);
    print_move(e, +1, +1);
    print_move(e, -1, +1);
    print_move(e, +1, -1);
}

/**
\brief Função que imprime os inimigos no ecrã.
@param e, estado do jogo, adquirir a informação relativa aos inimigos.
*/
void print_enemies(ESTADO e)
{
    int i;
    for (i = 0; i < e.num_inimigos; i++)
        print_image(e.inimigo[i].x, e.inimigo[i].y, TAM, ENEMY);
}

/**
\brief Função que imprime os obstáculos no ecrã.
@param e, estado do jogo, para receber a informação relativa aos obstáculos.
*/
void print_walls(ESTADO e)
{
    int i;
    for (i = 0; i < e.num_obstaculos; i++)
        print_image(e.obstaculo[i].x, e.obstaculo[i].y, TAM, WALL);
}

/**
\brief Função que imprime a imagem do bónus do path no ecrã.
*/
void print_bonus1()
{
    printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n",
           505, 40, 300, 300, BONUS1);
}

/**
\brief Função que imprime a imagem do bónus do ilumina os gatos no ecrã.
*/
void print_bonus2()
{
    printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n",
           505, 40, 300, 300, BONUS2);
}

/**
\brief Função que imprime a imagem do bónus do automático no ecrã.
*/
void print_bonus3()
{
    printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n",
           505, 40, 300, 300, BONUS3);
}

/**
\brief Função que imprime a imagem do score no ecrã.
*/
void print_score()
{
    printf("<image x=%d y=%d height=%d width=%d xlink:href=\"%s\"/>\n",
           500, 460, 200, 200, SCORE);
}

/**
\brief Função que gera números aleatórios, entre 0 e SIZE-1 inclusive.
@return r,um inteiro, escolhido aleatoriamente.
*/
int gera_numeros()
{
    int r;
    r = rand() % SIZE;
    return r;
}

/**
\brief Função principal.
Na hipótese de o jogador pretender movimentar-se para o localdo objetivo, ou seja, caso em que a ação toma o valor de 1, inicia-se o nível seguinte, pelo que se incrementa o valor deste. Se o botão destinado a iniciar o jogo for acionado, o que equivale a que o valor de ação é 2, inicializa-se o jogo, pelo que o nível torna a ser zero. Sempre que jogador obtém e requer a ajuda de inicilizar o mesmo nível, invocamos a função inicializar sendo o valor do nível o mesmo. Na condição do jogador automático e do score ser múltiplo de 11, é solicitada a função jogauto. Quando o rato adquire a ajuda da bomba e a aciona, é chamada a função mata_bomba. Os bónus são imprimidos de acordo com o score do jogador. Nesta função, são imprimidos todos os compenentes do jogo. Além disso, são requeridas as funções responsáveis pelos movimentos.
*/
void parse()
{
    srand(time(NULL));
    ESTADO e;
    char r;
    char *args = getenv("QUERY_STRING");
    if (strlen(args) == 0)
        e = inicializar(0);
    else
        e = str2estado(args);
    if (e.acao == 1) {
        r = scr(e);
        e = inicializar(++e.nivel);
        e.score = r;
    }
    if (e.acao == 2)
        e = inicializar(0);
    if (e.help == 4 && e.can == 3)
        e = inicializar(e.nivel);
    if (e.automatico == 1 && e.nivel % 6 == 0 && e.nivel != 0)
        e = jogauto(e);
    if (e.can == 2 && e.matar == 2)
        e = mata_bomba(e);
    print_board();
    print_button_novo_jogo(e);
    print_pathfinding(e);
    print_button_monstro(e);
    print_button_pocao(e);
    print_button_faca(e);
    print_button_explosao(e);
    print_button_novo(e);
    print_button_auto(e);
    print_enemies(e);
    print_walls(e);
    print_score();
    print_goal(e);
    if (e.score % 5 == 0 && e.score != 0)
        print_bonus2();
    if (e.score % 8 == 0 && e.score != 0)
        print_bonus1();
    if (e.nivel % 6 == 0 && e.nivel != 0)
        print_bonus3();
    if (e.nivel % 4 == 0)
        print_pocao(e);
    else if (e.nivel % 3 == 0)
        print_explosao(e);
    else if (e.nivel % 5 == 0)
        print_novo(e);
    else if (e.nivel % 7 == 0)
        print_faca(e);
    print_player(e);
    printf("<B>");
    printf("%d", scr(e));
    printf("</B>");

}
