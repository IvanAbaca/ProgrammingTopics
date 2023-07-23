#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "telemetria.h"

int verificarTam(const char* arch)
{
    FILE *archT = fopen(arch,"rb"); //Abro el archivo en modo lectura

    if(!archT)
        return 0;

    fseek(archT,0,SEEK_END); //Muevo el puntero del archivo al final del mismo

    if(ftell(archT)%tamReg != 0) //ftell me da el tamaño en bytes desde el principio hasta donde estoy. Si al tam final lo divido por el tam del registro me da la cantidad
        return 0;

    fclose(archT);
    return 1;
}

float obtenerVoltaje(FILE* arch, int iniReg)
{
    int volt;
    char hexa[20];
    fseek(arch,offsetVol+iniReg,SEEK_SET); //subsistema PCS está en 1604, offset 750 = byte 2354. Voy sumando el num de registro en el que estoy (0,4000,8000).

    fread(&volt,tamVol,1,arch); //Leo el valor del voltaje.
    //printf("vol d: %d x: %X\n", volt, volt);

    sprintf(hexa, "%X", volt); //Lo escribo como cadena en Hexadecimal.

    volt = encoding(tamVol,hexa); //Envio la cadena al encoding.

    return ((float)volt*0.01873128+(-38.682956)); // Aplico el calculo para obtener el valor de ingeniería final.

}

unsigned int encoding(int cant, char* hexa) // Si el primer bit no es 12 entonces quiere decir que esta en Little-Endian (por eso hay que modificarlo).
{
    int i;
    unsigned int valor=0;
    unsigned int a = 0x1234;
    char* p = (char*)&a;

    if(*p != 0x12) // Si el primer bit no es 12 entonces quiere decir que esta en Little-Endian (por eso hay que modificarlo).
        for(i=0;i<cant/2;i++)
        {
            intercambio(hexa+(i*2), (hexa+(cant-i)*2)-1);
            intercambio(hexa+(i*2)+1, (hexa+(cant-i)*2));
        }
    /*  el primer intercambio toma la primera letra y la posiciona en la penultima posicion
            el segundo intercambio toma la segunda letra y la posiciona en la ultima posicion
            (De esta manera intercambia de a 2 letras)
            Y despues realiza lo mismo con los siguientes 2 caracteres hasta terminar con los ciclos

            Ejemplo 2 bytes:
                AABB CCDD
                DABB CCAD
                DDBB CCAA
                DDCB BCAA
                DDCC BBAA
        */

    sscanf(hexa,"%x",&valor);
    return valor;
}
void intercambio(void* hexa, void* pos)
{
    char aux;
    aux= *(char*)hexa;
    *(char*)hexa = *((char*)pos-1);
    *((char*)pos-1)=aux;
}

char* obtenerFecha(FILE* arch, char* fecha, size_t tamFecha, int iniReg) // Crear un short int y castearlo a char para ver en donde esta el bit mas significativo.
{

    unsigned int fechaInt=0;
    char hexa[20];

    fseek(arch,offsetFecha+iniReg,SEEK_SET); // Voy al primer registro y a donde se encuentra la fecha.
    fread(&fechaInt,TamBFecha,1,arch); // Me la guardo en fecha int.


    if(fechaInt <= 0x0fffffff)
    {
        hexa[0] = '0';
        sprintf(hexa+1, "%X", fechaInt);
    }
    else
    {
        sprintf(hexa, "%X", fechaInt);
    }

    time_t tiempo = (time_t)encoding(TamBFecha, hexa); // Lo paso a segundos.
    //printf("\n%ld", (long int)tiempo);

    struct tm fecha_inicial; //https://www.zator.com/Cpp/E5_5_1a.htm
    fecha_inicial.tm_sec = 0;
    fecha_inicial.tm_min = 0;
    fecha_inicial.tm_hour = 0;
    fecha_inicial.tm_mday = 6;// Enero = 6
    fecha_inicial.tm_mon = 0;
    fecha_inicial.tm_year = 80; // Año desde 1980
    fecha_inicial.tm_wday = 0;
    fecha_inicial.tm_yday = 0;
    fecha_inicial.tm_isdst = -1;

    time_t tiempo_transcurrido = tiempo + mktime(&fecha_inicial); //Paso la fecha inicial a un numero y se la sumo a la fecha leida anteriormente.

    struct tm *fecha_resultante = localtime(&tiempo_transcurrido); // Lo transformo a una estructura.

    strftime(fecha, tamFecha, "%d/%m/%Y %H:%M:%S", fecha_resultante); // Convertir la estructura time a una cadena de fecha

    //printf("\nFecha: %s\n", fecha);
    return fecha;
}

void obtenerRegistros(const char* arch)
{
    FILE *archT = fopen(arch, "rb");    //Leo datos del archivo de telemetría
    FILE* pf = fopen("arch.csv", "wt"); //Los escribo en el csv

    char fecha[50];
    int iniReg = 0;

    if(!archT)
        exit(0);

    if(!pf)
        exit(0);

    fseek(archT,0,SEEK_END);
    long int end = ftell(archT); //Guardo el tamaño total de ArchT 129592000
    //printf("%ld\n\n\n", end);

    fseek(archT,0,SEEK_SET); //levanto el primer registro

    while((ftell(archT)+tamReg)!=end) //
    {
        exportarArchivoACSV(pf,obtenerVoltaje(archT,iniReg), obtenerFecha(archT, fecha, sizeof(fecha), iniReg)); //En el csv guardo el valor que me retorne oVolt, y obFecha
        fseek(archT, iniReg, SEEK_SET);

        iniReg+=tamReg; //Sumo de a 4000 (tam del reg)
    }
    //printf("%d\n",i);

    fclose(archT);
    fclose(pf);
}

void exportarArchivoACSV(FILE* pf, float volt, char* fecha)
{
    fprintf(pf, "%.2f;%s\n", volt, fecha);
}
