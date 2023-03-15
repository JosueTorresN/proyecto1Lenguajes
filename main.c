#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operativeMenu.h"
#include "./backend/mySQLconnector.h"

void menuSelect()
{
    int bandera = 1;
    do {
        int option;
        printf("Selecione el tipo de menu que desea utilizar:  \n");
        printf("1. Menu Operativo \n");
        printf("2. Menu Administrativo \n");
        printf("3. Salir \n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            menuOperativo();
            break;
        case 2:
            // menuAdministrativo();
            break;
        case 3:
            printf("Saliendo del programa... \n");
            bandera = 0;
            break;
        default:    
            printf("Opcion no valida, intente de nuevo \n");
            menuSelect();
            break;
        }
    } while (bandera);

}

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    // SitioEventos* sitioEventos = NULL;
    // sitioEventos = agregarSitioEventos(sitioEventos ,crearSitioEventos("hola", "hala", "holo", "illo"));
    // imprimirSitioEventos(sitioEventos);
    // imprimirSitioEventos(getSitioEventos());
    // getSitioEventos();
    // menuOperativo();
    menuSelect();
    return 0;
}