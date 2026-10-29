// Definir módulos de trabajador
#ifndef TRABAJADOR_H
#define TRABAJADOR_H

// Funciones
void trabajador(char *trabajadorBuscado, char idTrabajador[][10], char nombreTrabajador[][30], char apellidoTrabajador[][30], char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char descripcionMision[][100], char prioridadMision[][10], char estadoMision[][20], int cantMisiones, int cantTrabajadoresPorMision[], char misionAsignada[][10], char trabajadorAsignado[][10], int cantTrabajadores, int cantAsignaciones);

int buscarMisionTrabajador(char *trabajadorBuscado, char idTrabajador[][10], int cantAsignaciones, int cantidadMisiones, char trabajadorAsignado[][10], char misionAsignada[][10], char idMision[][10], int cantTrabajadores, int *posTrabajadorAsignado);

void menuTrabajador(char idMision[][10], int posMisionAsig, char idTrabajador[][10], int posTrabajadorAsig, char tipoMision[][30], char provMision[][30], char localidadMision[][30], char descripMision[][100], char prioriMision[][10], char estadoMision[][20], char nomTrabajador[][30], char apeTrabajador[][30], int cantMisiones);

void verMision(char idMision[][10], int posMisionAsig, char tipoMision[][30], char provMision[][30], char localidadMision[][30], char descripMision[][100], char prioriMision[][10], char estadoMision[][20], int cantMisiones);

void verEstado(char idMision[][10], int posMisionAsig, char estadoMision[][20], int cantMisiones);

void cambiarEstado(char idMision[][10], int posMisionAsig, char estadoMision[][20], int cantMisiones);

#endif