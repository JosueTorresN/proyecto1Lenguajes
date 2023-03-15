#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "credenciales.h"
#include "../models/sitioEventos.h"


int conectar(MYSQL **conexion);
void ejecutar_consultas(MYSQL *conexion,char *consulta);

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
        printf("Coneccion exitosa \n");
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

////Funcion encargada de insertar sitios de enventos
int insertSitioEventos(char *nombre, char *ubicacion, char *sitioWeb){
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        char par1[200] = "insert into sitioEventos (nombre, ubicacion, sitioWeb)values(";
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