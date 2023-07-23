#include "Funciones.h"


//Ejemplos hechos:
//sscanf    -> lee en una cadena segun formato y retorna num de datos asignados
//fprintf   -> guarda en archivo segun formato y retorna longitud de cad
//Ejemplos que hay que hacer:
//fscanf    -> lee de un archivo, guarda los datos segun formato y retorna num de asignaciones
//sprintf   -> guarda en una cadena segun formato y retorna longitud de cad 


int grabarArchivoTxt(const char* archT)
{
    int i;
    tAlumno alu[]={
                      {10,9.5,23,1001,'M'},
                      {20,5.5,21,1003,'F'},
                      {30,8.0,25,1090,'X'}
                    };

    FILE* pfT= fopen(archT,"wt");

    if(!pfT)
        return 1;

    for(i=0;i<(sizeof(alu)/sizeof(tAlumno));i++)
    {
        fprintf(stdout,"%d|%.2f|%d|%d|%c\n",alu[i].dni,alu[i].promedio,alu[i].edad,alu[i].legajo,alu[i].genero);
        //fprintf(stdout,"%d|%d|%.2f|%d|%c\n",alu[i].legajo,alu[i].dni,alu[i].promedio,alu[i].edad,alu[i].genero);
    }

    fclose(pfT);

    return 0;
}

int leerArchTexto(const char* arch) //Se puede usar fscanf (creo)
{
    char linea[10]; //num<=MAXLINE
    FILE *pf = fopen(arch, "wt");
    if(!pf)
        return 1;
    while(fgets(linea, sizeof(linea)-1, pf)) //-1 para no levantar el \0
        puts(linea);
    return 0;
}

int ejercicio5_11(const char* arch1, const char* arch2)
{
    char linea[50];
    char encabezado[5];
    /*  ENCABEZADO
    d   ->dni
    l   ->legajo
    e   ->edad
    p   ->promedio
    g   ->genero
    */

    int i;
    tAlumno alu;

    FILE *pf1 = fopen(arch1, "rt");
    if(!pf1)
        return 1;
    
    FILE *pf2 = fopen(arch2, "wt");
    if(!pf2)
        return 1;

    fgets(linea, sizeof(linea)-1, pf1);

    char *pe = strrchr(linea, '\n');
    if(!pe)
        return 1;

    for(i=0; i<5; i++) //CARGA ENCABEZADO
    {
        *pe = '\0';
        pe = strrchr(linea, '|');
        encabezado[i] = pe+1;
    }
    
    while(fgets(linea, sizeof(linea), pf1))
    {
        trozado(linea, encabezado, &alu);
        fwrite(&alu, sizeof(tAlumno), 1, pf2);
        fflush(pf2);
    }
    return 0;
}

int trozazoAlum(char* linea, char* encabezado, tAlumno* pAlu)
{
    //  1|2|3|4|5\n
    char *pe = strrchr(linea, '\n');
    if(!pe)
        return 1;

    for(i=4; i<=0; i++) //CARGA LINEA
    {
        *pe = '\0';
        pe = strrchr(linea, '|');
        if(encabezado[i] == 'd')
            sscanf(pe+1,"%d", &(pAlu->dni));
        if(encabezado[i] == 'l')
            sscanf(pe+1,"%d", &(pAlu->legajo));
        if(encabezado[i] == 'e')
            sscanf(pe+1,"%d", &(pAlu->edad));
        if(encabezado[i] == 'p')
            sscanf(pe+1,"%f", &(pAlu->prom));
        if(encabezado[i] == 'g')
            pAlu->genero = pe+1;
    }
    return 0;
}


int trozarAlumnosFijo(const char* arch, char* linea, tAlumno* pAlu)
{
    char *pe = strchr(linea, '\n');
    if(!pe)
        return 1;
    *pe = '\0';
     pe-=sizeof(pAlu->prom);
    sscanf(pe,"%f", &(pAlu->prom));

    *pe = '\0';
    pe-=sizeof(pAlu->NyAp);
    strncpy(pAlu->NyAp, pe, sizeof(pAlu->NyAp));

    *pe = '\0';
    pe-=sizeof(pAlu->dni);
    sscanf(pe, "%d", &pAlu->dni);

    return 0;
}

int trozarAlumnosVariable(char* linea, tAlumno* pAlu)
{
    char *pe = strrchr(linea, '|');
    if(!pe)
        return 1;
    *pe = '\0';
    sscanf(pe+1,"%f", &(pAlu->prom));
    pe = strchr(linea, '|');

    *pe = '\0';
    strcpy(pAlu->NyAp, pe+1);
    pe = strchr(linea, '|');

    *pe = '\0';
    sscanf(pe+1,"%d", &(pAlu->dni));

    return 0;
}

int leerArchTexto(const char* arch) //Se puede usar fscanf (creo)
{
    char linea[10]; //num<=MAXLINE
    FILE *pf = fopen(arch, "wt");
    if(!pf)
        return 1;
    while(fgets(linea, sizeof(linea)-1, pf)) //-1 para no levantar el \0
        puts(linea);
    return 0;
}

int crearLoteCampoVariable(const char* arch) //se puede usar fprintf
{

    FILE *pf = fopen(arch, "wt");

    if(!pf)
        return 1;
    int i;

    tAlumno alu[]={{123,"Pepin Pepon", 7.5},{234,"Pepun Pepan", 9},{789,"Sapin Sapito", 5.7}};
    tAlumno *pAlu = alu;

    for(i=0; i<sizeof(alu)/sizeof(tAlumno); i++){//stdout 
        fprintf(pf, "%d|%s|%5.2f\n",pAlu->dni, pAlu->NyAp, pAlu->prom);
        pAlu++;
    }

    fclose(pf);

    return 0;
}

int crearLoteTexto(const char* arch)
{
    int i;
    char mat[][MAXLINE]={"a","b","c","d","e"};
    FILE *pf = fopen(arch,"wt");
    if(!pf)
        return 1;

    for(i=0;i<sizeof(mat)/MAXLINE; i++)
        fputs(mat[i], pf);

    fclose(pf);
    return 0;
}


