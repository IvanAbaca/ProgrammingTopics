#include "Funciones.h"

unsigned int factorial(unsigned int num)
{
    if(num==0)
        return 1;
    return num*factorial(num-1);
}

int strlenMio(const char* cad)
{
    if(!*cad)
        return 0;
    return 1 + strlenMio(cad+1);
}

int map(void* vec, size_t tam, int ce, void accion(void*))
{
    if(ce!=0)
    {
        accion(vec);
        return map(vec+tam, tam, ce-1, accion);
    }
    accion(vec);
    return 0;
}

void mostrarInt(void* vec)
{
    printf("%d", *(int*)vec);
}
/*
int esPalindromo(const char* cad)
{
    char* fin = strlenMio(cad);

    if(alpha)
    {

    }
    if()
    {

    }
    if()
    {

    }
    if()
    {

    }
    return 0;
}
*/
int isAlpha(const char* cad)
{
    if(*cad >64 && *cad<91 && *cad >96 && *cad<123)
        return 1;
    return 0;
}
