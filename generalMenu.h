#ifndef GENERALMENU_H
#define GeneralMenu_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./models/evento.h"
#include "./backend/mySQLconnector.h"

void comprarBoleto() {
    printf("Comprar boleto \n");
    printf("Ingrese el nombre del evento: ");
    char nombre = (char*) malloc(sizeof(char)*50);
    scanf("%s", &nombre);
    char*** evento = consultarXNombreEvento(nombre);
}

void consultaEvento() {
    char*** listaEventos = getEvento();
    int numfilas = retunTablas("evento");
    Evento* evento = crearListaEventos(listaEventos, numfilas);
    // imprimirEventos(evento);
    printf("Ingrese el numero de fila del evento: ");
    int fila;
    scanf("%d", &fila);
    if(fila > numfilas || fila < 0) {
        printf("No existe el evento \n");
    } else {
        // Evento* even = buscarEvento(evento, fila);
        printf("Informacion del evento: \n");
        char *info = listaEventos[fila-1][0];
        getInformacionTotalEvento(atoi(info));
    }
}

void generalMenu() {
    int opcion;
    do {
        printf("Menu General \n");
        printf("1. Consulta por evento \n");
        printf("2. Comprar boleto \n");
        printf("3. Salir \n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                printf("Consulta por evento \n");
                consultaEvento();
                break;
            case 2:
                printf("Comprar boleto \n");
                break;
            case 3:
                printf("Salir \n");
                break;
            default:
                printf("Opcion no valida \n");
                break;
        }
    } while (opcion != 3);

}

#endif /* GENERALMENU_H */