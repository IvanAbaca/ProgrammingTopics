#ifndef TELEMETRIA_H_INCLUDED
#define TELEMETRIA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ArchTelem "HKTMST.bin"
#define ArchAExcel
#define tamReg 4000
#define offsetVol 2354
#define offsetFecha 100
#define tamVol 2
#define TamBFecha 4

typedef struct
{
    int tm_yday;
    int tm_wday;
    int tm_year;
    int tm_mon;
    int tm_mday;
    int tm_hour;
    int tm_min;
    int tm_sec;

}tm;

int verificarTam(const char*);
float obtenerVoltaje(FILE* arch, int i);
unsigned int encoding(int, char*);
void intercambio(void* hexa, void* pos);
char* obtenerFecha(FILE* arch, char* fecha, size_t tamFecha, int i);
void obtenerRegistros(const char* arch);
void exportarArchivoACSV(FILE* pf, float volt, char* fecha);


#endif // TELEMETRIA_H_INCLUDED
