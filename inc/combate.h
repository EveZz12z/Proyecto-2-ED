#ifndef COMBATE_H
#define COMBATE_H

#include "cola_enemigo.h"
#include "enemigo.h"
#include "inventario.h"
#include "objeto.h"
#include "personaje.h"
#include "uso_objeto.h"

void ver_inventario(const Inventario* inventario);
int ataque_jugador(Enemigo* enemigo, Personaje* personaje, ColaEnemigo* cola);
void ataque_enemigo(Enemigo* enemigo, Personaje* personaje);
void iniciar_combate(ColaEnemigo cola_enemigos, Inventario* inventario, Personaje* personaje);
void estado_combate(Personaje* personaje, Enemigo* enemigo, ColaEnemigo* cola);
void combate(Personaje* personaje, ColaEnemigo cola, Inventario* inventario);

#endif