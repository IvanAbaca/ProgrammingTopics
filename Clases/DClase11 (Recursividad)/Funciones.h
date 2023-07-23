#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>


unsigned int factorial(unsigned int num);
int strlenMio(const char* cad);
void mostrarInt(void* vec);
int map(void* vec, size_t tam, int ce, void accion(void*));
int esPalindromo(const char* cad);
int isAlpha(const char* cad);
#endif // FUNCIONES_H_INCLUDED
