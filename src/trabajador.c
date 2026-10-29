#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/trabajador.h"

void trabajador(char *trabajadorBuscado, char idTrabajador[][10], char nombreTrabajador[][30], char apellidoTrabajador[][30], char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char descripcionMision[][100], char prioridadMision[][10], char estadoMision[][20], int cantMisiones, int cantTrabajadoresPorMision[], char misionAsignada[][10], char trabajadorAsignado[][10], int cantTrabajadores, int cantAsignaciones) {
    int posTrabajadorAsignado = -1;
    int posMisionAsignada = -1;
    
    printf("\n");
    if (cantTrabajadores != 0) {
        // Busca la misión asignada al trabajador seleccionado (vuelve por referencia el índice del trabajador)
        posMisionAsignada = buscarMisionTrabajador(trabajadorBuscado, idTrabajador, cantAsignaciones, cantMisiones, trabajadorAsignado, misionAsignada, idMision, cantTrabajadores, &posTrabajadorAsignado);
        
        // Inicia el panel correspondiente al trabajador
        menuTrabajador(idMision, posMisionAsignada, idTrabajador, posTrabajadorAsignado, tipoMision, provinciaMision, localidadMision, descripcionMision, prioridadMision, estadoMision, nombreTrabajador, apellidoTrabajador, cantMisiones);
    } else {
        printf("\n==========================================================\n");
        printf("                  PANEL DEL TRABAJADOR                    \n");
        printf("==========================================================\n\n");
        printf("No existen trabajadores cargados en el sistema.\n\n");
        printf("Presiona cualquier tecla para continuar\n");
        getchar(); getchar();
    }
}

int buscarMisionTrabajador(char *trabajadorBuscado, char idTrabajador[][10], int cantAsignaciones, int cantidadMisiones, char trabajadorAsignado[][10], char misionAsignada[][10], char idMision[][10], int cantTrabajadores, int *posTrabajadorAsignado) {
    int i = 0, j = 0;
    int indiceMisionAsignada = -1;
    *posTrabajadorAsignado = -1;
    
    // Buscar una asignación del trabajador en el vector de asignaciones
    while (i < cantAsignaciones && indiceMisionAsignada == -1) {
        if (strcmp(trabajadorAsignado[i], trabajadorBuscado) == 0) {
            char misionBuscada[10];
            strcpy(misionBuscada, misionAsignada[i]);
            
            // Buscar el ID de la misión en el vector de misiones
            j = 0;
            while (j < cantidadMisiones && indiceMisionAsignada == -1) {
                if (strcmp(idMision[j], misionBuscada) == 0) {
                    indiceMisionAsignada = j;
                } else {
                    j++;
                }
            }
        }
        i++;
    }
    
    // Buscar la posición del trabajador en el vector de trabajadores
    i = 0;
    while (i < cantTrabajadores && *posTrabajadorAsignado == -1) {
        if (strcmp(idTrabajador[i], trabajadorBuscado) == 0) {
            *posTrabajadorAsignado = i;
        } else {
            i++;
        }
    }
    
    return indiceMisionAsignada;
}

void menuTrabajador(char idMision[][10], int posMisionAsig, char idTrabajador[][10], int posTrabajadorAsig, char tipoMision[][30], char provMision[][30], char localidadMision[][30], char descripMision[][100], char prioriMision[][10], char estadoMision[][20], char nomTrabajador[][30], char apeTrabajador[][30], int cantMisiones) {
    int opc;
    
    // Control por si el índice del trabajador no fue encontrado
    if (posTrabajadorAsig == -1) {
        printf("[ERROR] No se encontro al trabajador en los registros.\n");
        printf("Presione una tecla para continuar...\n");
        getchar(); getchar();
        return;
    }
    
    do {
        printf("\n==========================================================\n");
        printf("                 MENU DEL TRABAJADOR                      \n");
        printf("==========================================================\n");
        printf("ID: %s\n", idTrabajador[posTrabajadorAsig]);
        printf("Bienvenido %s %s\n\n", nomTrabajador[posTrabajadorAsig], apeTrabajador[posTrabajadorAsig]);
        printf("[1] Ver mision asignada\n");
        printf("[2] Ver estado\n");
        printf("[3] Cambiar estado\n");
        printf("[4] Cerrar sesion\n");
        printf("----------------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opc);
        
        switch(opc) {
            case 1:
                verMision(idMision, posMisionAsig, tipoMision, provMision, localidadMision, descripMision, prioriMision, estadoMision, cantMisiones);
                break;
            case 2:
                verEstado(idMision, posMisionAsig, estadoMision, cantMisiones);
                break;
            case 3:
                cambiarEstado(idMision, posMisionAsig, estadoMision, cantMisiones);
                break;
            case 4:
                printf("\nCerrando sesion...\n");
                break;
            default:
                printf("\nOpcion incorrecta. Vuelva a intentarlo\n");
        }
    } while (opc != 4);
}

void verMision(char idMision[][10], int posMisionAsig, char tipoMision[][30], char provMision[][30], char localidadMision[][30], char descripMision[][100], char prioriMision[][10], char estadoMision[][20], int cantMisiones) {
    printf("\n+----------------------------------------------------------+\n");
    printf("|                    MISION ASIGNADA                       |\n");
    printf("+----------------------------------------------------------+\n");
    
    if (posMisionAsig >= 0 && posMisionAsig < cantMisiones) {
        printf("| ID Mision    : %s\n", idMision[posMisionAsig]);
        printf("| Tipo         : %s\n", tipoMision[posMisionAsig]);
        printf("| Provincia    : %s\n", provMision[posMisionAsig]);
        printf("| Localidad    : %s\n", localidadMision[posMisionAsig]);
        printf("| Descripcion  : %s\n", descripMision[posMisionAsig]);
        printf("| Nivel        : %s\n", prioriMision[posMisionAsig]);
        printf("+----------------------------------------------------------+\n");
    } else {
        printf("[ERROR] Este trabajador no tiene ninguna mision asignada.\n");
    }
    printf("\nPresione Enter para continuar...\n");
    getchar(); getchar();
}

void verEstado(char idMision[][10], int posMisionAsig, char estadoMision[][20], int cantMisiones) {
    printf("\n+----------------------------------------------------------+\n");
    printf("|                    ESTADO DE MISION                      |\n");
    printf("+----------------------------------------------------------+\n");
    
    if (posMisionAsig >= 0 && posMisionAsig < cantMisiones) {
        printf("| Mision       : %s\n", idMision[posMisionAsig]);
        printf("| Estado actual: %s\n", estadoMision[posMisionAsig]);
        printf("+----------------------------------------------------------+\n");
    } else {
        printf("Este trabajador no tiene ninguna mision asignada.\n");
    }
    printf("\nPresione Enter para continuar...\n");
    getchar(); getchar();
}

void cambiarEstado(char idMision[][10], int posMisionAsig, char estadoMision[][20], int cantMisiones) {
    int opcionEstado;
    
    printf("\n+----------------------------------------------------------+\n");
    printf("|                    CAMBIAR ESTADO                        |\n");
    printf("+----------------------------------------------------------+\n");
    
    if (posMisionAsig >= 0 && posMisionAsig < cantMisiones) {
        printf("| Mision       : %s\n", idMision[posMisionAsig]);
        printf("| Estado actual: %s\n\n", estadoMision[posMisionAsig]);
        
        if (strcmp(estadoMision[posMisionAsig], "Controlada") == 0) {
            printf("La mision ya se encuentra controlada.\n");
            printf("No es posible modificar su estado.\n");
            printf("----------------------------------------------------------\n");
        } else {
            printf("[1] En camino\n");
            printf("[2] En curso\n");
            printf("[3] Controlada\n");
            printf("[4] Volver\n");
            printf("----------------------------------------------------------\n");
            printf("Seleccione una opcion: ");
            scanf("%d", &opcionEstado);
            
            switch(opcionEstado) {
                case 1:
                    if (strcmp(estadoMision[posMisionAsig], "En camino") == 0) {
                        printf("La mision ya se encuentra en camino.\n");
                    } else {
                        printf("No se puede volver al estado En camino.\n");
                    }
                    break;
                case 2:
                    if (strcmp(estadoMision[posMisionAsig], "En camino") == 0) {
                        strcpy(estadoMision[posMisionAsig], "En curso");
                        printf("Se cambio el estado correctamente a En curso\n");
                    } else if (strcmp(estadoMision[posMisionAsig], "En curso") == 0) {
                        printf("La mision ya se encuentra En curso.\n");
                    } else {
                        printf("No se puede pasar una mision Controlada a En curso.\n");
                    }
                    break;
                case 3:
                    if (strcmp(estadoMision[posMisionAsig], "En curso") == 0) {
                        strcpy(estadoMision[posMisionAsig], "Controlada");
                        printf("Se cambio el estado correctamente a Controlada\n");
                    } else {
                        printf("La mision debe estar En curso antes de ser Controlada.\n");
                    }
                    break;
                case 4:
                    printf("Volviendo...\n");
                    break;
                default:
                    printf("Opcion incorrecta.\n");
            }
        }
    } else {
        printf("[ERROR] Este trabajador no tiene ninguna mision asignada.\n");
    }
    printf("\nPresione cualquier tecla para continuar...\n");
    getchar(); getchar();
}