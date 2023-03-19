#ifndef EVENTO_H
#define EVENTO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct evento
{
    char* id;
    char* nombre;
    char* productora;
    char* fecha;
    char* sitio;
    struct evento *siguiente;
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

Evento* agregarEvento(Evento* evento, Evento* nuevo) {
    if (evento == NULL) {
        evento = nuevo;
        return evento;
    } else {
        Evento* sitioAux = evento;
        while(sitioAux->siguiente != NULL) {
            sitioAux = sitioAux->siguiente;
        }
        sitioAux->siguiente = nuevo;
        return evento;
    }
}

Evento* crearListaEventos(char*** eventos, int cantidadEventos) {
    Evento* listaEventos = NULL;
    for (int i = 0; i < cantidadEventos; i++) {
        agregarEvento(listaEventos, crearEvento(eventos[i][0], eventos[i][1], eventos[i][2], eventos[i][3], eventos[i][4]));
    }
    return listaEventos;
}

/*
    * Función que imprime un evento
    * @param sitio: sitio de eventos a imprimir
*/
void imprimirEventosAux(Evento* sitio, int cont) {
    printf("{--------------------}\n");
    printf("Sitio de eventos %d\n", cont);
    printf("Id: %s\n", sitio->id);
    printf("Nombre: %s\n", sitio->nombre);
    printf("Productora: %s\n", sitio->productora);
    printf("Fecha: %s\n", sitio->fecha);
    printf("Sitio: %s\n", sitio->sitio);
    printf("{--------------------}\n");
}

/*
    * Función que imprime todos los eventos
    * @param sitio: primer evento
*/
void imprimirEventos(Evento* sitio) {
    if(sitio == NULL) {
        printf("No hay eventos registrados\n");
        return;
    }
    Evento* sitioAux = sitio;
    int cont = 1;
    while(sitioAux != NULL) {
        imprimirEventosAux(sitioAux, cont);
        sitioAux = sitioAux->siguiente;
        cont++;
    }
}

Evento* buscarEvento(Evento* evento, int posicion) {
    printf("Buscando evento en la posición %s\n", evento->nombre);
    Evento* sitioAux = evento;
    int cont = 0;
    while(sitioAux != NULL) {
        if (cont == posicion) {
            return sitioAux;
        }
        sitioAux = sitioAux->siguiente;
        cont++;
    }
    return NULL;
}

#endif // EVENTO_H