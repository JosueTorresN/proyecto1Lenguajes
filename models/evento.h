#ifndef EVENTO_H
#define EVENTO_H
#include <stdlib.h>
#include <string.h>

struct evento
{
    char* id;
    char* nombre;
    char* productora;
    char* fecha;
    char* sitio;
    Evento *siguiente;
} typedef Evento;

Evento* crearEvento(char* id, char* nombre, char* productora, char* fecha, char* sitio) {
    Evento* evento = (Evento*) malloc(sizeof(Evento));
    char idAux[10];
    strcpy(idAux, id);
    char nombreAux[100];
    strcpy(nombreAux, nombre);
    char productoraAux[100];
    strcpy(productoraAux, productora);
    char fechaAux[100];
    strcpy(fechaAux, fecha);
    char sitioAux[100];
    strcpy(sitioAux, sitio);

    evento->id = idAux;
    evento->nombre = nombreAux;
    evento->productora = productoraAux;
    evento->fecha = fechaAux;
    evento->sitio = sitioAux;
    evento->siguiente = NULL;
    return evento;
}

void agregarEvento(Evento* evento, Evento* nuevo) {
    if (evento->siguiente == NULL) {
        evento->siguiente = nuevo; 
    } else {
        agregarEvento(evento->siguiente, nuevo);
    }
}

#endif // EVENTO_H