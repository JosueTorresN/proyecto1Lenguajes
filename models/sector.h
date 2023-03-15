#ifndef SECOR_H
#define SECOR_H

#include <stdlib.h>
#include <string.h>

struct sector
{
    char* id;
    char* nombre;
    char* inicial;
    int capacidad;
    int montoPrecio;
    char* idSitio;
    Sector *siguiente;
} typedef Sector;

Sector* crearSector(char* id, char* nombre, char* inicial, int capacidad, int montoPrecio, char* idSitio) {
    Sector* sector = (Sector*) malloc(sizeof(Sector));
    char idAux[10];
    strcpy(idAux, id);
    char nombreAux[100];
    strcpy(nombreAux, nombre);
    char inicialAux[100];
    strcpy(inicialAux, inicial);
    char idSitioAux[100];
    strcpy(idSitioAux, idSitio);

    sector->id = idAux;
    sector->nombre = nombreAux;
    sector->inicial = inicialAux;
    sector->capacidad = capacidad;
    sector->montoPrecio = montoPrecio;
    sector->idSitio = idSitioAux;
    sector->siguiente = NULL;
    return sector;
}

void agregarSector(Sector* sector, Sector* nuevo) {
    if (sector->siguiente == NULL) {
        sector->siguiente = nuevo; 
    } else {
        agregarSector(sector->siguiente, nuevo);
    }
}

#endif // SECOR_H

