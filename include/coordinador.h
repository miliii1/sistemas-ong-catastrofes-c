#ifndef COORDINADOR_H
#define COORDINADOR_H

void coordinador(char *idCoordinador, char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char descripcionMision[][100], char prioridadMision[][10], char estadoMision[][20], int *cantidadMisiones, char idTrabajador[][10], char nombreTrabajador[][30], char apellidoTrabajador[][30], int cantidadTrabajadores, char misionAsignada[][10], char trabajadorAsignado[][10], int *cantidadAsignaciones, int cantidadTrabajadoresPorMision[], int maximoMisiones, int maximoTrabajadoresPorMision, int maximoAsignaciones, char stockId[][10], char stockNombre[][30], char stockCategoria[][30], int stockCantidad[], char stockUnidad[][10], char stockEstado[][20], int *totalStock, int *acumuladoDonaciones);

void crearMision(char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char descripcionMision[][100], char prioridadMision[][10], char estadoMision[][20], int *cantidadMisiones, int maximoMisiones, int cantidadTrabajadoresPorMision[]);

void mostrarMisionesActivas(char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char localidadMision[][30], char prioridadMision[][10], char estadoMision[][20], int cantidadMisiones);

void asignarTrabajadores(char idMision[][10], char tipoMision[][30], char provinciaMision[][30], char prioridadMision[][10], char estadoMision[][20], int cantidadMisiones, char idTrabajador[][10], char nombreTrabajador[][30], char apellidoTrabajador[][30], int cantidadTrabajadores, char misionAsignada[][10], char trabajadorAsignado[][10], int *cantidadAsignaciones, int cantidadTrabajadoresPorMision[], int maximoTrabajadoresPorMision, int maximoAsignaciones);

void gestionarStock(char stockId[][10], char stockNombre[][30], char stockCategoria[][30], int stockCantidad[], char stockUnidad[][10], char stockEstado[][20], int *totalStock, int *acumuladoDonaciones);

#endif
