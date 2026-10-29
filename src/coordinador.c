#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/coordinador.h"

void coordinador(char *idCoordinador, char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char descripcionMision[][100], char prioridadMision[][10], char estadoMision[][20], int *cantidadMisiones, char idTrabajador[][10], char nombreTrabajador[][30], char apellidoTrabajador[][30], int cantidadTrabajadores, char misionAsignada[][10], char trabajadorAsignado[][10], int *cantidadAsignaciones, int cantidadTrabajadoresPorMision[], int maximoMisiones, int maximoTrabajadoresPorMision, int maximoAsignaciones, char stockId[][10], char stockNombre[][30], char stockCategoria[][30], int stockCantidad[], char stockUnidad[][10], char stockEstado[][20], int *totalStock, int *acumuladoDonaciones) {
    int opcion;
    
    do {
        printf("\n ================ PANEL DE COORDINADOR ================ \n");
        printf("ID: %s\n", idCoordinador);
        printf("Fondos disponibles: $%d\n", *acumuladoDonaciones);
        printf("\n");
        printf("[1] Crear mision\n");
        printf("[2] Misiones activas\n");
        printf("[3] Asignar trabajadores\n"); // relacionado con Trabajadores (asigna personal a misiones)
        printf("[4] Stock y compra de insumos\n");
        printf("[5] Cerrar sesion\n");
        printf("------------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                crearMision(idMision, tipoMision, provinciaMision, localidadMision, descripcionMision, prioridadMision, estadoMision, cantidadMisiones, maximoMisiones, cantidadTrabajadoresPorMision);
                break;
            case 2:
                mostrarMisionesActivas(idMision, tipoMision, provinciaMision, localidadMision, prioridadMision, estadoMision, *cantidadMisiones);
                printf("\nPresione una tecla para volver al menu...\n");
                getchar(); getchar();
                break;
            case 3:
                // relación con trabaja y admin (gestiona vec de asig)
                asignarTrabajadores(idMision, tipoMision, provinciaMision, prioridadMision, estadoMision, *cantidadMisiones, idTrabajador, nombreTrabajador, apellidoTrabajador, cantidadTrabajadores, misionAsignada, trabajadorAsignado, cantidadAsignaciones, cantidadTrabajadoresPorMision, maximoTrabajadoresPorMision, maximoAsignaciones);
                printf("\nPresione una tecla para volver al menu...\n");
                getchar(); getchar();
                break;
            case 4:
                gestionarStock(stockId, stockNombre, stockCategoria, stockCantidad, stockUnidad, stockEstado, totalStock, acumuladoDonaciones);
                break;
            case 5:
                printf("Sesion cerrada correctamente.\n");
                break;
            default:
                printf("Opcion incorrecta. Ingrese un numero valido.\n");
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
        }
    } while(opcion != 5);
}

void crearMision(char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char descripcionMision[][100], char prioridadMision[][10], char estadoMision[][20], int *cantidadMisiones, int maximoMisiones, int cantidadTrabajadoresPorMision[]) {
    char confirmacion[10];
    int urgencia;
    
    if (*cantidadMisiones >= maximoMisiones) {
        printf("[ERROR] Se alcanzo el maximo de misiones permitidas.\n");
    } else {
        int i = *cantidadMisiones;
        
        if (i + 1 < 10) {
            sprintf(idMision[i], "M0%d", i + 1);
        } else {
            sprintf(idMision[i], "M%d", i + 1);
        }
        
        printf("--- CREAR NUEVA MISION ---\n");
        printf("ID asignado: %s\n", idMision[i]);
        printf("Tipo de emergencia: ");
        scanf(" %[^\n]", tipoMision[i]);
        printf("Zona / Provincia: ");
        scanf(" %[^\n]", provinciaMision[i]);
        printf("Localidad / Area: ");
        scanf(" %[^\n]", localidadMision[i]);
        printf("Descripcion: ");
        scanf(" %[^\n]", descripcionMision[i]);
        
        do {
            printf("Nivel de urgencia [1] BAJA   [2] MEDIA   [3] ALTA: ");
            scanf("%d", &urgencia);
            if (urgencia == 1) strcpy(prioridadMision[i], "BAJA");
            else if (urgencia == 2) strcpy(prioridadMision[i], "MEDIA");
            else if (urgencia == 3) strcpy(prioridadMision[i], "ALTA");
            else {
                printf("[ERROR] Opcion invalida. Elija 1, 2 o 3.\n");
                urgencia = 0;
            }
        } while (urgencia == 0);
        
        strcpy(estadoMision[i], "En camino"); // estado que luego visualiza y modifica el traba?
        
        printf("\n+----------------------------------------------------------+\n");
        printf("|                 VISTA PREVIA DE LA MISION                |\n");
        printf("+----------------------------------------------------------+\n");
        printf("| Tipo      : %s\n", tipoMision[i]);
        printf("| Ubicacion : %s - %s\n", provinciaMision[i], localidadMision[i]);
        printf("| Urgencia  : %s\n", prioridadMision[i]);
        printf("| Detalle   : %s\n", descripcionMision[i]);
        printf("+----------------------------------------------------------+\n\n");
        
        do {
            printf("CONFIRMAR CREACION DE LA MISION? (S/N): ");
            scanf(" %[^\n]", confirmacion);
            if (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "s") != 0 && 
                strcmp(confirmacion, "N") != 0 && strcmp(confirmacion, "n") != 0) {
                printf("[ERROR] Opcion invalida. Debe ingresar S o N.\n");
            }
        } while (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "s") != 0 && 
                 strcmp(confirmacion, "N") != 0 && strcmp(confirmacion, "n") != 0);
        
        if (strcmp(confirmacion, "S") == 0 || strcmp(confirmacion, "s") == 0) {
            cantidadTrabajadoresPorMision[i] = 0;
            (*cantidadMisiones)++;
            printf("----------------------------------------------------------\n");
            printf("  [OK] MISION REGISTRADA CON ID: %s\n", idMision[i]);
            printf("----------------------------------------------------------\n");
        } else {
            printf("----------------------------------------------------------\n");
            printf("  [X] MISION CANCELADA. Los datos no se guardaron.\n");
            printf("----------------------------------------------------------\n");
            strcpy(idMision[i], "");
            strcpy(tipoMision[i], "");
            strcpy(provinciaMision[i], "");
            strcpy(localidadMision[i], "");
            strcpy(descripcionMision[i], "");
            strcpy(prioridadMision[i], "");
            strcpy(estadoMision[i], "");
        }
    }
    printf("\nPresione una tecla para continuar...\n");
    getchar(); getchar();
}

void mostrarMisionesActivas(char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char prioridadMision[][10], char estadoMision[][20], int cantidadMisiones) {
    int activas = 0;
    
    printf("--- MISIONES ACTIVAS ---\n");
    printf("----------------------------------------------------------\n");
    for (int j = 0; j < cantidadMisiones; j++) {
        if (strcmp(estadoMision[j], "Controlada") != 0) {
            printf("%s | %s | %s - %s | Urgencia: %s | Estado: %s\n", 
                   idMision[j], tipoMision[j], provinciaMision[j], localidadMision[j], prioridadMision[j], estadoMision[j]);
            activas++;
        }
    }
    if (activas == 0) {
        printf("No hay misiones activas registradas.\n");
    }
    printf("----------------------------------------------------------\n");
}

char* misionDeTrabajador(char trabajadorAsignado[][10], char misionAsignada[][10], int cantidadAsignaciones, char *idBuscado) {
    static char misionActual[10];
    strcpy(misionActual, "");
    for (int i = 0; i < cantidadAsignaciones; i++) {
        if (strcmp(trabajadorAsignado[i], idBuscado) == 0) {
            strcpy(misionActual, misionAsignada[i]);
        }
    }
    return misionActual;
}

void asignarTrabajadores(char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char prioridadMision[][10], char estadoMision[][20], int cantidadMisiones, char idTrabajador[][10], char nombreTrabajador[][30], char apellidoTrabajador[][30], int cantidadTrabajadores, char misionAsignada[][10], char trabajadorAsignado[][10], int *cantidadAsignaciones, int cantidadTrabajadoresPorMision[], int maximoTrabajadoresPorMision, int maximoAsignaciones) {
    char confirmacion[10], idMisionBuscada[10], idTrabajadorBuscado[10];
    int posMision = -1, posTrabajador = -1, activas = 0;
    
    printf("--- ASIGNAR TRABAJADORES ---\n");
    
    if (cantidadMisiones == 0) {
        printf("No hay misiones registradas.\n");
    } else if (cantidadTrabajadores == 0) {
        printf("No hay trabajadores cargados.\n"); // gestionados por el admin
    } else {
        printf("MISIONES DISPONIBLES:\n");
        printf("----------------------------------------------------------\n");
        for (int j = 0; j < cantidadMisiones; j++) {
            if (strcmp(estadoMision[j], "Controlada") != 0) {
                printf("[%s] %s | %s | %s | Urgencia: %s | Trabajadores: %d/%d\n", 
                       idMision[j], tipoMision[j], provinciaMision[j], prioridadMision[j], 
                       cantidadTrabajadoresPorMision[j], maximoTrabajadoresPorMision);
                activas++;
            }
        }
        printf("----------------------------------------------------------\n");
        
        if (activas == 0) {
            printf("No hay misiones activas para asignar.\n");
        } else {
            do {
                printf("Ingrese el ID de la mision (ej: M01) o 0 para cancelar: ");
                scanf(" %[^\n]", idMisionBuscada);
                if (strcmp(idMisionBuscada, "0") != 0) {
                    for (int i = 0; i < cantidadMisiones; i++) {
                        if (strcmp(idMision[i], idMisionBuscada) == 0 && strcmp(estadoMision[i], "Controlada") != 0) {
                            posMision = i;
                        }
                    }
                    if (posMision == -1) printf("[ERROR] La mision no existe o ya esta controlada.\n");
                } else break;
            } while (posMision == -1);
            
            if (posMision != -1) {
                if (cantidadTrabajadoresPorMision[posMision] >= maximoTrabajadoresPorMision) {
                    printf("[ERROR] La mision %s ya tiene el maximo de %d trabajadores.\n", idMision[posMision], maximoTrabajadoresPorMision);
                } else {
                    printf("\nLISTA DE TRABAJADORES:\n");
                    printf("----------------------------------------------------------\n");
                    for (int i = 0; i < cantidadTrabajadores; i++) {
                        char *misionOcupada = misionDeTrabajador(trabajadorAsignado, misionAsignada, *cantidadAsignaciones, idTrabajador[i]);
                        if (strlen(misionOcupada) == 0) {
                            printf("%s - %s %s (libre)\n", idTrabajador[i], nombreTrabajador[i], apellidoTrabajador[i]);
                        } else {
                            printf("%s - %s %s (en mision %s)\n", idTrabajador[i], nombreTrabajador[i], apellidoTrabajador[i], misionOcupada);
                        }
                    }
                    printf("----------------------------------------------------------\n");
                    
                    do {
                        printf("Ingrese ID del trabajador a asignar (ej: T02) o 0 para cancelar: ");
                        scanf(" %[^\n]", idTrabajadorBuscado);
                        if (strcmp(idTrabajadorBuscado, "0") != 0) {
                            for (int i = 0; i < cantidadTrabajadores; i++) {
                                if (strcmp(idTrabajador[i], idTrabajadorBuscado) == 0) posTrabajador = i;
                            }
                            if (posTrabajador == -1) printf("[ERROR] Ese trabajador no existe.\n");
                        } else break;
                    } while (posTrabajador == -1);
                    
                    if (posTrabajador != -1) {
                        char *misionOcupada = misionDeTrabajador(trabajadorAsignado, misionAsignada, *cantidadAsignaciones, idTrabajador[posTrabajador]);
                        if (strlen(misionOcupada) > 0) {
                            printf("[ERROR] El trabajador %s ya esta asignado a la mision %s.\n", idTrabajador[posTrabajador], misionOcupada);
                        } else {
                            printf("\n+----------------------------------------------------------+\n");
                            printf("|                   CONFIRMAR ASIGNACION                   |\n");
                            printf("+----------------------------------------------------------+\n");
                            printf("| Mision  : %s\n", idMision[posMision]);
                            printf("| Personal: %s - %s %s\n", idTrabajador[posTrabajador], nombreTrabajador[posTrabajador], apellidoTrabajador[posTrabajador]);
                            printf("+----------------------------------------------------------+\n");
                            
                            do {
                                printf("CONFIRMAR ASIGNACION DEL TRABAJADOR? (S/N): ");
                                scanf(" %[^\n]", confirmacion);
                                if (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "s") != 0 && 
                                    strcmp(confirmacion, "N") != 0 && strcmp(confirmacion, "n") != 0) {
                                    printf("[ERROR] Opcion invalida. Debe ingresar S o N.\n");
                                }
                            } while (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "s") != 0 && 
                                     strcmp(confirmacion, "N") != 0 && strcmp(confirmacion, "n") != 0);
                            
                            if (strcmp(confirmacion, "S") == 0 || strcmp(confirmacion, "s") == 0) {
                                if (*cantidadAsignaciones >= maximoAsignaciones) {
                                    printf("[ERROR] Se alcanzo el limite de asignaciones.\n");
                                } else {
                                    strcpy(misionAsignada[*cantidadAsignaciones], idMision[posMision]);
                                    strcpy(trabajadorAsignado[*cantidadAsignaciones], idTrabajador[posTrabajador]);
                                    (*cantidadAsignaciones)++;
                                    cantidadTrabajadoresPorMision[posMision]++;
                                    printf("[OK] Trabajador %s asignado a la mision %s\n", idTrabajador[posTrabajador], idMision[posMision]);
                                    printf("Ahora la mision tiene %d trabajador(es).\n", cantidadTrabajadoresPorMision[posMision]);
                                }
                            } else {
                                printf("[X] Asignacion cancelada.\n");
                            }
                        }
                    }
                }
            }
        }
    }
}

void gestionarStock(char stockId[][10], char stockNombre[][30], char stockCategoria[][30], int stockCantidad[], char stockUnidad[][10], char stockEstado[][20], int *totalStock, int *acumuladoDonaciones) {
    int opStock, filaMod, cantCompra, costoUnitario, costoTotal;
    char nuevoEstado[20];
    
    do {
        printf("\n--- GESTION DE STOCK E INSUMOS ---\n");
        printf("Fondos disponibles para compras: $%d\n", *acumuladoDonaciones); // comparte fondos globales con el mod finan
        printf("------------------------------------------------------------\n");
        for (int j = 1; j <= *totalStock; j++) {
            printf("[%d] %s | %s | %s | %d %s | %s\n", 
                   j, stockId[j], stockNombre[j], stockCategoria[j], stockCantidad[j], stockUnidad[j], stockEstado[j]);
        }
        printf("------------------------------------------------------------\n\n");
        printf("[1] Modificar cantidad y estado de un insumo\n");
        printf("[2] Agregar un nuevo insumo\n");
        printf("[3] Comprar insumo con los fondos disponibles\n");
        printf("[4] Volver al menu principal\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opStock);
        
        switch(opStock) {
            case 1:
                printf("Ingrese el numero del insumo a modificar (1 al %d): ", *totalStock);
                scanf("%d", &filaMod);
                if (filaMod >= 1 && filaMod <= *totalStock) {
                    printf("Insumo seleccionado: %s\n", stockNombre[filaMod]);
                    printf("Ingrese la nueva cantidad actual: ");
                    scanf("%d", &stockCantidad[filaMod]);
                    do {
                        printf("Ingrese el nuevo estado (Optimo / Bajo / Critico): ");
                        scanf(" %[^\n]", nuevoEstado);
                        if (strcasecmp(nuevoEstado, "OPTIMO") != 0 && 
                            strcasecmp(nuevoEstado, "BAJO") != 0 && 
                            strcasecmp(nuevoEstado, "CRITICO") != 0) {
                            printf("[ERROR] Estado invalido.\n");
                        }
                    } while (strcasecmp(nuevoEstado, "OPTIMO") != 0 && 
                             strcasecmp(nuevoEstado, "BAJO") != 0 && 
                             strcasecmp(nuevoEstado, "CRITICO") != 0);
                    strcpy(stockEstado[filaMod], nuevoEstado);
                    printf("[OK] Stock actualizado correctamente.\n");
                } else {
                    printf("[ERROR] Numero de insumo invalido.\n");
                }
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
                break;
                
            case 2:
                if (*totalStock < 10) {
                    (*totalStock)++;
                    printf("--- AGREGAR NUEVO INSUMO ---\n");
                    printf("Ingrese ID (ej: S06): ");
                    scanf(" %[^\n]", stockId[*totalStock]);
                    printf("Ingrese nombre del insumo: ");
                    scanf(" %[^\n]", stockNombre[*totalStock]);
                    printf("Ingrese categoria: ");
                    scanf(" %[^\n]", stockCategoria[*totalStock]);
                    printf("Ingrese cantidad: ");
                    scanf("%d", &stockCantidad[*totalStock]);
                    printf("Ingrese unidad de medida (lts/kg/uds): ");
                    scanf(" %[^\n]", stockUnidad[*totalStock]);
                    printf("Ingrese estado (Optimo/Bajo/Critico): ");
                    scanf(" %[^\n]", stockEstado[*totalStock]);
                    printf("[OK] Nuevo insumo agregado al stock.\n");
                } else {
                    printf("[ERROR] Se alcanzo el limite maximo de 10 insumos.\n");
                }
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
                break;
                
            case 3:
                if (*acumuladoDonaciones <= 0) {
                    printf("[ERROR] No hay fondos disponibles. Finanzas debe registrar donaciones.\n"); // dependencia del mod finan
                } else {
                    printf("Ingrese el numero del insumo a comprar (1 al %d): ", *totalStock);
                    scanf("%d", &filaMod);
                    if (filaMod >= 1 && filaMod <= *totalStock) {
                        printf("Insumo: %s\n", stockNombre[filaMod]);
                        printf("Costo por unidad ($): ");
                        scanf("%d", &costoUnitario);
                        printf("Cantidad a comprar: ");
                        scanf("%d", &cantCompra);
                        if (costoUnitario > 0 && cantCompra > 0) {
                            costoTotal = costoUnitario * cantCompra;
                            printf("Costo total: $%d\n", costoTotal);
                            if (costoTotal <= *acumuladoDonaciones) {
                                *acumuladoDonaciones -= costoTotal; // ddescuenta de los fondos globales compartidos confinan
                                stockCantidad[filaMod] += cantCompra;
                                printf("[OK] Compra realizada.\n");
                                printf("Nuevo stock de %s: %d %s\n", stockNombre[filaMod], stockCantidad[filaMod], stockUnidad[filaMod]);
                                printf("Fondos restantes: $%d\n", *acumuladoDonaciones);
                            } else {
                                printf("[ERROR] Fondos insuficientes. Disponible: $%d\n", *acumuladoDonaciones);
                            }
                        } else {
                            printf("[ERROR] Costo y cantidad deben ser mayores a 0.\n");
                        }
                    } else {
                        printf("[ERROR] Numero de insumo invalido.\n");
                    }
                }
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
                break;
                
            case 4:
                printf("Volviendo...\n");
                break;
                
            default:
                printf("Opcion invalida.\n");
                printf("Presione una tecla para continuar...\n");
                getchar(); getchar();
        }
    } while (opStock != 4);
}