#include "Funciones.h"

/*
Crear arch1.txt arch2.txt
Ambos tienen los datos de un vector
Ambos tienen como 1er registro la cant de elementos del vector
Ejemplo 1er registro : (dim1)
El segundo registro tiene "+" o "-" y el tam del dato
Los siguientes registros son el vector desordenado
Ejemplo de 3er registro en adelante: pos|valor
Verificar que tengan la misma dimension
En caso de no tener misma dimension dejar como neutro

Funciones:
Crear lotes
Cargar vec
operacionVectores
cargarResult con formato: a +- b = c

Simular la funcion strcat()


*/
void* leerArchTxt(const char* arch, void cargarVec(FILE*, void*, char))
{
    FILE* pf = fopen(arch, "rt");
    if(!pf)
        return NULL;
    int ce, tam, i;
    char operacion;

    fscanf(pf, "(%d)\n", &ce);
    fscanf(pf, "%c%d\n", &operacion, &tam);

    void* vec = malloc(tam*ce);

    for(i=0; i<ce; i++)
        cargarVec(pf, vec, operacion);

    fclose(pf);
    return vec;
}

void cargarVec_entero(FILE* pf, void* vec, char operacion)
{
    int pos, valor, *vecInt = (int*) vec;
    fscanf(pf, "%d|%d\n", &pos, &valor);
    if(operacion == '-')
        valor*=-1;
    *(vecInt+pos) = valor;
}

int crearArchTxt(const char* arch1, const char* arch2)
{
    FILE* pf1 = fopen(arch1, "wt");
    if(!pf1)
        return 1;
    FILE* pf2 = fopen(arch2, "wt");
    if(!pf2)
        return 1;

    int vec1[TAM] = {5,6,7,4,2,6,9,1,3,7};
    int vec2[TAM] = {4,6,9,8,5,3,1,6,7,3};
    char operacion1 = '+';
    char operacion2 = '+';
    //char formato[3] = "%d";

    fprintf(pf1, "(%d)\n", TAM);
    fprintf(pf1, "%c%d\n", operacion1, (int)sizeof(int));
    fprintf(pf1, "%d|%d\n", 1, vec1[1]);
    fprintf(pf1, "%d|%d\n", 7, vec1[7]);
    fprintf(pf1, "%d|%d\n", 0, vec1[0]);
    fprintf(pf1, "%d|%d\n", 6, vec1[6]);
    fprintf(pf1, "%d|%d\n", 4, vec1[4]);
    fprintf(pf1, "%d|%d\n", 8, vec1[8]);
    fprintf(pf1, "%d|%d\n", 5, vec1[5]);
    fprintf(pf1, "%d|%d\n", 3, vec1[3]);
    fprintf(pf1, "%d|%d\n", 9, vec1[9]);
    fprintf(pf1, "%d|%d\n", 2, vec1[2]);

    fprintf(pf2, "(%d)\n", TAM);
    fprintf(pf2, "%c%d\n", operacion2, (int)sizeof(int));
    fprintf(pf2, "%d|%d\n", 9, vec2[9]);
    fprintf(pf2, "%d|%d\n", 4, vec2[4]);
    fprintf(pf2, "%d|%d\n", 6, vec2[6]);
    fprintf(pf2, "%d|%d\n", 7, vec2[7]);
    fprintf(pf2, "%d|%d\n", 2, vec2[2]);
    fprintf(pf2, "%d|%d\n", 5, vec2[5]);
    fprintf(pf2, "%d|%d\n", 0, vec2[0]);
    fprintf(pf2, "%d|%d\n", 8, vec2[8]);
    fprintf(pf2, "%d|%d\n", 1, vec2[1]);
    fprintf(pf2, "%d|%d\n", 3, vec2[3]);

    fclose(pf1);
    fclose(pf2);
    return 0;
}
