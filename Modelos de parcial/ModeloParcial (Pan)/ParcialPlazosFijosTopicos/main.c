#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Fecha/Fecha.h"
#include "../SolucionParcialPlazosFijosTopicos/SolucionParcialPlazosFijos.h"


PlazoFijo* cargarVectorPF_ALU(const char* nombrePlazosFijos, int* ce);
void procesarPF_ALU(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso);
int trozarVariable(char* linea, PlazoFijo* pPlazo);
int cmpPlazo(const void* a , const void* b);

int main(int argc, char* argv[])
{
	generarArchivos(argv[1], argv[2]);

	if(argc != 4)
	{
		puts("Cantidad incorrecta de parámetros.");
		return 1;
	}

	puts("Cuentas antes de actualizar:");
	mostrarCuentas(argv[1]);

	FILE* cuentasDat = fopen(argv[1], "r+b");

	if(!cuentasDat)
		return 2;

	Fecha fechaProceso;
	int fechaOk = txtAFecha(argv[3], &fechaProceso);

	if(!fechaOk)
		return 3;

	PlazoFijo* plazosFijosVec = NULL;

	int ce;
    //plazosFijosVec = cargarVectorPF    (argv[2], &ce);
	plazosFijosVec = cargarVectorPF_ALU(argv[2], &ce);

    //procesarPF(cuentasDat, plazosFijosVec, ce, &fechaProceso);
	procesarPF_ALU(cuentasDat, plazosFijosVec, ce, &fechaProceso);

	fclose(cuentasDat);

	puts("\nCuentas despues de actualizar:");
	mostrarCuentas(argv[1]);

    return 0;
}

int trozarVariable(char* linea, PlazoFijo* pPlazo)
{
    char* pe = strchr(linea, '\n');
    if(!pe)
        return 1;

    *pe = '\0';
    pe = strrchr(linea, '|');
    sscanf(pe+1, "%d", &(pPlazo->dias));

    *pe = '\0';
    pe = strrchr(linea, '/');
    sscanf(pe+1, "%d", &(pPlazo->fechaConstitucion.anio));

    *pe = '\0';
    pe = strrchr(linea, '/');
    sscanf(pe+1, "%d", &(pPlazo->fechaConstitucion.mes));

    *pe = '\0';
    pe = strrchr(linea, '|');
    sscanf(pe+1, "%d", &(pPlazo->fechaConstitucion.dia));

    *pe = '\0';
    pe = strrchr(linea, '|');
    sscanf(pe+1, "%f", &(pPlazo->interesAnual));

    *pe = '\0';
    pe = strrchr(linea, '|');
    sscanf(pe+1, "%f", &(pPlazo->monto));

    *pe = '\0';
    pe = strrchr(linea, '|');
    sscanf(pe+1, "%d", &(pPlazo->cuenta));

    *pe = '\0';
    sscanf(linea, "%d", &(pPlazo->nroPF));

    return 0;
}

PlazoFijo* cargarVectorPF_ALU(const char* nombrePlazosFijos, int* ce)
{
    FILE* pf = fopen(nombrePlazosFijos, "rt");
    if(!pf)
        return NULL;
    fseek(pf, 0, SEEK_END);
    *ce = ftell(pf)/sizeof(PlazoFijo);
    fseek(pf, 0, SEEK_SET);

    char linea[40];
    PlazoFijo* pPlazo = malloc(sizeof(PlazoFijo)*(*ce));

    while(fgets(linea, 40, pf))
    {
        trozarVariable(linea, (pPlazo));
        pPlazo++;
    }
    pPlazo-=(*ce);
    void* cmp = cmpPlazo;
    qsort(pPlazo, *ce, sizeof(PlazoFijo), cmp);

    fclose(pf);
    return pPlazo;
}


int cmpPlazo(const void* a , const void* b)
{
    PlazoFijo* pa = (PlazoFijo*)a;
    PlazoFijo* pb = (PlazoFijo*)b;

    if(pa->cuenta > pb->cuenta)
        return 1;
    else if(pa->cuenta < pb->cuenta)
        return -1;
    return 0;
}

void procesarPF_ALU(FILE* cuentasDat, PlazoFijo* plazosFijosVec, int ce, Fecha* fechaProceso)
{
    Cuenta cuenta;
    fread(&cuenta, sizeof(cuenta), 1, cuentasDat);
    PlazoFijo* pIni = plazosFijosVec;

    while(ce>0)
    {
        if(cuenta.cuenta == plazosFijosVec->cuenta)
        {
            if(plazosFijosVec->dias - difEnDiasEntreFechas(&(plazosFijosVec->fechaConstitucion), fechaProceso) < 0)
                cuenta.saldo = cuenta.saldo + plazosFijosVec->monto + (plazosFijosVec->interesAnual/100 * plazosFijosVec->dias/365 * plazosFijosVec->monto);
            plazosFijosVec++;
            ce--;

        }
        else if(cuenta.cuenta < plazosFijosVec->cuenta)
        {
            fseek(cuentasDat, (long)sizeof(Cuenta)*-(1L), SEEK_CUR);
            fwrite(&cuenta, sizeof(Cuenta), 1, cuentasDat);
            fflush(cuentasDat);
            fread(&cuenta, sizeof(cuenta), 1, cuentasDat);
        }
        else
        {
            plazosFijosVec++;
            ce--;
        }
    }
    free(pIni);
}


/*
PlazoFijo
nroPF:              Entero
cuenta:             Entero
monto:              Real
interesAnual:       Real
fechaConstitución:  Fecha
dias:               Entero

Cuenta
cuenta:     Entero
cliente:    Texto
saldo:      Real

*/
