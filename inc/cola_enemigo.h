/**
 * @file cola_enemigo.h
 * @author Daniela Soto
 * @brief 
 */
#ifndef COLA_ENEMIGO_H
#define COLA_ENEMIGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enemigo.h"

/**
 * @brief 
 * 
 */
typedef struct _NodoEnemigo{
    Enemigo enemigo;
    struct _NodoEnemigo* siguiente;
} NodoEnemigo;

typedef struct _ColaEnemigo* ColaEnemigo;

/**
 * @brief 
 * 
 */
struct _ColaEnemigo{
    NodoEnemigo* front;
    NodoEnemigo* rear;
    int tamanio;
};

ColaEnemigo cola_enemigo_create();
ColaEnemigo cola_enemigo_make_empty(ColaEnemigo q);
int cola_enemigo_is_empty(ColaEnemigo q);
int cola_enemigo_enqueue(Enemigo e, ColaEnemigo q);
Enemigo cola_enemigo_dequeue(ColaEnemigo q);
Enemigo* cola_enemigo_front(ColaEnemigo q);
int cola_enemigo_size(ColaEnemigo q);
void cola_enemigo_delete(ColaEnemigo q);

#endif