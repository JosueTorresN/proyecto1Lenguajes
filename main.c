#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operativeMenu.h"
#include "./backend/mySQLconnector.h"

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    imprimirSitioEventos(getSitioEventos());
    // getSitioEventos();
    // menuOperativo();
    return 0;
}