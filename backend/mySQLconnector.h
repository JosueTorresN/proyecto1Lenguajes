#ifndef MYSQLCONNECTOR_H
#define MYSQLCONNECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "credenciales.h"
#include "../models/sitioEventos.h"


int conectar(MYSQL **conexion);
void ejecutar_consultas(MYSQL *conexion,char *consulta);
void imprimir_matriz(char ***matriz, int filas, int columnas);
char*** generarMatrizDeValoresDeConsulta(MYSQL_RES *valor, int pFilas, int pColumnas);
int agregarAsiento(int pNumeroAsintos, int pEspacioEventoID, int pDisponibilidad);
int agregarEspacioEvento(char *nombre, char *inicialDelSector, int pCantidadEspacios, char* pSitioEventosID, int pMontoPrecioEspacio);
void crearAsientos(int pCantidadEspacios);
int retunTablas(char *tabla_Consultar);
int resertAsientos(int pIDespaciEvento);
int insertEventos(char *nombre, char *productora, int pSitioEventosID, char *fecha);
char*** getEvento(); 
char*** getInformacionTotalEvento(int pIdEvento);
char*** consultarXNombreEvento(char *pNombre);
// int insertSitioEventos(char *nombre, char *ubicacion, char *sitioWeb);

////Funcion encargada de insertar sitios de enventos
int insertarSitioEventos(char *nombre, char *ubicacion, char *sitioWeb){
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "insert into sitioEventos (nombre, ubicacion, sitioWeb)values(";
        // printf("Este es el nombre => %s \n",nombre);
        strcat(par1,"'");
        strcat(par1,nombre);
        strcat(par1,"'");
        strcat(par1,",");
        strcat(par1,"'");
        strcat(par1,ubicacion);
        strcat(par1,"'");
        strcat(par1,",");
        strcat(par1,"'");
        strcat(par1,sitioWeb);
        strcat(par1,"'");
        strcat(par1,")");
        // printf("%s\n",par1);
        
        if(!error){
            consulta = par1;
            if (mysql_query(conexion, par1)) {
            printf("Unable to insert data into Employee table\n");
            mysql_close(conexion);
            return 1;
            }printf("\n");
        }
        return 0;
    }
}

SitioEventos* getSitioEventosAux(MYSQL *conexion){
    MYSQL_RES *res_ptr;
    MYSQL_ROW res_fila;

    res_ptr = mysql_store_result(conexion);
    if(res_ptr){
        int filas = mysql_num_rows(res_ptr);
        int columnas = mysql_num_fields(res_ptr);
        int contador = 0;
        SitioEventos *sitioEventos = NULL;
        for (int i = 0; i < filas; i++)
        {
            res_fila = mysql_fetch_row(res_ptr);
            sitioEventos = agregarSitioEventos(sitioEventos,crearSitioEventos(res_fila[0], res_fila[1], res_fila[2], res_fila[3]));
        }
        
        return sitioEventos;
    }
    return NULL;
}

//Primerafuncion la cual se llama en el programa y se utiliza para iniciar la coneccion con la base de datos y para realizar las consultas a la misma. 
SitioEventos* getSitioEventos(){
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);

    if(error){
        printf("Error al conectarse a la DB \n");
        exit(1);
    }
    error = mysql_query(conexion, "SELECT * FROM sitioEventos");
    if(error){
        printf("Error al ejecutar la consulta \n");
        exit(1);
    }
    return getSitioEventosAux(conexion);

    // if(!error){
    //     consulta = "SELECT * FROM sitioEventos";
    //     ejecutar_consultas(conexion,consulta);
    //     mysql_close(conexion);
    // }
    // return 0;
}

int conectar(MYSQL **conexion){
    int error;
    *conexion = mysql_init(NULL);/*mysql_init(NULL);*/
    if(mysql_real_connect(*conexion,HOST,USERNAME,PASSWORD,DATABASE,PORT,NULL,0)!=NULL)
    {
        // printf("Coneccion exitosa \n");
        error = 0;
    }
    else{
        printf("Error al conectarse a la DB \n");
        error = 1;
    }
    return error;
    
}

void ejecutar_consultas(MYSQL *conexion,char *consulta){
    int error, filas, columnas;
    MYSQL_RES *res_ptr;
    MYSQL_FIELD *campo;
    MYSQL_ROW res_fila;
    error = mysql_query(conexion, consulta);
    if(!error){
        res_ptr = mysql_store_result(conexion);
        if(res_ptr){
            filas = mysql_num_rows(res_ptr);
            columnas = mysql_num_fields(res_ptr);
            while (campo = mysql_fetch_field(res_ptr)){
                printf("%15s",campo->name);
            }printf("\n");
            for(int i =1; i<=filas; i++){
                res_fila = mysql_fetch_row(res_ptr);
                for (int j = 0; j < columnas; j++){
                    printf("%15s",res_fila[j]);
                }
                printf("\n");
                

            }
            
        }else{
            printf("Error al mostrar tabla");
        }
    }else{
        printf("Error al ejecutar la consulta");
    }
}




/////////////////////////////

char*** getConsulta(char *tabla_Consultar){
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);
    printf("%s \n","pasa por aqui");
    if(!error){
        
        printf("%s \n","pasa por aqui x2");
        char consulta[100] = "Select * from ";
        
        strcat(consulta,tabla_Consultar);
    
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        //MYSQL_ROW res_fila;
        error = mysql_query(conexion, consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                char*** matriz = generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
                return matriz;
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }
        
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}

char*** generarMatrizDeValoresDeConsulta(MYSQL_RES *valor, int pFilas, int pColumnas){
    int filas = pFilas;
    int columnas = pColumnas;
    MYSQL_ROW res_fila;
    
    char ***matriz = (char***)malloc(filas * sizeof(char**));
    
    for (int i = 0; i < filas; i++) {
        matriz[i] = (char**)malloc(columnas * sizeof(char*));
        res_fila = mysql_fetch_row(valor);
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = (char*)malloc(256 * sizeof(char)); // Asignar memoria para la cadena de caracteres
            
            strcpy(matriz[i][j], res_fila[j]); // Copiar la cadena de caracteres a la memoria asignada
        }
    }
    imprimir_matriz(matriz, filas, columnas);
    return matriz;
}



void imprimir_matriz(char ***matriz, int filas, int columnas) {

    int i, j, k;
    for (i = 0; i < filas; i++) {
        printf("Fila %d: ", i+1);
        for (j = 0; j < columnas; j++) {
            printf("[");
            for (k = 0; matriz[i][j][k] != '\0'; k++) {
                printf("%c", matriz[i][j][k]);
            }
            printf("] ");
        }
        printf("\n");
    }
}


////////////////////////// Funcion encargada de agregar asientos
int agregarAsiento(int pNumeroAsintos, int pEspacioEventoID, int pDisponibilidad){
    char numeroAsintos[20];
    sprintf(numeroAsintos, "%d", pNumeroAsintos);
    char espacioEventoID[20];
    sprintf(espacioEventoID, "%d", pEspacioEventoID);
    char disponibilidad[20];
    sprintf(disponibilidad, "%d", pDisponibilidad);
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "insert into asiento (numeroAsineto, espacioEventoID, disponibilidad)values(";

        strcat(par1,numeroAsintos);
        strcat(par1,",");
        strcat(par1,espacioEventoID);
        strcat(par1,",");
        strcat(par1,disponibilidad);
        
        strcat(par1,")");
        // printf("%s\n",par1);
        
        if(!error){
            consulta = par1;
            if (mysql_query(conexion, par1)) {
            printf("Unable to insert data into Employee table\n");
            mysql_close(conexion);
            return 1;
            }printf("\n");
        }
        return 0;
    }
}

/////////////////////////FUNCION ENCARGADA DE INSERTAR  UN NUEVEO ESPACIO PARA EVENTO
int agregarEspacioEvento(char *nombre, char *inicialDelSector, int pCantidadEspacios, char* pSitioEventosID, int pMontoPrecioEspacio){
    
    char cantidadEspacios[20];
    sprintf(cantidadEspacios, "%d", pCantidadEspacios);
    char sitioEventosID[20];
    sprintf(sitioEventosID, "%s", pSitioEventosID);
    char montoPrecioEspacio[20];
    sprintf(montoPrecioEspacio, "%d", pMontoPrecioEspacio);
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "insert into espacioEvento (nombre, inicialDelSector, cantidadEspacios, sitioEventosID, montoPrecioEspacio)values(";
        strcat(par1,"'");
        strcat(par1,nombre);
        strcat(par1,"'");
        strcat(par1,",");
        strcat(par1,"'");
        strcat(par1,inicialDelSector);
        strcat(par1,"'");
        strcat(par1,",");
        strcat(par1,cantidadEspacios);
        strcat(par1,",");
        strcat(par1,sitioEventosID);
        strcat(par1,",");
        strcat(par1,montoPrecioEspacio);
        strcat(par1,")");
        printf("%s\n",par1);
        
        if(!error){
            consulta = par1;
            if (mysql_query(conexion, par1)) {
                printf("Unable to insert data into Employee table\n");
                mysql_close(conexion);

                // agregarAsiento(1,1,1);
                
                return 1;
            }printf("\n");
            crearAsientos(pCantidadEspacios);
            // printf("Bandera =>>\n");
        }
        return 0;
    }
}

void crearAsientos(int pCantidadEspacios){
    char*** matriz = getConsulta("espacioEvento");
    int tamano = retunTablas("espacioEvento");
    char* espacioEventoID = (char*)malloc(20 * sizeof(char));
    // char* temp = matriz[tamano][1];
    // printf("Tamano %d\n", tamano);
    espacioEventoID = matriz[tamano -1][0];
    // printf("Essspacio evento IDDDDDDDDDDDDDDDDD%s\n", temp);
    for (int i = 0; i < pCantidadEspacios; i++) {
        agregarAsiento(i+1, atoi(espacioEventoID), 0);
    }
}


////Funcion encargada de regresar la cantidad de filas de una tabla 
int retunTablas(char *tabla_Consultar){
    MYSQL_ROW row;
    MYSQL_RES *result;
    int num_rows = -1;
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "select count(*) from ";
        strcat(par1,tabla_Consultar);
        // printf("%s\n",par1);
        if(!error){
            consulta = par1;
            
            if(mysql_query(conexion, par1)) {
                printf("Unable to insert data into Employee table\n");

            }
            // Obtener el resultado de la consulta
            result = mysql_use_result(conexion);
            if (!result) {
                printf("Error al obtener el resultado de la consulta: %s\n", mysql_error(conexion));
                mysql_close(conexion);
                return -1;
            }
            if ((row = mysql_fetch_row(result))) {
                
                num_rows = atoi(row[0]);
            }

            // Liberar memoria y cerrar la conexión
            mysql_free_result(result);
            mysql_close(conexion);
            // printf("%i",num_rows);
            return num_rows;     
        }
        return 0;
    }
}


////Funcion encargada de resetear los campos de los asientos 
int resertAsientos(int pIDespaciEvento){
    char idEspacioEvento[20];
    sprintf(idEspacioEvento, "%d", pIDespaciEvento);
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "UPDATE asiento SET disponibilidad = 1 WHERE espacioEventoID = ";
        strcat(par1,idEspacioEvento);
        printf("%s\n",par1);
        
        if(!error){
            consulta = par1;
            if (mysql_query(conexion, par1)) {
            printf("Unable to insert data into Employee table\n");
            mysql_close(conexion);
            return 1;
            }printf("\n");
        }
        return 0;
    }
}



////Funcion encargada de insertar sitios de enventos
int insertEventos(char *nombre, char *productora, int pSitioEventosID, char *fecha){
    int error;
    MYSQL *conexion;
    char *consulta;

    char sitioEventosID[20];
    sprintf(sitioEventosID, "%d", pSitioEventosID);
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "insert into evento (nombre, productora, sitioEventosID, fecha)values(";
        strcat(par1,"'");
        strcat(par1,nombre);
        strcat(par1,"'");
        strcat(par1,",");
        strcat(par1,"'");
        strcat(par1,productora);
        strcat(par1,"'");
        strcat(par1,",");
        strcat(par1,sitioEventosID);
        strcat(par1,",");
        strcat(par1,"'");
        strcat(par1,fecha);
        strcat(par1,"'");
        strcat(par1,")");
        printf("%s\n",par1);
        
        if(!error){
            consulta = par1;
            if (mysql_query(conexion, par1)) {
            printf("Unable to insert data into Employee table\n");
            mysql_close(conexion);
            return 1;
            }printf("\n");
        }
        return 0;
    }
}


///Funcion creada para regresar la informacion de los estados de los eventos
char*** getConsultaEstadoEvento(){
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);

    if(!error){

        char consulta[300] = "select * from evento inner join espacioEvento on evento.sitioEventosID = espacioEvento.sitioEventosID inner join sitioEventos on espacioEvento.sitioEventosID = sitioEventos.sitioEventosID";
    
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        error = mysql_query(conexion, consulta);
        printf("%s \n",consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                char*** eventos = generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
                return eventos;
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }
        
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}


///Funcion encargada de realizar una consulta de las facturasXeventos que se encuentran en un rango de fechas establecido
char*** consultarFactura(char *pFecha1, char *pFecha2){
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);
    printf("%s \n","pasa por aqui");
    if(!error){
        
        printf("%s \n","pasa por aqui x2");
        char consulta[300] = "SELECT * FROM factura inner join evento on factura.eventosID =  evento.sitioEventosID WHERE evento.fecha BETWEEN ";
        strcat(consulta,"'");
        strcat(consulta,pFecha1);
        strcat(consulta,"'");
        strcat(consulta," and ");
        strcat(consulta,"'");
        strcat(consulta,pFecha2);
        strcat(consulta,"'");
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        //MYSQL_ROW res_fila;
        error = mysql_query(conexion, consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                char*** matriz = generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
                return matriz;
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }
        
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}


////Funcion encargada de insertar una factura
int agregarFactura(char *nombre, char *fecha, int pMonto, int pCedula, int pEventosID){
    char monto[20];
    sprintf(monto, "%d", pMonto);
    char cedula[20];
    sprintf(cedula, "%d", pCedula);
    char eventosID[20];
    sprintf(eventosID, "%d", pEventosID);
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char consulta[200] = "insert into factura (nombre, cedula, fecha, monto, eventosID)values(";
        strcat(consulta,"'");
        strcat(consulta,nombre);
        strcat(consulta,"'");
        strcat(consulta,",");
        strcat(consulta,cedula);
        strcat(consulta,",");
        strcat(consulta,"'");
        strcat(consulta,fecha);
        strcat(consulta,"'");
        strcat(consulta,",");
        strcat(consulta,monto);
        strcat(consulta,",");
        strcat(consulta,eventosID);
        
        strcat(consulta,")");
        printf("%s\n",consulta);
        
        if(!error){
            if (mysql_query(conexion, consulta)) {
            printf("Unable to insert data into Employee table\n");
            mysql_close(conexion);
            return 1;
            }printf("\n");
        }
        return 0;
    }
}



////Funcion encargada de regresar los sectores y asientos que se encuentran relacionados entre si
int getEspacioXAsiento(int pIDespacioEvento){
    char idEXA[20];
    sprintf(idEXA, "%d", pIDespacioEvento);
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);
    if(!error){        
        char consulta[300] = "Select * from espacioEvento inner join asiento on espacioEvento.espacioEventoID = asiento.espacioEventoID where espacioEvento.espacioEventoID = ";        
        strcat(consulta,idEXA);    
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        //MYSQL_ROW res_fila;
        error = mysql_query(conexion, consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }     
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}


///Funcion creada para regresar la informacion de la tabal eventos
char*** getEvento(){
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);

    if(!error){

        char consulta[300] = "select * from evento";
    
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        error = mysql_query(conexion, consulta);
        printf("%s \n",consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                char*** eventos = generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
                return eventos;
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }
        
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}



///Funcion encargada de regresar toda la info referente a un evento, el sitio el, asientos y espacios del evento
char*** getInformacionTotalEvento(int pIdEvento){
    char idEXA[20];
    sprintf(idEXA, "%d", pIdEvento);
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);
    printf("%s \n","pasa por aqui");
    if(!error){
        
        char consulta[400] = "select * from evento inner join espacioEvento on evento.sitioEventosID = espacioEvento.sitioEventosID inner join sitioEventos on espacioEvento.sitioEventosID = sitioEventos.sitioEventosID inner join asiento on espacioEvento.espacioEventoID = asiento.espacioEventoID where evento.eventosID = ";
        
        strcat(consulta,idEXA);
    
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        //MYSQL_ROW res_fila;
        error = mysql_query(conexion, consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                char*** matriz = generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
                return matriz;
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }
        
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}



///Funcion encargada de realizar una consulta por nombre del evento
char*** consultarXNombreEvento(char *pNombre){
    int error = 0;
    MYSQL *conexion;
    error = conectar(&conexion);
    printf("%s \n","pasa por aqui");
    if(!error){
        
        printf("%s \n","pasa por aqui x2");
        char consulta[300] = "SELECT * FROM evento WHERE evento.nombre = ";
        strcat(consulta,"'");
        strcat(consulta,pNombre);
        strcat(consulta,"'");
        int error, filas, columnas;
        MYSQL_RES *res_ptr;
        MYSQL_FIELD *campo;
        //MYSQL_ROW res_fila;
        error = mysql_query(conexion, consulta);
        if(!error){
            res_ptr = mysql_store_result(conexion);
            if(res_ptr){
                filas = mysql_num_rows(res_ptr);
                columnas = mysql_num_fields(res_ptr);
                char*** matriz = generarMatrizDeValoresDeConsulta(res_ptr,filas,columnas);
                mysql_close(conexion);
                return matriz;
            }
        }else{
            printf("Error al mostrar la tabla");
            exit(1);
        }
        
    }else{
        printf("Error al ejecutar la consulta");
        exit(1);
    }
}
#endif