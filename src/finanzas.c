#include <stdio.h>
#include <string.h>
#include "../include/finanzas.h"

void finanzas(char *idUsuario, int *acumuladoDonaciones, Mision misiones[], int cantMisiones, int donacionesPorMision[]) {
    int opFinanzas, monto, cantDistribuir, i;
    char idMisionDestino[10];

    do {
        printf("\n ================ PANEL DE FINANZAS ================ \n");
        printf("ID: %s\n", idUsuario);
        printf("Fondos disponibles para distribuir: %d\n", *acumuladoDonaciones);
        printf("[1] Ver estado financiero\n");
        printf("[2] Registrar donacion recibida\n");
        printf("[3] Distribuir fondos a una mision\n");
        printf("[4] Cerrar sesion\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opFinanzas);

        switch(opFinanzas) {
            case 1:
                printf("--- ESTADO FINANCIERO ACTUAL ---\n");
                printf("Fondos pendientes: %d\n", *acumuladoDonaciones);
                for(i = 1; i <= cantMisiones; i++) {
                    printf("%s | %s | %s | Recibido: %d\n", misiones[i].id, misiones[i].tipo, misiones[i].estado, donacionesPorMision[i]);
                }
                break;
            case 2:
                printf("Ingrese el monto recibido: ");
                scanf("%d", &monto);
                if (monto > 0) {
                    *acumuladoDonaciones += monto;
                    printf("[OK] Donacion registrada. Nuevo total disponible: %d\n", *acumuladoDonaciones);
                } else {
                    printf("[ERROR!] El monto debe ser mayor a 0.\n");
                }
                break;
            case 3:
                if (*acumuladoDonaciones <= 0) {
                    printf("No hay fondos disponibles.\n");
                } else {
                    printf("Ingrese el ID de la mision destino (ej: M01): ");
                    scanf("%s", idMisionDestino);
                    int posMision = -1;
                    for(i = 1; i <= cantMisiones; i++) {
                        if(strcmp(misiones[i].id, idMisionDestino) == 0 && strcmp(misiones[i].estado, "Controlada") != 0) {
                            posMision = i;
                        }
                    }
                    if(posMision == -1) {
                        printf("[ERROR!] Mision no encontrada o ya controlada.\n");
                    } else {
                        printf("Cantidad a enviar (maximo %d): ", *acumuladoDonaciones);
                        scanf("%d", &cantDistribuir);
                        if(cantDistribuir > 0 && cantDistribuir <= *acumuladoDonaciones) {
                            *acumuladoDonaciones -= cantDistribuir;
                            donacionesPorMision[posMision] += cantDistribuir;
                            printf("[OK] Fondos distribuidos con exito.\n");
                        } else {
                            printf("[ERROR!] Cantidad invalida.\n");
                        }
                    }
                }
                break;
            case 4:
                printf("Cerrando sesion de finanzas...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opFinanzas != 4);
}