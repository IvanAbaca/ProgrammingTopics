#include "Funciones.h"


#define archBin "archbin.dat"
#define archTxt "archtxt.txt"
/*
crear archivo bin
crear archuvo text
Actualizar de bin con text
    -suma cant si existe
    -error
formato:
int - 2 int - 3 int - 4 int - 1 int -> 18 caracteres

impar+3*par

*/
int main()
{
    printf("Hello world!\n");
    crearBin(archBin);
    crearText(archTxt);
    mostrarArchBin(archBin);
    actualizar(archBin, archTxt, (void*)cmp);
    mostrarArchBin(archBin);
    return 0;
}



