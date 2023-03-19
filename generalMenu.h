#ifndef GENERALMENU_H
#define GeneralMenu_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./models/evento.h"
#include "./backend/mySQLconnector.h"

void imprimirFactura(char*** evento, char*** haciento, int* hacientos, int cont, char* nombre, char* cedula) {
    int precioFinal = 0;
    printf("*--------------------------------------------* \n");
    printf("Factura \n");
    printf("Nombre del evento: %s \n", evento[0][1]);
    printf("Fecha del evento: %s \n", evento[0][2]);
    printf("Lugar del evento: %s \n", evento[0][3]);
    printf("Nombre del cliente: %s \n", nombre);
    printf("Cedula del cliente: %s \n", cedula);
    printf("&--------------------------------------------& \n");
    printf("Hacientos comprados: \n");
    for (int i = 0; i < cont; i++) {
        precioFinal += atoi(haciento[hacientos[i]-1][10]);
        printf("Haciento: %d \n", hacientos[i]);
        printf("Precio: %s \n", haciento[hacientos[i]-1][10]);
        printf("Tipo: %s \n", haciento[hacientos[i]-1][7]);
        printf("&--------------------------------------------& \n");
        reservarAsientos(atoi(haciento[hacientos[i]-1][15]));
    }
    agregarFactura(nombre, evento[0][4], precioFinal, atoi(cedula), atoi(evento[0][0]));
}

void comprarBoletoAux(char*** evento, char*** haciento) {
    int numHacientos;
    int stop = 0;
    int* hacientos = (int*) malloc(sizeof(int)*100);
    int cont = 0;
    do
    {
        printf("Ingrese el numero de los hacientos que desea comprar: \n");
        scanf("%d", &numHacientos);
        hacientos[cont] = numHacientos;
        cont++;
        printf("Desea comprar otro haciento? 1. Si 2. No \n");
        scanf("%d", &stop);
        if (stop == 2) {
            stop = 1;
        } else {
            stop = 0;
        }
    } while (stop == 0);
    printf("Ingrese su nombre: ");
    char* nombre = (char*) malloc(sizeof(char)*50);
    scanf("%s", nombre);
    printf("Ingrese su cedula: ");
    char* cedula = (char*) malloc(sizeof(char)*50);
    scanf("%s", cedula);
    imprimirFactura(evento, haciento, hacientos, cont, nombre, cedula);
}

void comprarBoleto() {
    printf("Comprar boleto \n");
    printf("Ingrese el nombre del evento: ");
    char* nombre = (char*) malloc(sizeof(char)*50);
    scanf("%s", nombre);
    char*** evento = consultarXNombreEvento(nombre);
    if(evento == NULL) {
        printf("No existe el evento \n");
    } else {
        printf("Informacion del evento: \n");
        char *info = evento[0][0];
        char*** haciento = getInformacionTotalEvento(atoi(info));
        comprarBoletoAux(evento, haciento);
    }
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
                // printf("Comprar boleto \n");
                comprarBoleto();
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