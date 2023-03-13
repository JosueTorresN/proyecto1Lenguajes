#ifndef OPERATIVEMENU_H
#define OPERATIVEMENU_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void estadisticas() {
    // Top 3 meses con mas eventos
    // Top 3 eventos con mas recaudacion
    // Listado de sitios de eventos con cantidad de eventos y monto total recaudado (de mayor amenor) por rango de fechas 
}

void listaFacturas() {// Falta la busqueda por rango de fecha
    char* listaFacturas[3] = {"Factura 1", "Factura 2", "Factura 3"};
    printf("\nLista de facturas \n");
    for (int i = 0; i < 3; i++)
    {
        printf("%i- %s \n", i+1, listaFacturas[i]);
    }
    printf("Escoja una opcion o cancele con # >> ");
    char opcion[1];
    scanf("%s", opcion);
    if (strcmp(opcion, "#") == 0) {
        printf("Cancelado\n");
    } else {
        printf("Opcion %s seleccionada\n", opcion);
    }
}

void estadoEvento() {
    char* listaEspacios[3] = {"Espacio 1", "Espacio 2", "Espacio 3"};
    printf("\nEstado de evento \n");
    for (int i = 0; i < 3; i++)
    {
        printf("%i- %s \n", i+1, listaEspacios[i]);
    }
    printf("Escoja una opcion o cancele con # >> ");
    char opcion[1];
    scanf("%s", opcion);
    if (strcmp(opcion, "#") == 0) {
        printf("Cancelado\n");
    } else {
        printf("Opcion %s seleccionada\n", opcion);
        gestionEspaciosEventosAux();
    }
}

// Hay que crear el loop, para recorrer todos los sectores
void gestionEventosAux() {
    char confirmacion[1];
    printf("\nAgrege el valor para cada sector \n");
    printf("Sector 1: ");
    int sector1;
    scanf("%d", &sector1);
    printf("Sector 2: ");
    int sector2;
    scanf("%d", &sector2);
    printf("Confirmar? Y/n\n");
    scanf("%s", confirmacion);
    if (strcmp(confirmacion, "Y") == 0) {
        printf("Evento creado con exito\n");
    } else {
        printf("Evento no creado\n");
    }
}

void gestionEventos() {
    char nombreEvento[20];
    char productoraEvento[20];
    char fechaEvento[20];
    char lugarEvento[20]; //Este es temporal, hay que cambiarlo por un struct
    char confirmacion[1];

    printf("\nNuevo evento \n");
    printf("Nombre del evento: ");
    scanf("%s", nombreEvento);
    printf("Productora del evento: ");
    scanf("%s", productoraEvento);
    printf("Fecha del evento: ");
    scanf("%s", fechaEvento);
    printf("Lugar del evento: ");
    scanf("%s", lugarEvento);
    printf("Nombre: %s\n", nombreEvento);
    printf("Productora: %s\n", productoraEvento);
    printf("Fecha: %s\n", fechaEvento);
    printf("Lugar: %s\n", lugarEvento);
    printf("Confirmar? Y/n\n");
    scanf("%s", confirmacion);
    if (strcmp(confirmacion, "Y") == 0) {
        printf("Evento creado con exito\n");
    } else {
        printf("Evento no creado\n");
    }
}

void editarEspacio() {
    char nombreEspacio[20];
    char siglaEspacio[1];
    int capacidadEspacio;
    char confirmacion[1];
    printf("\nEditar espacio \n");
    printf("Nombre del espacio: ");
    scanf("%s", nombreEspacio);
    printf("Sigla del espacio: ");
    scanf("%s", siglaEspacio);
    printf("Capacidad del espacio: ");
    scanf("%d", &capacidadEspacio);
    printf("Nombre: %s\n", nombreEspacio);
    printf("Sigla: %s\n", siglaEspacio);
    printf("Capacidad: %d\n", capacidadEspacio);
    printf("Confirmar? Y/n\n");
    scanf("%s", confirmacion);
    if (strcmp(confirmacion, "Y") == 0) {
        printf("Espacio editado con exito\n");
    } else {
        printf("Espacio no editado\n");
    }
}

void crearEspacio() {
    char nombreEspacio[20];
    char siglaEspacio[1];
    int capacidadEspacio;
    char confirmacion[1];
    printf("\nNuevo espacio \n");
    printf("Nombre del espacio: ");
    scanf("%s", nombreEspacio);
    printf("Sigla del espacio: ");
    scanf("%s", siglaEspacio);
    printf("Capacidad del espacio: ");
    scanf("%d", &capacidadEspacio);
    printf("Nombre: %s\n", nombreEspacio);
    printf("Sigla: %s\n", siglaEspacio);
    printf("Capacidad: %d\n", capacidadEspacio);
    printf("Confirmar? Y/n\n");
    scanf("%s", confirmacion);
    if (strcmp(confirmacion, "Y") == 0) {
        printf("Espacio creado con exito\n");
    } else {
        printf("Espacio no creado\n");
    }
}

void gestionEspaciosEventosAux() {
    int bandera = 0;
    int opcion;
    do
    {
        printf("\n1- Agregar espacio \n");
        printf("2- Eliminar espacio \n");
        printf("3- Modificar espacio \n");
        printf("4- Resetear espacio \n");
        printf("5- Volver \n");
        printf(">> ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("Agregar espacio \n");
            crearEspacio();
            break;

        case 2:
            printf("Eliminar espacio \n");
            break;

        case 3:
            printf("Modificar espacio \n");
            editarEspacio();
            break;

        case 4:
            printf("Resetear espacio \n");
            break;

        case 5:
            bandera = 1;
            break;

        default:
            printf("Opcion no valida \n");
            break;
        }

    } while (bandera == 0);
    

}

void gestionEspaciosEventos() {
    char* listaEspacios[3] = {"Espacio 1", "Espacio 2", "Espacio 3"};
    printf("\nGestion de espacios sitio de evento \n");
    for (int i = 0; i < 3; i++)
    {
        printf("%i- %s \n", i+1, listaEspacios[i]);
    }
    printf("Escoja una opcion o cancele con # >> ");
    char opcion[1];
    scanf("%s", opcion);
    if (strcmp(opcion, "#") == 0) {
        printf("Cancelado\n");
    } else {
        printf("Opcion %s seleccionada\n", opcion);
        gestionEspaciosEventosAux();
    }
}

void newEvent() {
    char nombreEvento[20];
    char ubicacionEvento[20];
    char paginaWebEvento[20];
    char confirmacin[1];

    printf("\nNuevo evento \n");
    printf("Nombre del evento: ");
    scanf("%s", nombreEvento);
    printf("Ubicacion del evento: ");
    scanf("%s", ubicacionEvento);
    printf("Pagina web del evento: ");
    scanf("%s", paginaWebEvento);
    printf("Nombre: %s\n", nombreEvento);
    printf("Ubicacion: %s\n", ubicacionEvento);
    printf("Pagina web: %s\n", paginaWebEvento);
    // printf("%s %s %s \n", nombreEvento, ubicacionEvento, paginaWebEvento);
    printf("Confirmar? Y/n\n");
    scanf("%s", confirmacin);
    if (strcmp(confirmacin, "Y") == 0) {
        printf("Evento creado con exito\n");
    } else {
        printf("Evento no creado\n");
    }
}

void menuOperativo() {
    int flag = 0;
    int opcion;
    do
    {
        printf("\nMenu Operativo \n");
        printf("1- Gestion de sition de eventos \n");
        printf("2- Gestion de espacios sitio de evento \n");
        printf("3- Gestion de eventos \n");
        printf("4- Estado de evento \n");
        printf("5- Gestion de espacios \n");
        printf("6- Lista de facturas \n");
        printf("7- Estadisticas \n");
        printf("8- Volver \n");
        printf(">> ");
        
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            newEvent();
            break;

        case 2:
            gestionEspaciosEventos();
            break;
        
        default:
            break;
        }
    } while (flag == 0);
}

#endif