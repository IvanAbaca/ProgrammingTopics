#include "telemetria.h"

int main()
{
    if(!verificarTam(ArchTelem))
    {
        printf("El archivo no se pudo abrir.");
        return 1;
    }

    obtenerRegistros(ArchTelem);

    return 0;
}
