#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/coordinador.h"

// con esta funcion auxilia para guardar la misión en el archivo de texto
void guardarMisionDisco(Mision m) {
    FILE *archivo = fopen("data/misiones.txt", "a");
    if (archivo == NULL) {
        printf("[ERROR!] No se pudo abrir el archivo para guardar la mision.\n");
        return;
    }
    
    fprintf(archivo, "%s;%s;%s;%s;%s;%s;%s\n", 
            m.id, m.tipo, m.provincia, m.localidad, m.descripcion, m.urgencia, m.estado);
    fclose(archivo);
}

void crearMision(Mision misiones[], int *cantMisiones, int maximoMisiones, int cantTrabajadoresPorMision[]) {
    if (*cantMisiones + 1 >= maximoMisiones) {
        printf("[ERROR!] Se alcanzo el maximo de misiones permitidas.\n");
        return;
    }
    
    int i = *cantMisiones + 1;
    if (i < 10) {
        sprintf(misiones[i].id, "M0%d", i);
    } else {
        sprintf(misiones[i].id, "M%d", i);
    }
    
    printf("--- CREAR NUEVA MISION ---\n");
    printf("ID asignado: %s\n", misiones[i].id);
    printf("Tipo de emergencia: ");
    scanf(" %[^\n]", misiones[i].tipo);
    printf("Zona / Provincia: ");
    scanf(" %[^\n]", misiones[i].provincia);
    printf("Localidad / Area: ");
    scanf(" %[^\n]", misiones[i].localidad);
    printf("Descripcion: ");
    scanf(" %[^\n]", misiones[i].descripcion);
    
    int opUrgencia;
    do {
        printf("Nivel de urgencia [1] BAJA   [2] MEDIA   [3] ALTA: ");
        scanf("%d", &opUrgencia);
        if (opUrgencia == 1) strcpy(misiones[i].urgencia, "BAJA");
        else if (opUrgencia == 2) strcpy(misiones[i].urgencia, "MEDIA");
        else if (opUrgencia == 3) strcpy(misiones[i].urgencia, "ALTA");
        else printf("[ERROR!] Opcion invalida.\n");
    } while (opUrgencia < 1 || opUrgencia > 3);
    
    strcpy(misiones[i].estado, "En camino");
    cantTrabajadoresPorMision[i] = 0;
    
    // guardadamos la mision en el archivo txt
    guardarMisionDisco(misiones[i]);

    (*cantMisiones)++;
    printf("[OK] Mision registrada y guardada en archivo con ID: %s\n", misiones[i].id);
}

void coordinador(char *idUsuario, Mision misiones[], int *cantMisiones, char trabajadoresPorMision[][5][10], int cantTrabajadoresPorMision[], int maximoMisiones, char trabajadores[][3][30], int cantTrabajadores, Insumo stock[], int *totalStock, int *acumuladoDonaciones, int donacionesPorMision[]) {
    int opcion;
    do {
        printf("\n ================ PANEL DE COORDINADOR ================ \n");
        printf("ID: %s\n", idUsuario);
        printf("Fondos disponibles: $%d\n", *acumuladoDonaciones);
        printf("[1] Crear mision\n");
        printf("[2] Misiones activas\n");
        printf("[3] Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                crearMision(misiones, cantMisiones, maximoMisiones, cantTrabajadoresPorMision);
                break;
            case 2:
                for(int j = 1; j <= *cantMisiones; j++) {
                    if(strcmp(misiones[j].estado, "Controlada") != 0) {
                        printf("%s | %s | %s - %s | Urgencia: %s | Estado: %s | Fondos: $%d\n", 
                            misiones[j].id, misiones[j].tipo, misiones[j].provincia, misiones[j].localidad, 
                            misiones[j].urgencia, misiones[j].estado, donacionesPorMision[j]);
                    }
                }
                break;
            case 3:
                printf("Saliendo del panel de coordinador...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opcion != 3);
}