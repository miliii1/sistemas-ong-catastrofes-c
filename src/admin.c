#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/admin.h"


static int buscarUsuario(char ids[][10], int cantidad, const char *id) {
    int i;
    for (i = 0; i < cantidad; i++) if (strcmp(ids[i], id) == 0) return i;
    return -1;
}

int guardarUsuarios(char idUsuario[][10], char nombreUsuario[][50],
                    char contrasenaUsuario[][50], char rolUsuario[][20], int cantUsuarios,
                    char idAdministrador[][10], char nombreAdministrador[][30],
                    char apellidoAdministrador[][30], int cantAdministradores,
                    char idTrabajador[][10], char nombreTrabajador[][30],
                    char apellidoTrabajador[][30], int cantTrabajadores) {
    FILE *f = fopen("data/usuarios.txt", "w");
    int i;
    if (!f) {
        printf("[ERROR] No se pudo abrir data/usuarios.txt para guardar.\n");
        return 0;
    }
    for (i = 0; i < cantUsuarios; i++) {
        const char *nombre = "", *apellido = "";
        int p;
        if (strcmp(rolUsuario[i], "ADMINISTRADOR") == 0) {
            p = buscarUsuario(idAdministrador, cantAdministradores, idUsuario[i]);
            if (p >= 0) { nombre = nombreAdministrador[p]; apellido = apellidoAdministrador[p]; }
        } else {
            p = buscarUsuario(idTrabajador, cantTrabajadores, idUsuario[i]);
            if (p >= 0) { nombre = nombreTrabajador[p]; apellido = apellidoTrabajador[p]; }
        }
        fprintf(f, "%s;%s;%s;%s;%s;%s\n", idUsuario[i], nombreUsuario[i],
                contrasenaUsuario[i], rolUsuario[i], nombre, apellido);
    }
    fclose(f);
    return 1;
}

int cargarUsuarios(char idUsuario[][10], char nombreUsuario[][50],
                   char contrasenaUsuario[][50], char rolUsuario[][20],
                   int *cantUsuarios, char idAdministrador[][10],
                   char nombreAdministrador[][30], char apellidoAdministrador[][30],
                   int *cantAdministradores, char idTrabajador[][10],
                   char nombreTrabajador[][30], char apellidoTrabajador[][30],
                   int *cantTrabajadores) {
    FILE *f = fopen("data/usuarios.txt", "r");
    char linea[256], nombre[30], apellido[30];
    *cantUsuarios = *cantAdministradores = *cantTrabajadores = 0;
    if (!f) return 0;
    while (fgets(linea, sizeof(linea), f) && *cantUsuarios < MAX_USUARIOS) {
        char id[10], usuario[50], clave[50], rol[20];
        if (sscanf(linea, "%9[^;];%49[^;];%49[^;];%19[^;];%29[^;];%29[^\n]",
                   id, usuario, clave, rol, nombre, apellido) == 6) {
            int n = *cantUsuarios;
            strcpy(idUsuario[n], id); strcpy(nombreUsuario[n], usuario);
            strcpy(contrasenaUsuario[n], clave); strcpy(rolUsuario[n], rol);
            if (strcmp(rol, "ADMINISTRADOR") == 0 && *cantAdministradores < MAX_ADMINISTRADORES) {
                int a = (*cantAdministradores)++;
                strcpy(idAdministrador[a], id); strcpy(nombreAdministrador[a], nombre);
                strcpy(apellidoAdministrador[a], apellido);
            } else if (strcmp(rol, "TRABAJADOR") == 0 && *cantTrabajadores < MAX_TRABAJADORES) {
                int t = (*cantTrabajadores)++;
                strcpy(idTrabajador[t], id); strcpy(nombreTrabajador[t], nombre);
                strcpy(apellidoTrabajador[t], apellido);
            }
            (*cantUsuarios)++;
        }
    }
    fclose(f);
    return 1;
}

static void agregarUsuario(char idUsuario[][10], char nombreUsuario[][50],
    char contrasenaUsuario[][50], char rolUsuario[][20], int *cantUsuarios,
    char idAdministrador[][10], char nombreAdministrador[][30], char apellidoAdministrador[][30],
    int *cantAdministradores, char idTrabajador[][10], char nombreTrabajador[][30],
    char apellidoTrabajador[][30], int *cantTrabajadores) {
    char rol[10], clave2[50];
    int n = *cantUsuarios;
    if (n >= MAX_USUARIOS) { printf("[ERROR] Se alcanzo el maximo de usuarios.\n"); return; }
    do {
        printf("\n[A] Administrador\n[T] Trabajador\n[S] Volver\nSeleccione el rol: ");
        scanf(" %9s", rol);
        rol[0] = (char)toupper((unsigned char)rol[0]);
    } while (strcmp(rol,"A") && strcmp(rol,"T") && strcmp(rol,"S"));
    if (strcmp(rol,"S") == 0) return;
    if (strcmp(rol,"A") == 0 && *cantAdministradores >= MAX_ADMINISTRADORES) {
        printf("[ERROR] Se alcanzo el maximo de administradores.\n"); return;
    }
    if (strcmp(rol,"T") == 0 && *cantTrabajadores >= MAX_TRABAJADORES) {
        printf("[ERROR] Se alcanzo el maximo de trabajadores.\n"); return;
    }
    printf("Nombre de usuario (sin espacios): "); scanf(" %49s", nombreUsuario[n]);
    {
        int k, repetido = 0;
        for (k = 0; k < *cantUsuarios; k++)
            if (strcmp(nombreUsuario[k], nombreUsuario[n]) == 0) repetido = 1;
        if (repetido) {
        printf("[ERROR] Ese nombre de usuario ya existe.\n"); return;
    }
    }
    printf("Contrasena: "); scanf(" %49s", contrasenaUsuario[n]);
    printf("Confirme la contrasena: "); scanf(" %49s", clave2);
    if (strcmp(clave2, contrasenaUsuario[n]) != 0) {
        printf("[ERROR] Las contrasenas no coinciden. No se registro el usuario.\n"); return;
    }
    if (strcmp(rol,"A") == 0) {
        int a = *cantAdministradores;
        printf("Nombre del administrador: "); scanf(" %29[^\n]", nombreAdministrador[a]);
        printf("Apellido del administrador: "); scanf(" %29[^\n]", apellidoAdministrador[a]);
        {
            int numero = a + 1;
            snprintf(idAdministrador[a], 10, "A%02d", numero);
            while (buscarUsuario(idUsuario, *cantUsuarios, idAdministrador[a]) >= 0) {
                numero++;
                snprintf(idAdministrador[a], 10, "A%02d", numero);
            }
        }
        strcpy(idUsuario[n], idAdministrador[a]); strcpy(rolUsuario[n], "ADMINISTRADOR");
        (*cantAdministradores)++;
    } else {
        int t = *cantTrabajadores;
        printf("Nombre del trabajador: "); scanf(" %29[^\n]", nombreTrabajador[t]);
        printf("Apellido del trabajador: "); scanf(" %29[^\n]", apellidoTrabajador[t]);
        {
            int numero = t + 1;
            snprintf(idTrabajador[t], 10, "T%02d", numero);
            while (buscarUsuario(idUsuario, *cantUsuarios, idTrabajador[t]) >= 0) {
                numero++;
                snprintf(idTrabajador[t], 10, "T%02d", numero);
            }
        }
        strcpy(idUsuario[n], idTrabajador[t]); strcpy(rolUsuario[n], "TRABAJADOR");
        (*cantTrabajadores)++;
    }
    (*cantUsuarios)++;
    printf("[OK] Usuario registrado correctamente.\n");
}

static void eliminarUsuario(char idUsuario[][10], char nombreUsuario[][50],
    char contrasenaUsuario[][50], char rolUsuario[][20], int *cantUsuarios,
    char idAdministrador[][10], char nombreAdministrador[][30], char apellidoAdministrador[][30],
    int *cantAdministradores, char idTrabajador[][10], char nombreTrabajador[][30],
    char apellidoTrabajador[][30], int *cantTrabajadores,
    char trabajadorAsignado[][10], char misionAsignada[][10], int *cantAsignaciones,
    char idMision[][10], int cantMisiones, int cantidadTrabajadoresPorMision[]) {
    char id[10], confirma[10];
    int p, i, j;
    printf("ID del usuario a eliminar: "); scanf(" %9s", id);
    p = buscarUsuario(idUsuario, *cantUsuarios, id);
    if (p < 0) { printf("[ERROR] No existe un usuario con ese ID.\n"); return; }
    printf("Se eliminara %s (%s). Confirmar (S/N): ", nombreUsuario[p], rolUsuario[p]);
    scanf(" %9s", confirma);
    if (toupper((unsigned char)confirma[0]) != 'S') { printf("Operacion cancelada.\n"); return; }

    if (strcmp(rolUsuario[p], "ADMINISTRADOR") == 0) {
        int a;
        if (*cantAdministradores <= 1) {
            printf("[ERROR] No se puede eliminar el ultimo administrador.\\n");
            return;
        }
        a = buscarUsuario(idAdministrador, *cantAdministradores, id);
        if (a >= 0) {
            for (i = a; i < *cantAdministradores - 1; i++) {
                strcpy(idAdministrador[i], idAdministrador[i+1]);
                strcpy(nombreAdministrador[i], nombreAdministrador[i+1]);
                strcpy(apellidoAdministrador[i], apellidoAdministrador[i+1]);
            }
            (*cantAdministradores)--;
        }
    } else {
        int t = buscarUsuario(idTrabajador, *cantTrabajadores, id);
        if (t >= 0) {
            for (i = t; i < *cantTrabajadores - 1; i++) {
                strcpy(idTrabajador[i], idTrabajador[i+1]);
                strcpy(nombreTrabajador[i], nombreTrabajador[i+1]);
                strcpy(apellidoTrabajador[i], apellidoTrabajador[i+1]);
            }
            (*cantTrabajadores)--;
        }
        for (i = 0; i < *cantAsignaciones; ) {
            if (strcmp(trabajadorAsignado[i], id) == 0) {
                int m;
                for (m = 0; m < cantMisiones; m++) {
                    if (strcmp(idMision[m], misionAsignada[i]) == 0 &&
                        cantidadTrabajadoresPorMision[m] > 0) {
                        cantidadTrabajadoresPorMision[m]--;
                        break;
                    }
                }
                for (j = i; j < *cantAsignaciones - 1; j++) {
                    strcpy(trabajadorAsignado[j], trabajadorAsignado[j+1]);
                    strcpy(misionAsignada[j], misionAsignada[j+1]);
                }
                (*cantAsignaciones)--;
            } else i++;
        }
    }
    for (i = p; i < *cantUsuarios - 1; i++) {
        strcpy(idUsuario[i], idUsuario[i+1]); strcpy(nombreUsuario[i], nombreUsuario[i+1]);
        strcpy(contrasenaUsuario[i], contrasenaUsuario[i+1]); strcpy(rolUsuario[i], rolUsuario[i+1]);
    }
    (*cantUsuarios)--;
    printf("[OK] Usuario eliminado.\n");
}

void administrador(char *idAdmin, char idUsuario[][10], char nombreUsuario[][50],
    char contrasenaUsuario[][50], char rolUsuario[][20], int *cantUsuarios,
    char idAdministrador[][10], char nombreAdministrador[][30], char apellidoAdministrador[][30],
    int *cantAdministradores, char idTrabajador[][10], char nombreTrabajador[][30],
    char apellidoTrabajador[][30], int *cantTrabajadores,
    char trabajadorAsignado[][10], char misionAsignada[][10], int *cantAsignaciones,
    char idMision[][10], int cantMisiones, int cantidadTrabajadoresPorMision[]) {
    int op;
    do {
        printf("\n+----------------------------------------------------------+\n");
        printf("|                 PANEL DE ADMINISTRADOR                   |\n");
        printf("+----------------------------------------------------------+\n");
        printf("ID: %s\n", idAdmin);
        printf("[1] Agregar usuario\n[2] Eliminar usuario\n[3] Listar usuarios\n[4] Cerrar sesion\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &op) != 1) { int c; while ((c=getchar())!='\n' && c!=EOF) {} op=0; }
        switch (op) {
            case 1:
                agregarUsuario(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,cantUsuarios,
                    idAdministrador,nombreAdministrador,apellidoAdministrador,cantAdministradores,
                    idTrabajador,nombreTrabajador,apellidoTrabajador,cantTrabajadores);
                guardarUsuarios(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,*cantUsuarios,
                    idAdministrador,nombreAdministrador,apellidoAdministrador,*cantAdministradores,
                    idTrabajador,nombreTrabajador,apellidoTrabajador,*cantTrabajadores);
                break;
            case 2:
                eliminarUsuario(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,cantUsuarios,
                    idAdministrador,nombreAdministrador,apellidoAdministrador,cantAdministradores,
                    idTrabajador,nombreTrabajador,apellidoTrabajador,cantTrabajadores,
                    trabajadorAsignado,misionAsignada,cantAsignaciones,
                    idMision,cantMisiones,cantidadTrabajadoresPorMision);
                guardarUsuarios(idUsuario,nombreUsuario,contrasenaUsuario,rolUsuario,*cantUsuarios,
                    idAdministrador,nombreAdministrador,apellidoAdministrador,*cantAdministradores,
                    idTrabajador,nombreTrabajador,apellidoTrabajador,*cantTrabajadores);
                break;
            case 3:
                printf("\n%-8s %-20s %-18s %-25s\n","ID","USUARIO","ROL","NOMBRE Y APELLIDO");
                for (int i=0;i<*cantUsuarios;i++) {
                    const char *nombre="", *apellido="";
                    int x;
                    if (!strcmp(rolUsuario[i],"ADMINISTRADOR")) {
                        x=buscarUsuario(idAdministrador,*cantAdministradores,idUsuario[i]);
                        if(x>=0){nombre=nombreAdministrador[x];apellido=apellidoAdministrador[x];}
                    } else {
                        x=buscarUsuario(idTrabajador,*cantTrabajadores,idUsuario[i]);
                        if(x>=0){nombre=nombreTrabajador[x];apellido=apellidoTrabajador[x];}
                    }
                    printf("%-8s %-20s %-18s %s %s\n",idUsuario[i],nombreUsuario[i],rolUsuario[i],nombre,apellido);
                }
                break;
            case 4: printf("Sesion cerrada correctamente.\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (op != 4);
}
