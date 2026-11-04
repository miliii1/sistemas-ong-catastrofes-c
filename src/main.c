#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/admin.h"
#include "../include/coordinador.h"
#include "../include/trabajador.h"
#include "../include/finanzas.h"

#define MAX_MISIONES 20
#define MAX_ASIGNACIONES 100
#define MAX_STOCK 10

static void inicializarAdmin(char ids[][10], char usuarios[][50], char claves[][50],
                             char roles[][20], int *cu, char idA[][10], char nomA[][30],
                             char apeA[][30], int *ca) {
    strcpy(ids[0], "A01"); strcpy(usuarios[0], "admin");
    strcpy(claves[0], "admin"); strcpy(roles[0], "ADMINISTRADOR");
    strcpy(idA[0], "A01"); strcpy(nomA[0], "Administrador");
    strcpy(apeA[0], "Principal");
    *cu = 1; *ca = 1;
}

int main(void) {
    char idUsuario[MAX_USUARIOS][10] = {{0}};
    char nombreUsuario[MAX_USUARIOS][50] = {{0}};
    char contrasenaUsuario[MAX_USUARIOS][50] = {{0}};
    char rolUsuario[MAX_USUARIOS][20] = {{0}};
    char idAdministrador[MAX_ADMINISTRADORES][10] = {{0}};
    char nombreAdministrador[MAX_ADMINISTRADORES][30] = {{0}};
    char apellidoAdministrador[MAX_ADMINISTRADORES][30] = {{0}};
    char idTrabajador[MAX_TRABAJADORES][10] = {{0}};
    char nombreTrabajador[MAX_TRABAJADORES][30] = {{0}};
    char apellidoTrabajador[MAX_TRABAJADORES][30] = {{0}};
    int cantUsuarios=0, cantAdministradores=0, cantTrabajadores=0;

    char idMision[MAX_MISIONES][10]={{0}}, tipoMision[MAX_MISIONES][30]={{0}};
    char provinciaMision[MAX_MISIONES][30]={{0}}, localidadMision[MAX_MISIONES][30]={{0}};
    char descripcionMision[MAX_MISIONES][100]={{0}}, prioridadMision[MAX_MISIONES][10]={{0}};
    char estadoMision[MAX_MISIONES][20]={{0}};
    int cantMisiones=0, trabajadoresPorMision[MAX_MISIONES]={0};
    char misionAsignada[MAX_ASIGNACIONES][10]={{0}};
    char trabajadorAsignado[MAX_ASIGNACIONES][10]={{0}};
    int cantAsignaciones=0;
    char stockId[MAX_STOCK+1][10]={{0}}, stockNombre[MAX_STOCK+1][30]={{0}};
    char stockCategoria[MAX_STOCK+1][30]={{0}}, stockUnidad[MAX_STOCK+1][10]={{0}};
    char stockEstado[MAX_STOCK+1][20]={{0}};
    int stockCantidad[MAX_STOCK+1]={0}, totalStock=0;
    int acumuladoDonaciones=10000, donacionesPorMision[MAX_MISIONES]={0};

    if (!cargarUsuarios(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,&cantUsuarios,
        idAdministrador,nombreAdministrador,apellidoAdministrador,&cantAdministradores,
        idTrabajador,nombreTrabajador,apellidoTrabajador,&cantTrabajadores)) {
        inicializarAdmin(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,&cantUsuarios,
                         idAdministrador,nombreAdministrador,apellidoAdministrador,&cantAdministradores);
        guardarUsuarios(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,cantUsuarios,
            idAdministrador,nombreAdministrador,apellidoAdministrador,cantAdministradores,
            idTrabajador,nombreTrabajador,apellidoTrabajador,cantTrabajadores);
    }

    /* Datos iniciales de stock, compartidos con Coordinador. */
    totalStock=3;
    strcpy(stockId[1],"S01"); strcpy(stockNombre[1],"Agua"); strcpy(stockCategoria[1],"Hidratacion");
    stockCantidad[1]=100; strcpy(stockUnidad[1],"lts"); strcpy(stockEstado[1],"Optimo");
    strcpy(stockId[2],"S02"); strcpy(stockNombre[2],"Alimentos"); strcpy(stockCategoria[2],"Comida");
    stockCantidad[2]=50; strcpy(stockUnidad[2],"uds"); strcpy(stockEstado[2],"Bajo");
    strcpy(stockId[3],"S03"); strcpy(stockNombre[3],"Mantas"); strcpy(stockCategoria[3],"Abrigo");
    stockCantidad[3]=30; strcpy(stockUnidad[3],"uds"); strcpy(stockEstado[3],"Optimo");

    for (;;) {
        char usuario[50], clave[50];
        int pos=-1, opcionLogin=0, i;
        printf("\n==========================================================\n");
        printf("       RAIZ - ONG DE RESCATE ANTE CATASTROFES\n");
        printf("==========================================================\n");
        printf("Usuario: "); if (scanf(" %49s",usuario)!=1) break;
        printf("Contrasena: "); if (scanf(" %49s",clave)!=1) break;
        for(i=0;i<cantUsuarios;i++)
            if(!strcmp(nombreUsuario[i],usuario) && !strcmp(contrasenaUsuario[i],clave)) {pos=i;break;}

        if(pos>=0) {
            if(!strcmp(rolUsuario[pos],"ADMINISTRADOR")) {
                administrador(idUsuario[pos],idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,
                    &cantUsuarios,idAdministrador,nombreAdministrador,apellidoAdministrador,
                    &cantAdministradores,idTrabajador,nombreTrabajador,apellidoTrabajador,
                    &cantTrabajadores,trabajadorAsignado,misionAsignada,&cantAsignaciones,
                    idMision,cantMisiones,trabajadoresPorMision);
            } else if(!strcmp(rolUsuario[pos],"TRABAJADOR")) {
                trabajador(idUsuario[pos],idTrabajador,nombreTrabajador,apellidoTrabajador,
                    idMision,tipoMision,provinciaMision,localidadMision,descripcionMision,
                    prioridadMision,estadoMision,cantMisiones,trabajadoresPorMision,
                    misionAsignada,trabajadorAsignado,cantTrabajadores,cantAsignaciones);
            }
            continue;
        }

        printf("\nAcceso a modulos internos:\n");
        printf("[1] Coordinador  [2] Finanzas  [0] Reintentar/salir\n");
        printf("Opcion: ");
        if(scanf("%d",&opcionLogin)!=1) { int c; while((c=getchar())!='\n'&&c!=EOF){} continue; }
        if(opcionLogin==1) {
            char idC[10];
            printf("ID de coordinador (C01): "); scanf(" %9s",idC);
            if(!strcmp(idC,"C01") && !strcmp(clave,"coord123")) {
                coordinador(idC,idMision,tipoMision,provinciaMision,localidadMision,
                    descripcionMision,prioridadMision,estadoMision,&cantMisiones,
                    idTrabajador,nombreTrabajador,apellidoTrabajador,cantTrabajadores,
                    misionAsignada,trabajadorAsignado,&cantAsignaciones,trabajadoresPorMision,
                    MAX_MISIONES,5,MAX_ASIGNACIONES,stockId,stockNombre,stockCategoria,
                    stockCantidad,stockUnidad,stockEstado,&totalStock,&acumuladoDonaciones);
            } else printf("[ERROR] Credenciales de coordinador invalidas. Clave inicial: coord123.\n");
        } else if(opcionLogin==2) {
            char idF[10];
            printf("ID de finanzas (F01): "); scanf(" %9s",idF);
            if(!strcmp(idF,"F01") && !strcmp(clave,"fin123"))
                finanzas(idF,&acumuladoDonaciones,idMision,tipoMision,provinciaMision,
                         estadoMision,cantMisiones,donacionesPorMision);
            else printf("[ERROR] Credenciales de finanzas invalidas. Clave inicial: fin123.\n");
        } else if(opcionLogin==0) {
            printf("Saliendo del sistema...\n"); break;
        }
    }
    guardarUsuarios(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,cantUsuarios,
        idAdministrador,nombreAdministrador,apellidoAdministrador,cantAdministradores,
        idTrabajador,nombreTrabajador,apellidoTrabajador,cantTrabajadores);
    return 0;
}
