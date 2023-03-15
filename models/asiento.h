#ifndef ASIENTO_H
#define ASIENTO_H

#include <stdlib.h>
#include <string.h>

struct asiento
{
    char* id;
    char* nombre;
    int disponible;
    int numeroHaciento;
    char* idSector;
    Asiento *siguiente;
} typedef Asiento;

Asiento* crearAsiento(char* id, char* nombre, int disponible, int numeroHaciento, char* idSector) {
    Asiento* asiento = (Asiento*) malloc(sizeof(Asiento));
    char idAux[10];
    strcpy(idAux, id);
    char nombreAux[100];
    strcpy(nombreAux, nombre);
    char idSectorAux[100];
    strcpy(idSectorAux, idSector);

    asiento->id = idAux;
    asiento->nombre = nombreAux;
    asiento->disponible = disponible;
    asiento->numeroHaciento = numeroHaciento;
    asiento->idSector = idSectorAux;
    asiento->siguiente = NULL;
    return asiento;
}

void agregarAsiento(Asiento* asiento, Asiento* nuevo) {
    if (asiento->siguiente == NULL) {
        asiento->siguiente = nuevo; 
    } else {
        agregarAsiento(asiento->siguiente, nuevo);
    }
}

#endif // ASIENTO_H