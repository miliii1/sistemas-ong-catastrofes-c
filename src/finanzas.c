#include <stdio.h>
#include <string.h>
#include "../include/finanzas.h"

void finanzas(char *idFinanzas, int *acumuladoDonaciones, char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char estadoMision[][20], int cantidadMisiones, int donacionesPorMision[]) {
    int opFinanzas, monto, cantDistribuir, totalDistribuido;
    char idMisionDestino[10], confirmacion[10];

    do {
        printf("\n ================ PANEL DE FINANZAS ================ \n");
        printf("ID: %s\n", idFinanzas);
        printf("Fondos disponibles para distribuir: $%d\n", *acumuladoDonaciones);
        printf("-----------------------------------------------------\n");
        printf("[1] Ver estado financiero\n");
        printf("[2] Registrar donacion recibida\n");
        printf("[3] Distribuir fondos a una mision\n"); // se relaciona con el vector donacionesPorMision y las misiones creadas por coordi
        printf("[4] Cerrar sesion\n");
        printf("-----------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opFinanzas);

        switch(opFinanzas) {
            case 1:
                printf("\n--- ESTADO FINANCIERO ACTUAL ---\n");
                printf("Fondos pendientes de distribucion: $%d\n\n", *acumuladoDonaciones);
                printf("Fondos asignados por mision:\n");
                printf("-----------------------------------------------------\n");
                totalDistribuido = 0;
                if (cantidadMisiones == 0) {
                    printf("No hay misiones registradas.\n");
                } else {
                    for (int i = 0; i < cantidadMisiones; i++) {
                        printf("%s | %s | %s | Recibido: $%d\n", idMision[i], tipoMision[i], estadoMision[i], donacionesPorMision[i]);
                        totalDistribuido += donacionesPorMision[i];
                    }
                }
                printf("-----------------------------------------------------\n");
                printf("Total ya distribuido: $%d\n", totalDistribuido);
                printf("Total recaudado (distribuido + pendiente): $%d\n\n", totalDistribuido + *acumuladoDonaciones);
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
                break;
                
            case 2:
                printf("\n--- REGISTRAR DONACION ---\n");
                printf("Ingrese el monto recibido: ");
                scanf("%d", &monto);
                if (monto > 0) {
                    *acumuladoDonaciones += monto; // modifica fondos globales que tamb utiliza el coordi para compras de stock
                    printf("[OK] Donacion registrada. Fondos disponibles: $%d\n", *acumuladoDonaciones);
                } else {
                    printf("[ERROR] El monto debe ser mayor a 0.\n");
                }
                printf("\nPresione una tecla para continuar...\n");
                getchar(); getchar();
                break;
                
            case 3:
                printf("\n--- DISTRIBUIR FONDOS A MISIONES ---\n");
                if (*acumuladoDonaciones <= 0) {
                    printf("No hay fondos disponibles para distribuir.\n");
                } else if (cantidadMisiones == 0) {
                    printf("No hay misiones registradas.\n"); // depende de las misiones creadas por el coord
                } else {
                    printf("Fondos disponibles: $%d\n\n", *acumuladoDonaciones);
                    printf("MISIONES ACTIVAS:\n");
                    printf("-----------------------------------------------------\n");
                    for (int i = 0; i < cantidadMisiones; i++) {
                        if (strcmp(estadoMision[i], "Controlada") != 0) {
                            printf("%s | %s | %s | Recibido: $%d\n", idMision[i], tipoMision[i], provinciaMision[i], donacionesPorMision[i]);
                        }
                    }
                    printf("-----------------------------------------------------\n");
                    printf("Ingrese el ID de la mision destino (ej: M01): ");
                    scanf(" %[^\n]", idMisionDestino);
                    
                    int posMision = -1;
                    for (int i = 0; i < cantidadMisiones; i++) {
                        if (strcmp(idMision[i], idMisionDestino) == 0 && strcmp(estadoMision[i], "Controlada") != 0) {
                            posMision = i;
                        }
                    }
                    
                    if (posMision == -1) {
                        printf("[ERROR] La mision no existe o ya esta controlada.\n");
                    } else {
                        printf("Cantidad a enviar a %s (maximo $%d): ", idMisionDestino, *acumuladoDonaciones);
                        scanf("%d", &cantDistribuir);
                        
                        if (cantDistribuir > 0 && cantDistribuir <= *acumuladoDonaciones) {
                            do {
                                printf("Confirmar envio de $%d a %s? (S/N): ", cantDistribuir, idMisionDestino);
                                scanf(" %[^\n]", confirmacion);
                                if (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "s") != 0 && 
                                    strcmp(confirmacion, "N") != 0 && strcmp(confirmacion, "n") != 0) {
                                    printf("[ERROR] Opcion invalida. Debe ingresar S o N.\n");
                                }
                            } while (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "s") != 0 && 
                                     strcmp(confirmacion, "N") != 0 && strcmp(confirmacion, "n") != 0);
                            
                            if (strcmp(confirmacion, "S") == 0 || strcmp(confirmacion, "s") == 0) {
                                *acumuladoDonaciones -= cantDistribuir;
                                donacionesPorMision[posMision] += cantDistribuir;
                                printf("\n[OK] Se enviaron $%d a la mision %s\n", cantDistribuir, idMisionDestino);
                                printf("La mision ya acumula: $%d\n", donacionesPorMision[posMision]);
                                printf("Fondos restantes en Finanzas: $%d\n", *acumuladoDonaciones);
                            } else {
                                printf("[X] Distribucion cancelada.\n");
                            }
                        } else {
                            printf("[ERROR] Cantidad invalida o supera los fondos disponibles.\n");
                        }
                    }
                }
                printf("\nPresione una tecla para continuar...\n");
                getchar(); getchar();
                break;
                
            case 4:
                printf("Sesion cerrada correctamente.\n");
                break;
                
            default:
                printf("Opcion invalida.\n");
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
        }
    } while (opFinanzas != 4);
}
