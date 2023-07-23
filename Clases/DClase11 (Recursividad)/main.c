#include "Funciones.h"

int main()
{
    unsigned int i;
    printf("\nEJEMPLO 1 DE RECURSIVIDAD\n");
    for(i=0; i<16; i++)
        printf("\nFACTORIAL DE %02d = %d", i, factorial(i));

    const char* cad = "1234";
    printf("\n\nEJEMPLO 2\n\nLong de %s: %d", cad, strlenMio(cad));

    printf("\n\nEJEMPLO 3\n\n");
    int vec[9]={1,2,3,4,5,6,7,8,9};
    map(vec, 4, 9-1, (void*)mostrarInt);
    return 0;
}

/*
Abaca
Ivan
Argentina
Holanda 682
22 years old
Work: Upholsterer
Married: No
*/ 