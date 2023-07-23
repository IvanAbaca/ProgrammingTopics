#include "Funciones.h"
#define arch1 "arch1.txt"
#define arch2 "arch2.txt"

int main()
{
    crearArchTxt(arch1, arch2);
    int* vec1 = (int*) leerArchTxt(arch1, (void*) cargarVec_entero);
    int* vec2 = (int*) leerArchTxt(arch2, (void*) cargarVec_entero);
    int i;
    char operacion = '+';
    if(vec2[0] < 0)
        operacion = ' ';
    for(i=0; i<TAM; i++)
        printf("\n%d%c%d = %d", vec1[i], operacion, vec2[i], vec1[i]+vec2[i]);



    return 0;
}
