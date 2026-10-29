#include "enemigo.h"
#include <stdio.h>
#include <string.h>

Enemigo crear_enemigo_tipo1(int id, const char* nombre, int pv, int ataque, int vida_max){
    Enemigo  e;

    e.id = id;
    snprintf(e.nombre, sizeof(e.nombre), "%s", nombre);
    e.pv = pv;
    e.ataque = ataque;
    e.vida_max = vida_max;
    
    return e;
}
Enemigo crear_enemigo_tipo2(int id, const char* nombre, int pv, int ataque, int vida_max){
    Enemigo  e;

    e.id = id;
    snprintf(e.nombre, sizeof(e.nombre), "%s", nombre);
    e.pv = pv;
    e.ataque = ataque;
    e.vida_max = vida_max;
    
    return e;
}

Enemigo crear_enemigo_tipo3(int id, const char* nombre, int pv, int ataque, int vida_max){
    Enemigo  e;

    e.id = id;
    snprintf(e.nombre, sizeof(e.nombre), "%s", nombre);
    e.pv = pv;
    e.ataque = ataque;
    e.vida_max = vida_max;
    
    return e;
}

void mostrar_enemigo(Enemigo e){
    printf("Enemigo: \n");
    printf("ID: %d | Nombre: %s | Pv: %d | Ataque: %d | \n", e.id, e.nombre, e.pv, e.ataque);
    return;
}