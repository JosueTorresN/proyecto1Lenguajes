#ifndef OPERATIVEMENU_H
#define OPERATIVEMENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menuOperativo() {
    flag = 0;
    int opcion;
    do
    {
        printf("Menu Operativo \n");
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
            /* code */
            break;
        
        default:
            break;
        }
    } while (flag == 0);
    

}

#endif