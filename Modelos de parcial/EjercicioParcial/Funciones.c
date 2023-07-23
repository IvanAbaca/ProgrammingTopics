#include "Funciones.h"

int cmp(void* bin, void* txt)
{
    if(strncmp((char*)bin, (char*)txt,17)>0)
        return 1;
    if(strncmp((char*)bin, (char*)txt,17)<0)
        return -1;
    return 0;
}

int trozarVariable(char* cad, char corte, t_libro* lib)
{
    char* pl = strchr(cad, '\n');
    if(!pl)
        return 1;
    *pl = '\0';

    pl = strrchr(cad, corte);
    sscanf(pl+1,"%d", &(lib->stock));
    *pl = '\0';

    pl = strrchr(cad, corte);
    sscanf(pl+1,"%d", &(lib->isbn.verif));
    *pl = '\0';

    pl = strrchr(cad, corte);
    sscanf(pl+1,"%d", &(lib->isbn.nroArt));
    *pl = '\0';

    pl = strrchr(cad, corte);
    sscanf(pl+1,"%d", &(lib->isbn.editor));
    *pl = '\0';

    pl = strrchr(cad, corte);
    sscanf(pl+1,"%d", &(lib->isbn.codPais));
    *pl = '\0';

    sscanf(cad,"%d", &(lib->isbn.cod));

    return 0;
}

int isISBN(char* cad)
{
    int impar=0, par=0, i=1, j;
    for(j=0; j<17; j++)
    {
        if(i%2 == 1 && *cad != '-' && *cad != '\n')
        {
            impar+= *cad-48;
            i++;
        }
        else if(i%2 == 0 && *cad != '-' && *cad != '\n')
        {
            par+= *cad-48;
            i++;
        }
            cad++;
    }
    if((impar+3*par)%10 == 0)
            return 1;
    return 0;
}

int actualizar(const char* bin, const char* txt, int cmp(void*, void*))
{
    FILE* pf1 = fopen(bin, "rb");
    if(!pf1)
        return 1;
    FILE* pf2 = fopen(txt, "rt");
    if(!pf2)
        return 1;
    FILE* pf3 = fopen("temp.dat", "wb");
    if(!pf3)
        return 1;
    FILE* pf4 = fopen("error.txt", "wt");
    if(!pf4)
        return 1;

    char cadTxt[50];
    char cadBin[50];
    t_libro libBin, libText;

    fread(&libBin, sizeof(t_libro), 1, pf1);
    fgets(cadTxt, 50, pf2);
    int isIsbnTxt = isISBN(cadTxt), cmpLib;

    while(!feof(pf1) || !feof(pf2))
    {
        sprintf(cadBin, "%d-%d-%d-%d-%d-%d\n", libBin.isbn.cod, libBin.isbn.codPais, libBin.isbn.editor, libBin.isbn.nroArt, libBin.isbn.verif, libBin.stock);
        cmpLib = cmp(cadBin, cadTxt);
        trozarVariable(cadTxt, '-', &libText);
        if(cmpLib == 0 && isIsbnTxt)
        {
            libBin.stock+=libText.stock;
            fwrite(&libBin, sizeof(t_libro), 1, pf3);
            fread(&libBin, sizeof(t_libro), 1, pf1);
            fgets(cadTxt, sizeof(cadTxt), pf2);
        }
        else if(cmpLib == 1 && isIsbnTxt)
        {
            fprintf(pf4, "Error en el: %d-%d\n", libText.isbn.cod, libText.isbn.codPais);
            fgets(cadTxt, sizeof(cadTxt), pf2);
        }
        else if(cmpLib == -1)
        {
            fwrite(&libBin, sizeof(t_libro), 1, pf3);
            fread(&libBin, sizeof(t_libro), 1, pf1);
        }

        if(!isIsbnTxt)
        {
            fprintf(pf4, "Error en el: %d-%d\n", libText.isbn.cod, libText.isbn.codPais);
            fgets(cadTxt, sizeof(cadTxt), pf2);
        }
        isIsbnTxt = isISBN(cadTxt);
    }

    while(!feof(pf2))
    {
        trozarVariable(cadTxt, '-', &libText);
        if(isIsbnTxt)
        {
            fprintf(pf4, "Error en el: %d-%d\n", libText.isbn.cod, libText.isbn.codPais);
            fgets(cadTxt, sizeof(cadTxt), pf2);
        }
        else
        {
            fprintf(pf4, "Error en el: %d-%d\n", libText.isbn.cod, libText.isbn.codPais);
            fgets(cadTxt, sizeof(cadTxt), pf2);
        }
        isIsbnTxt = isISBN(cadTxt);
    }
    while(!feof(pf1))
    {
        fwrite(&libBin, sizeof(t_libro), 1, pf3);
        fread(&libBin, sizeof(t_libro), 1, pf1);
    }

    fclose(pf1);
    fclose(pf2);
    fclose(pf3);
    fclose(pf4);
    remove(bin);
    rename("temp.dat", bin);

    return 0;
}

int crearBin(const char* arch)
{
    FILE* pf = fopen(arch, "wb");
    if(!pf)
        return 1;

    t_libro vec[] =
    {
    {{978,84,253,4025,3},10},
    {{978,83,263,4025,3},20},
    {{978,83,263,4015,4},30},
    {{978,82,273,4005,5},40},
    {{978,74,353,4025,3},50},
    {{978,74,352,4125,3},60},
   };

    fwrite(vec, sizeof(t_libro), sizeof(vec)/sizeof(t_libro), pf);
    fclose(pf);
    return 0;
}

int crearText(const char* arch)
{
    FILE* pf = fopen(arch, "wt");
    if(!pf)
        return 1;

    t_libro vec[] =
    {
    {{978,84,253,4025,3},10},
    {{978,83,263,4025,3},20},
    {{978,83,263,4015,4},30},
    {{978,82,273,4005,5},40},
    {{978,74,353,4025,3},50},
    {{978,74,352,4125,3},60},
   };
    int i;

    for(i=0; i<(sizeof(vec)/sizeof(t_libro)); i++)
        fprintf(pf, "%d-%d-%d-%d-%d-%d\n",
                    vec[i].isbn.cod,
                    vec[i].isbn.codPais,
                    vec[i].isbn.editor,
                    vec[i].isbn.nroArt,
                    vec[i].isbn.verif ,
                    vec[i].stock);

    fclose(pf);
    return 0;
}

int mostrarArchBin(const char* arch)
{
    FILE* pf = fopen(arch, "rb");
    if(!pf)
        return 1;
    t_libro lib;

    fread(&lib, sizeof(t_libro), 1, pf);
    printf("\n\nCod\tCodPais\tEditor\tNroArt\tVerif\tStock\n");
    printf("%d\t|%d\t|%d\t|%d\t|%d\t|%d\n",
                    lib.isbn.cod,
                    lib.isbn.codPais,
                    lib.isbn.editor,
                    lib.isbn.nroArt,
                    lib.isbn.verif ,
                    lib.stock);

    while(!feof(pf))
    {
        fread(&lib, sizeof(t_libro), 1, pf);
        printf("%d\t|%d\t|%d\t|%d\t|%d\t|%d\n",
                lib.isbn.cod,
                lib.isbn.codPais,
                lib.isbn.editor,
                lib.isbn.nroArt,
                lib.isbn.verif ,
                lib.stock);
    }

    fclose(pf);
    return 0;
}
