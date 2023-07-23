#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int cod;
    int codPais;
    int editor;
    int nroArt;
    int verif;

} t_isbn;

typedef struct
{
    t_isbn isbn;
    int stock;

} t_libro;

//HECHAS
int crearText(const char* arch);
int crearBin(const char* arch);
int mostrarArchBin(const char* arch);

//NO HECHAS
int actualizar(const char* bin, const char* txt, int cmp(void*, void*));
int isISBN(char* cad);
int trozarVariable(char* cad, char corte, t_libro* lib);
int cmp(void* bin, void* txt);

#endif // FUNCIONES_H_INCLUDED
