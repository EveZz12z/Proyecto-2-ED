#ifndef AVENTURA_H
#define AVENTURA_H

#include "inventario.h"
#include "personaje.h"
#include "cola_enemigo.h"
#include "objeto.h"
#include "enemigo.h"
#include "combate.h"
#include "cola_enemigo.h"

void zona_catacumba(Inventario* inventario, Personaje* personaje);
void zona_abismo(Inventario* inventario, Personaje* personaje);
void zona_paramo(Inventario* inventario, Personaje* personaje);
void mostrar_zonas();
void iniciar_zona();

#endif