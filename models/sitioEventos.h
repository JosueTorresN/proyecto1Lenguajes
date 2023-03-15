#ifndef SITIOEVENTOS_H
#define SITIOEVENTOS_H
#include <stdlib.h>
#include <string.h>

struct sitioEventos
{
    char* id;
    char* nombre;
    char* direccion;
    char* sitioWeb;
    SitioEventos *siguiente;
} typedef SitioEventos;

SitioEventos* crearSitioEventos(char* id, char* nombre, char* direccion, char* sitioWeb) {
    SitioEventos* sitio = (SitioEventos*) malloc(sizeof(SitioEventos));
    char idAux[10];
    strcpy(idAux, id);
    char nombreAux[100];
    strcpy(nombreAux, nombre);
    char direccionAux[100];
    strcpy(direccionAux, direccion);
    char sitioWebAux[100];
    strcpy(sitioWebAux, sitioWeb);

    sitio->id = idAux;
    sitio->nombre = nombreAux;
    sitio->direccion = direccionAux;
    sitio->sitioWeb = sitioWebAux;
    sitio->siguiente = NULL;
    return sitio;
}

void agregarSitioEventos(SitioEventos* sitio, SitioEventos* nuevo) {
    if (sitio->siguiente == NULL) {
        sitio->siguiente = nuevo; 
    } else {
        agregarSitioEventos(sitio->siguiente, nuevo);
    }
}

#endif // SITIOEVENTOS_H
