#include "Funciones.h"

int merge_mio(const char* archE, const char* archN, int compare(void*, void*))
{
    /*
    alta(a)         -> Si lo encuentra: ERROR                       / Si no lo encuentra: Escribe en TEMP.dat
    baja(b)         -> Si lo encuentra: No hace nada                / Si no lo encuentra: ERROR
    modificar(m)    -> Si lo encuentra: Guarda tNov en TEMP.dat     / Si no lo encuentra: ERROR

    Remove EMP.dat -> Rename TEMP.dat

    */
    int cmp = 0;
    tEmpleado emp;
    tNovedad nov;
    FILE *pfe = fopen(archE,"rb");
    FILE *pfn =  fopen(archN,"rb");
    FILE *pft =  fopen("temp.dat","wb");
    if(!pfe)
        return 1;
    if(!pfn)
        return 1;
    if(!pft)
        return 1;

    fread(&emp,sizeof(emp),1,pfe);
    fread(&nov,sizeof(nov),1,pfn);

    while(!feof(pfn))
    {
        cmp = compare(&emp,&nov);
        if(cmp == 0){       //Nov=Emp:  0
            actualizar(nov,pft,cmp);
            fflush(pft);
            if(!feof(pfe))
                fread(&emp,sizeof(tEmpleado),1,pfe);
            fread(&nov,sizeof(tNovedad),1,pfn);
        }
        else if(cmp == 1 || feof(pfe)){  //Nov>Emp:  1
            actualizar(nov,pft,cmp);
            fflush(pft);
            fread(&nov,sizeof(tNovedad),1,pfn);
        }
        else if(cmp == -1){ //Nov<Emp: -1
            if(!feof(pfe))
                fread(&emp,sizeof(tEmpleado),1,pfe);
        }
    }
    fclose(pfn);
    fclose(pft);
    fclose(pfe);
    remove(archE);
    rename("temp.dat", archE);
    return 0;
}

int cargarVecNov(const char* arch, tNovedad* nov)
{
    FILE *pf =  fopen(arch,"rb");
    if(!pfe)
        return 1;
    while(!feof(pf))
    {
        fread(nov, sizeof(tNovedad), 1, pf);
        nov++;
    }
    fclose(pf);
    return 0;
}


int merge_vecNov(const char* archE, tNovedad* vec, int ce, int compare(void*, void*))
{
    /*
    alta(a)         -> Si lo encuentra: ERROR                       / Si no lo encuentra: Escribe en TEMP.dat
    baja(b)         -> Si lo encuentra: No hace nada                / Si no lo encuentra: ERROR
    modificar(m)    -> Si lo encuentra: Guarda tNov en TEMP.dat     / Si no lo encuentra: ERROR

    Remove EMP.dat -> Rename TEMP.dat

    */
    
    int cmp = 0;
    tEmpleado emp;
    tNovedad* fin = vec+ce;
    tNovedad nov = *vec;

    FILE *pfe = fopen(archE,"rb");
    FILE *pft =  fopen("temp.dat","wb");
    if(!pfe)
        return 1;
    if(!pft)
        return 1;

    fread(&emp,sizeof(emp),1,pfe);

    while(vec != fin)
    {
        cmp = compare(&emp,&nov);
        if(cmp == 0){       //Nov=Emp:  0
            actualizar(nov,pft,cmp);
            fflush(pft);
            if(!feof(pfe))
                fread(&emp,sizeof(tEmpleado),1,pfe);
            nov = *(++vec);
        }
        else if(cmp == 1 || feof(pfe)){  //Nov>Emp:  1
            actualizar(nov,pft,cmp);
            fflush(pft);
            nov = *(++vec);
        }
        else if(cmp == -1){ //Nov<Emp: -1
            if(!feof(pfe))
                fread(&emp,sizeof(tEmpleado),1,pfe);
        }
    }
    fclose(pft);
    fclose(pfe);
    remove(archE);
    rename("temp.dat", archE);
    return 0;
}    

int cmpEmpNov(void* emp, void* nov)
{
    tNovedad* novedad = (tNovedad*)nov;
    tEmpleado* empleado = (tEmpleado*)emp;

    int cmp = 1;

    cmp = strcmp(empleado->apellido, novedad->emp.apellido);
    if(cmp != 0)
        return cmp;

    cmp = strcmp(empleado->nombre, novedad->emp.nombre);
    if((cmp != 0))
        return cmp;

    if(novedad->emp.dni != empleado->dni)
        return cmp;

    return 0;
}

void actualizar(tNovedad nov, FILE *pf, int cmp)
{
    tEmpleado temp;
    if(nov.novedad == 'a' && cmp != 0)
    {
        temp.dni = nov.emp.dni;
        strcpy(temp.nombre,nov.emp.nombre);
        strcpy(temp.apellido,nov.emp.apellido);
        temp.sueldo = nov.emp.sueldo;
        fwrite(&temp, sizeof(tEmpleado), 1, pf);
        fflush(pf);
    }
    else if(nov.novedad == 'm' && cmp == 0)
    {
        temp.dni = nov.emp.dni;
        strcpy(temp.nombre,nov.emp.nombre);
        strcpy(temp.apellido,nov.emp.apellido);
        temp.sueldo = nov.emp.sueldo;
        fwrite(&temp, sizeof(tEmpleado), 1, pf);
        fflush(pf);
    }
    else if(nov.novedad == 'b' && cmp == 0)
        fflush(pf);
    else
        printf("\nError en DNI: %d \t(%c)", nov.emp.dni, nov.novedad);
}

int crearLoteEmpl(const char* nom_archv)
{
/*  LOTE DE PRUEBA PARA EL EJERCICIO 13 (PRIMERA PARTE)
    tEmpl empl[10] = {
        {1,"b","a",100},{2,"z","a",200},{3,"c","b",300},{4,"d","b",400},{5  ,"e","e",500},
        {6,"f","f",600},{7,"g","g",700},{8,"h","h",800},{9,"i","i",900},{10 ,"j","j",1000}};
*/
//  LOTE DE PRUEBA PARA EL MERGE (SEGUNDA PARTE)
    tEmpleado empl[TamEmp] = {
        {1,"a","a",100},{2,"c","d",100},{3,"e","f",100},{4,"d","b",400},{5  ,"e","e",500},
        {6,"f","f",600},{7,"g","g",700},{8,"o","p",100},{9,"q","r",100},{10 ,"s","t",100}};

    FILE* pf = fopen(nom_archv, "wb");
    if(!pf)
        return 1;
    fwrite(empl, sizeof(empl), 1, pf);
    fclose(pf);
    return 0;
}

int crearLoteNovedades(const char* nom_archv)
{
    tNovedad nov[TamNov] = {
        {{1,"a","b",100},'a'},{{2,"c","d",100},'b'},{{3,"e","f",300},'m'},{{4,"g","h",100},'b'},{{5,"i","j",400},'m'},       // A = 1,7,10 | B = 2,4,8 | M = 3,5,6,9
        {{6,"k","l",200},'m'},{{7,"m","n",100},'a'},{{8,"o","p",100},'b'},{{9,"q","r",500},'m'},{{10,"s","t",100},'a'}, {{11,"u","v",100},'a'}};

    // 1,2,3,7,8,9,11 no tienen error.
    // 4,5,6,10 tiene error.

    FILE* pf = fopen(nom_archv, "wb");
    if(!pf)
        return 1;
    fwrite(nov, sizeof(nov), 1, pf);
    fclose(pf);
    return 0;
}

int mostrarEmpl(char* nombreArch)
{
    FILE* archBin=fopen(nombreArch,"rb");
    if(!archBin)
        return 1;

    tEmpleado emp;
    printf("\nArchivo leido: %s\n", nombreArch);
    fread(&emp,sizeof(tEmpleado),1,archBin);
    while(!feof(archBin))
    {
        printf("DNI: %d\t\tNombre: %s\tApellido: %s\tSueldo: %.2f\n",emp.dni, emp.nombre, emp.apellido, emp.sueldo);
        fread(&emp,sizeof(tEmpleado),1,archBin);

    }

    fclose(archBin);
    return 0;
}

int mostrarNovedades(char* nombreArch)
{
    FILE* archBin=fopen(nombreArch,"rb");
    if(!archBin)
        return 1;

    tNovedad nov;
    printf("\nArchivo leido: %s\n", nombreArch);
    fread(&nov,sizeof(tNovedad),1,archBin);
    while(!feof(archBin))
    {
        printf("DNI: %d\t\tNombre: %s\tApellido: %s\tSueldo: %.2f\tTipo: %c\n", nov.emp.dni, nov.emp.nombre, nov.emp.apellido, nov.emp.sueldo, nov.novedad);
        fread(&nov,sizeof(tNovedad),1,archBin);

    }
    fclose(archBin);
    return 0;
}


