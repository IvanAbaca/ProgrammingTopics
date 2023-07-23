#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define TAM 10
/*
Crear lotes
Cargar vec
operacionVectores
cargarResult con formato: a +- b = c
*/
int crearArchTxt(const char* arch1, const char* arch2);
void* leerArchTxt(const char* arch, void cargarVec(FILE*, void*, char));
void cargarVec_entero(FILE* pf, void* vec, char operacion);


#endif // FUNCIONES_H_INCLUDED
