#ifndef COORDINADOR_H
#define COORDINADOR_H
#include "estructuras.h"

void coordinador(char *idUsuario, Mision misiones[], int *cantMisiones, char trabajadoresPorMision[][5][10], int cantTrabajadoresPorMision[], int maximoMisiones, char trabajadores[][3][30], int cantTrabajadores, Insumo stock[], int *totalStock, int *acumuladoDonaciones, int donacionesPorMision[]);

#endif