#ifndef ADMIN_H
#define ADMIN_H

#define MAX_USUARIOS 100
#define MAX_ADMINISTRADORES 20
#define MAX_TRABAJADORES 40

void administrador(char *idAdmin, char idUsuario[][10], char nombreUsuario[][50],
                   char contrasenaUsuario[][50], char rolUsuario[][20], int *cantUsuarios,
                   char idAdministrador[][10], char nombreAdministrador[][30],
                   char apellidoAdministrador[][30], int *cantAdministradores,
                   char idTrabajador[][10], char nombreTrabajador[][30],
                   char apellidoTrabajador[][30], int *cantTrabajadores,
                   char trabajadorAsignado[][10], char misionAsignada[][10],
                   int *cantAsignaciones, char idMision[][10], int cantMisiones,
                   int cantidadTrabajadoresPorMision[]);

int cargarUsuarios(char idUsuario[][10], char nombreUsuario[][50],
                   char contrasenaUsuario[][50], char rolUsuario[][20],
                   int *cantUsuarios, char idAdministrador[][10],
                   char nombreAdministrador[][30], char apellidoAdministrador[][30],
                   int *cantAdministradores, char idTrabajador[][10],
                   char nombreTrabajador[][30], char apellidoTrabajador[][30],
                   int *cantTrabajadores);

int guardarUsuarios(char idUsuario[][10], char nombreUsuario[][50],
                    char contrasenaUsuario[][50], char rolUsuario[][20], int cantUsuarios,
                    char idAdministrador[][10], char nombreAdministrador[][30],
                    char apellidoAdministrador[][30], int cantAdministradores,
                    char idTrabajador[][10], char nombreTrabajador[][30],
                    char apellidoTrabajador[][30], int cantTrabajadores);

#endif
