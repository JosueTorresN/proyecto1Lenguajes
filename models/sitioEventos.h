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
    struct sitioEventos* siguiente;
} typedef SitioEventos;

/*
    * Función que imprime un sitio de eventos
    * @param sitio: sitio de eventos a imprimir
*/
void imprimirSitioEventosAux(SitioEventos* sitio) {
    printf("ID: %s\n", sitio->id);
    printf("Nombre: %s\n", sitio->nombre);
    printf("Dirección: %s\n", sitio->direccion);
    printf("Sitio web: %s\n", sitio->sitioWeb);
}

/*
    * Función que imprime todos los sitios de eventos
    * @param sitio: primer sitio de eventos
*/
void imprimirSitioEventos(SitioEventos* sitio) {
    if(sitio == NULL) {
        printf("No hay sitios de eventos registrados\n");
        return;
    }
    SitioEventos* sitioAux = sitio;
    while(sitioAux != NULL) {
        imprimirSitioEventosAux(sitioAux);
        sitioAux = sitioAux->siguiente;
    }
    
}

/*
    * Función que crea un sitio de eventos
    * @param id: id del sitio de eventos
    * @param nombre: nombre del sitio de eventos
    * @param direccion: dirección del sitio de eventos
    * @param sitioWeb: sitio web del sitio de eventos
    * @return sitio de eventos creado
*/
SitioEventos* crearSitioEventos(char* id, char* nombre, char* direccion, char* sitioWeb) {
    SitioEventos* sitio = (SitioEventos*) malloc(sizeof(SitioEventos));
    char* idAux = (char*)malloc(sizeof(char) * strlen(id) + 1);
    strcpy(idAux, id);
    char* nombreAux = (char*)malloc(sizeof(char) * strlen(nombre) + 1);
    strcpy(nombreAux, nombre);
    char* direccionAux = (char*)malloc(sizeof(char) * strlen(direccion) + 1);
    strcpy(direccionAux, direccion);
    char* sitioWebAux = (char*)malloc(sizeof(char) * strlen(sitioWeb) + 1);
    strcpy(sitioWebAux, sitioWeb);

    sitio->id = idAux;
    sitio->nombre = nombreAux;
    sitio->direccion = direccionAux;
    sitio->sitioWeb = sitioWebAux;
    sitio->siguiente = NULL;
    return sitio;
}

/*
    * Función que agrega un sitio de eventos a la lista de sitios de eventos
    * @param sitio: primer sitio de eventos
    * @param nuevo: sitio de eventos a agregar
*/
SitioEventos* agregarSitioEventos(SitioEventos* sitio, SitioEventos* nuevo) {
    if (sitio == NULL) {
        sitio = nuevo;
        return nuevo;
    } else {
        SitioEventos* sitioAux = sitio;
        while(sitioAux->siguiente != NULL) {
            sitioAux = sitioAux->siguiente;
        }
        sitioAux->siguiente = nuevo;
        return sitio;
    }
    //  else if (sitio->siguiente == NULL) {
    //     sitio->siguiente = nuevo;
    // } else {
    //     agregarSitioEventos(sitio->siguiente, nuevo);
    // }
}

#endif // SITIOEVENTOS_H
