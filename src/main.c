#include <stdio.h>
#include <string.h>
#include "../include/estructuras.h"
#include "../include/coordinador.h"
#include "../include/finanzas.h"

// esto en una prueba se puede borrar 

int cargarMisionesDisco(Mision misiones[]) {
    FILE *archivo = fopen("data/misiones.txt", "r");
    
    if (archivo == NULL) {
   
        return 0; 
    }

    int cant = 0;
  
    while (fscanf(archivo, " %[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", 
                  misiones[cant + 1].id, 
                  misiones[cant + 1].tipo, 
                  misiones[cant + 1].provincia, 
                  misiones[cant + 1].localidad, 
                  misiones[cant + 1].descripcion, 
                  misiones[cant + 1].urgencia, 
                  misiones[cant + 1].estado) == 7) {
        cant++;
    }

    fclose(archivo);
    return cant; 
}

int main() {

Mision misiones[20];
int cantMisiones = 0;


cantMisiones = cargarMisionesDisco(misiones);
printf("Se cargaron %d misiones desde el archivo.\n", cantMisiones);

    char trabajadoresPorMision[20][5][10];
    int cantTrabajadoresPorMision[20] = {0};
    char trabajadores[40][3][30];
    int cantTrabajadores = 0;
    Insumo stock[10];
    int totalStock = 0;
    int acumuladoDonaciones = 10000; 
    int donacionesPorMision[21] = {0};

    
    cantMisiones = 1;
    strcpy(misiones[1].id, "M01");
    strcpy(misiones[1].tipo, "Inundacion");
    strcpy(misiones[1].provincia, "Buenos Aires");
    strcpy(misiones[1].localidad, "La Matanza");
    strcpy(misiones[1].descripcion, "Asistencia a familias");
    strcpy(misiones[1].urgencia, "ALTA");
    strcpy(misiones[1].estado, "En camino");

    int opcion;
    do {
        printf("\n========================================\n");
        printf("    PRUEBA AISLADA - MODULOS C y F\n");
        printf("========================================\n");
        printf("[1] Entrar al panel de Coordinador\n");
        printf("[2] Entrar al panel de Finanzas\n");
        printf("[3] Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                coordinador("C01", misiones, &cantMisiones, trabajadoresPorMision, cantTrabajadoresPorMision, 20, trabajadores, cantTrabajadores, stock, &totalStock, &acumuladoDonaciones, donacionesPorMision);
                break;
            case 2:
                finanzas("F01", &acumuladoDonaciones, misiones, cantMisiones, donacionesPorMision);
                break;
            case 3:
                printf("Saliendo del programa de prueba...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while(opcion != 3);

    
    return 0;
}