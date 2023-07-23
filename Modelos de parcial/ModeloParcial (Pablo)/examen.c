#include <stdio.h>
#include "examen.h"

//----------------------------------------CONTAR PALABRAS-------------------------------------------------
int _contarPalabras(const char* nomArc, char* palMasLarga, int* cantVeces){
    FILE* pf = fopen(nomArc, "rt"); //abre archivo
    if(!pf)
    return 1;
    int cantPalabras = 0;
    char linea[150];
    char* ini;
    char* fin;
    *cantVeces = 1;
    while(fgets(linea, sizeof(linea), pf)) //recibe lineas uno a uno
    {
        ini = linea;
        fin = linea;

        while(proximaPalabra_alu(&ini, &fin)) //busca palabra
        {
            if(fin-ini > strlen_alu(palMasLarga)) //Una mas larga nueva
            {
                strncpy_alu(palMasLarga, ini, fin-ini); //reinicia cont y guarda la nueva
                *cantVeces = 1;
            }
            else if(strcmp_alu(ini, palMasLarga) == 0) //es igual a la mas larga
                (*cantVeces)++; // 1 mas
            ini = fin;
            cantPalabras++; //suma cant palabras
        }
    }
    fclose(pf); //cierra archivo
    return cantPalabras;
}

//------------------------------------- FUNCIONES DE CONTAR PALABRAS-------------------------------------------------
int strncpy_alu(char* dest, const char* src, size_t tam) //strcpy de n cantidad ya que no tengo \0
{
    int i;
    for(i=0; i<tam; i++)
        *(dest+i) = *(src+i);
    return 0;
}

int strlen_alu(const char* cad) //strlen promedio
{
    int ce=0;
    while(*(cad+ce))
        ce++;
    return ce;
}

char toLower_alu(char carac)
{
    if(carac >= 'A' && carac <='Z') //si es mayuscula suma el ascii necesario
        return carac+32;
    return carac;
}

int strcmp_alu(const char* cad1, const char* cad2)
{
    while(*cad1 && *cad2) //mientras no se acabe ninguna cadena
    {
        if(toLower_alu(*cad1) != toLower_alu(*cad2)) //tolower por si tiene mayusculas
            return *cad1-*cad2; //retorna diferencia
        cad1++;
        cad2++;
    }
  return 0;
}

int isAlpha_alu(char* carac)
{
    if((*carac >= 'A' && *carac <='Z') || (*carac >= 'a' && *carac <='z')) //si esta entre esos ascii entonces es letras
        return 1;
    return 0;//no es letras
}

char* proximaPalabra_alu(char** ini, char** fin)
{
    while(!isAlpha_alu(*ini) && **ini != '\0') //busca la sig letra siempre y cuando no se acabe mi cadena
        (*ini)++;
    *fin=*ini;
    while(isAlpha_alu(*fin)) //busca el fin de la cadena
        (*fin)++;
    if(*ini!=*fin) //si estan en dif lugares significa que es una palabra
        return *ini;
    return NULL;  //como fin no se movió significa que no es una palabra
}

//----------------------------------------FIN DE CONTAR PALABRAS-------------------------------------------------




//-------------------------------------------BUSQUEDA BINARIA----------------------------------------------------

/*
Va dividiendo a la mitad y busca si el valor es menor o mayor,
dependiendo el resultado recorta los limites del vector
*/

void* _bbinaria(const void *clave, const void *vec, size_t ce, size_t tam, int cmpB(const void *, const void *)){
    int cmp;
    while(ce>0)
    {
        cmp = cmpB(vec+(ce/2)*tam, clave);

        if(cmp == 0)
            return (void*)(vec+(ce/2)*tam);
        else if(cmp < 0)
            vec+=tam*((ce/2)+1);

        ce /= 2;
    }
    return NULL;
}

//-------------------------------------------FIN DE BUSQUEDA BINARIA-------------------------------------------------

//-------------------------------------------------MATRICES----------------------------------------------------------


int _sumTrianDerEntreDiag(int mat[][MAX_COL], int filas){
    int i, j, sum = 0;
    for(j=filas-1; j>filas/2; j--)  //Lee desde la ultima columna
        for(i=filas-j; i<j; i++)    //Lee las filas de dicha columna
            sum += mat[i][j];       //Suma
    return sum;                     //Devuelve la suma
}

int _sumTrianInfEntreDiag(int mat[][MAX_COL], int filas){
    int i, j, sum = 0;
    for(j=filas-1; j>filas/2; j--)  //Lee desde la ultima fila
        for(i=filas-j; i<j; i++)    //Lee las columnas de dicha fila
            sum += mat[j][i];       //Suma
    return sum;                     //Devuelve la suma
}

//-------------------------------------------------FIN DE MATRICES--------------------------------------------------
