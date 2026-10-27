#include "enemigo.h"
#include <stdio.h>
#include <string.h>

Enemigo crear_enemigo_tipo1(int id, const char* nombre, int pv, int ataque){
    Enemigo  e;

    e.id = 1;
    strcpy(e.nombre, "tipo1");
    e.pv = 30;
    e.ataque = 10;
    
    return e;
}
Enemigo crear_enemigo_tipo2(int id, const char* nombre, int pv, int ataque){
    Enemigo  e;

    e.id = 2;
    strcpy(e.nombre, "tipo2");
    e.pv = 40;
    e.ataque = 20;
    
    return e;
}

Enemigo crear_enemigo_tipo3(int id, const char* nombre, int pv, int ataque){
    Enemigo  e;

    e.id = 3;
    strcpy(e.nombre, "tipo3");
    e.pv = 50;
    e.ataque = 30;
    
    return e;
}

void mostrar_enemigo(Enemigo e){
    printf("Enemigo: \n");
    printf("ID: %d | Nombre: %s | Pv: %d | Ataque: %d | \n", e.id, e.nombre, e.pv, e.ataque);
    return;
}