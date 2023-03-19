#ifndef GENERALMENU_H
#define GeneralMenu_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./models/evento.h"
#include "./backend/mySQLconnector.h"

void consultaEvento() {
    char*** listaEventos = getConsultaEstadoEvento();
    Evento* evento = crearListaEventos(listaEventos, retunTablas("evento"));
    imprimirEventos(evento);
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