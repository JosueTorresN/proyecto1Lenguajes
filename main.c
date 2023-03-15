#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operativeMenu.h"
#include "./backend/mySQLconnector.h"

void menuSelect()
{
    int option;
    printf("Selecione el tipo de menu que desea utilizar: \n");
    printf("1. Menu Operativo \n");
    printf("2. Menu Administrativo \n");
    printf("3. Salir \n");

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    // SitioEventos* sitioEventos = NULL;
    // sitioEventos = agregarSitioEventos(sitioEventos ,crearSitioEventos("hola", "hala", "holo", "illo"));
    // imprimirSitioEventos(sitioEventos);
    imprimirSitioEventos(getSitioEventos());
    // getSitioEventos();
    // menuOperativo();
    return 0;
}