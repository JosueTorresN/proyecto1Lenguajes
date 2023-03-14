#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "credenciales.h"

int conectar(MYSQL **conexion);
void ejecutar_consultas(MYSQL *conexion,char *consulta);


int main (int arg, char *argv[]){
    int error;
    MYSQL *conexion;
    char *consulta;
    error = conectar(&conexion);
    if(!error){
        consulta = "SELECT * FROM sitioEventos";
        ejecutar_consultas(conexion,consulta);
    }
    return 0;
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