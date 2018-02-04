#include <stdio.h>
#include "parser.h"

/**
\brief Função que abre o HTML.
*/
void print_header()
{
    printf("content-type: text/html\n\n");
    printf("<body>\n");
    printf("<svg width=800 height=600>\n");

}

/**
\brief Função que fecha o HTML.
*/
void print_footer()
{
    printf("</svg>\n");
    printf("</body>\n");
}

/**
\brief Função que permite visualizar o jogo.
@return 0, inteiro que indica se a função foi executada com sucesso.
*/
int main()
{
    print_header();
    printf
        ("<rect x=510 y=0 height=500 width=500 style=\"fill:#999999\"/>\n");
    parse();
    print_footer();
    return 0;
}
