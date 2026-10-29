#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Enemigo{
    int id;
    char nombre[30];
    int pv;
    int ataque;
    int vida_max
};

typedef struct _Enemigo Enemigo;

typedef enum{
    ENEMIGO_TIPO1,
    ENEMIGO_TIPO2,
    ENEMIGO_TIPO3,
} TipoEnemigo;

Enemigo crear_enemigo_tipo1(int id, const char* nombre, int pv, int ataque, int vida_max);
Enemigo crear_enemigo_tipo2(int id, const char* nombre, int pv, int ataque, int vida_max);
Enemigo crear_enemigo_tipo3(int id, const char* nombre, int pv, int ataque, int vida_max);
void mostrar_enemigo(Enemigo e);

#endif