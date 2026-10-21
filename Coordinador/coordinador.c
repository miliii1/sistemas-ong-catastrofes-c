#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//declaraciones de lo prototiposs
void mostrarMisionesActivas(char misiones[20][7][50], int totalMisiones);
void crearMision(char misiones[20][7][50], int *cantMisiones);
void coordinador(char idUsuario[], char misiones[20][7][50], int *cantMisiones, 
                 char trabajadoresPorMision[20][5][50], int cantTrabajadoresPorMision[20], 
                 int maximoMisiones, char trabajadores[40][3][50], int cantTrabajadores, 
                 char stock[10][7][50], int totalStock);

// ==========================================================
//                   MODULO COORDINADOR
// ==========================================================

void coordinador(char idUsuario[], char misiones[20][7][50], int *cantMisiones, 
                 char trabajadoresPorMision[20][5][50], int cantTrabajadoresPorMision[20], 
                 int maximoMisiones, char trabajadores[40][3][50], int cantTrabajadores, 
                 char stock[10][7][50], int totalStock) {
    int opcion;
    
    do {
        printf("\n ================ PANEL DE COORDINADOR ================ \n");
        printf("[1] Crear mision      [2] Misiones Activas      [3] Asignar trabajadores      [4] Ver Stock      [5] Cerrar Sesion \n");
        printf("--------------------------------------------------------------------------------------------------------------------\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                crearMision(misiones, cantMisiones);
                break;
            case 2:
                mostrarMisionesActivas(misiones, *cantMisiones);
                printf("\nPresione Enter para volver al menu...");
                getchar(); getchar(); 
                break;
            case 3:
                printf("\n[Modulo de asignacion de trabajadores en desarrollo]\n");
                printf("Presione Enter para volver al menu...");
                getchar(); getchar();
                break;
            case 4:
                printf("\n--- VER STOCK ---\n");
                printf("Total de stock actual: %d\n", totalStock);
                printf("Presione Enter para volver al menu...");
                getchar(); getchar();
                break;
            case 5:
                printf("\nSaliendo del panel de coordinador...\n");
                break;
            default:
                printf("Opcion Incorrecta. Ingrese un numero valido.\n");
                printf("Presione Enter para continuar...");
                getchar(); getchar();
        }
    } while (opcion != 5);
}

// ======================================= crear mision
void crearMision(char misiones[20][7][50], int *cantMisiones) {
    char confirmacion[10];
    int idx = *cantMisiones + 1;
    
    // se genera el id automatico de m01, m02...
    if (*cantMisiones == 0) {
        strcpy(misiones[1][0], "M01");
        idx = 1;
    } else {
        if (idx < 10) {
            sprintf(misiones[idx][0], "M0%d", idx);
        } else {
            sprintf(misiones[idx][0], "M%d", idx);
        }
    }
    
    printf("\n--- CREAR NUEVA MISION ---\n");
    printf("Tipo de emergencia: ");
    scanf(" %[^\n]", misiones[idx][1]); // lee cadenas con espacios
    printf("Zona / Provincia: ");
    scanf(" %[^\n]", misiones[idx][2]);
    printf("Localidad / Area: ");
    scanf(" %[^\n]", misiones[idx][3]);
    printf("Descripcion: ");
    scanf(" %[^\n]", misiones[idx][4]);
    
    int urgenciaOpc;
    printf("Nivel de urgencia [1] BAJA   [2] MEDIA   [3] ALTA: ");
    scanf("%d", &urgenciaOpc);
    
    if (urgenciaOpc == 1) strcpy(misiones[idx][5], "BAJA");
    else if (urgenciaOpc == 2) strcpy(misiones[idx][5], "MEDIA");
    else if (urgenciaOpc == 3) strcpy(misiones[idx][5], "ALTA");
    else strcpy(misiones[idx][5], "BAJA");
    
    strcpy(misiones[idx][6], "En camino");
    
    printf("\n+----------------------------------------------------------+\n");
    printf("|                VISTA PREVIA DE LA MISION                 |\n");
    printf("+----------------------------------------------------------+\n");
    printf("| Tipo      : %s\n", misiones[idx][1]);
    printf("| Ubicacion : %s - %s\n", misiones[idx][2], misiones[idx][3]);
    printf("| Urgencia  : %s\n", misiones[idx][5]);
    printf("| Detalle   : %s\n", misiones[idx][4]);
    printf("+----------------------------------------------------------+\n\n");
    
    do {
        printf("¿CONFIRMAR CREACION DE LA MISION? (S/N): ");
        scanf(" %s", confirmacion);
        
        if (strcmp(confirmacion, "s") == 0) strcpy(confirmacion, "S");
        if (strcmp(confirmacion, "n") == 0) strcpy(confirmacion, "N");
        
        if (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "N") != 0) {
            printf("[ERROR] Opcion invalida. Debe ingresar obligatoriamente S o N.\n");
        }
    } while (strcmp(confirmacion, "S") != 0 && strcmp(confirmacion, "N") != 0);
    
    if (strcmp(confirmacion, "S") == 0) {
        printf("----------------------------------------------------------\n");
        printf("  [OK] MISION REGISTRADA EXITOSAMENTE CON ID: %s\n", misiones[idx][0]);
        printf("----------------------------------------------------------\n");
        (*cantMisiones)++; 
    } else {
        printf("----------------------------------------------------------\n");
        printf("  [X] MISION CANCELADA. Los datos no se guardaron.\n");
        printf("----------------------------------------------------------\n");
        for (int k = 1; k <= 6; k++) {
            strcpy(misiones[idx][k], "");
        }
    }
    
    printf("\nPresione Enter para continuar...");
    getchar(); getchar();
}

// ======================================= mostrar misiones activas
void mostrarMisionesActivas(char misiones[20][7][50], int totalMisiones) {
    printf("\n--- MISIONES ACTIVAS ---\n");
    printf("+------+------------------------------+---------------+-------------+\n");
    printf("| ID   | Tipo de emergencia           | Zona          |   Urgencia  |\n");
    printf("+------+------------------------------+---------------+-------------+\n");
    
    if (totalMisiones == 0) {
        printf("|  --  | No hay misiones activas registradas          |  --         |\n");
    } else {
        for (int j = 1; j <= totalMisiones; j++) {
            printf("| %-4s | %-28s | %-13s | %-11s |\n", 
                   misiones[j][0], misiones[j][1], misiones[j][2], misiones[j][5]);
        }
    }
    
    printf("+------+------------------------------+---------------+-------------+\n");
}