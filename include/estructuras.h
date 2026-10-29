#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

typedef struct {
    char id[10];
    char tipo[30];
    char provincia[30];
    char localidad[30];
    char descripcion[100];
    char urgencia[10];
    char estado[20];
} Mision;

typedef struct {
    char id[10];
    char nombre[30];
    char categoria[30];
    int cantidad;
    char unidad[10];
    char estado[20];
} Insumo;

#endif