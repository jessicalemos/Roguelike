#include <stdio.h>
#include "estado.h"

#define MAX_BUFFER		10240

/**
\brief Função que converte um estado para string.
@param e, estado a converter.
@return buffer, a string que corresponde ao estado fornecido.
*/
char *estado2str(ESTADO e)
{
    static char buffer[MAX_BUFFER];
    char *p = (char *) &e;
    int i;

    buffer[0] = 0;

    for (i = 0; i < sizeof(ESTADO); i++)
        sprintf(buffer, "%s%02x", buffer, p[i]);

    return buffer;
}

/**
\brief Função que converte uma string para um estado.
@param *argumentos, string a converter.
@return e, o estado que corresponde à string fornecida.
*/
ESTADO str2estado(char *argumentos)
{
    ESTADO e;
    char *p = (char *) &e;
    int i;

    for (i = 0; i < sizeof(ESTADO); i++, argumentos += 2) {
        int d;
        sscanf(argumentos, "%2x", &d);
        p[i] = (char) d;
    }

    return e;
}
