#ifndef EXAMEN_H_INCLUDED
#define EXAMEN_H_INCLUDED

#define MAX_COL 100
#define MAXNOMEMP 31
typedef struct{
    int dni;
    char nomYAp[MAXNOMEMP];
    double sueldo;
}tEmpleado;

//FUNCIONES ALUMNO
char* proximaPalabra_alu(char** ini, char** fin);
int isAlpha_alu(char* carac);
int strcmp_alu(const char* cad1, const char* cad2);
int strlen_alu(const char* cad);
int strncpy_alu(char* dest, const char* src, size_t tam);
char toLower_alu(char carac);


//FIN DE FUNCIONES DE ALUMNO

void* _bbinaria(const void *clave, const void *vec, size_t ce, size_t tam, int cmp(const void *, const void *));
int _contarPalabras(const char* nomArc, char* palMasLarga, int* cantVeces);
int _sumTrianDerEntreDiag(int mat[][MAX_COL], int filas);
int _sumTrianInfEntreDiag(int mat[][MAX_COL], int filas);



int sumTrianDerEntreDiag(int mat[][MAX_COL], int filas);
int sumTrianInfEntreDiag(int mat[][MAX_COL], int filas);
void* bbinaria(const void *clave, const void *vec, size_t ce, size_t tam, int cmp(const void *, const void *));
//void* rbbinaria(const void *clave, const void *vec, size_t ce, size_t tam, int cmp(const void *, const void *));
int cmpEmpladoNombre(const void*, const void*);
int cmp_enteros(const void* a, const void* b);
int cmp_str(const void* a, const void* b);
int crearLotePruebaTxtFrasesSim(const char* nomArch);
int contarPalabras(const char* nomArc, char* palMasLarga, int* cantVeces);
#endif // EXAMEN_H_INCLUDED
