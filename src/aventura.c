#include "aventura.h"

void mostrar_zonas(){
    printf("Zonas disponibles: \n”");
    printf("1.- Catacumba (dificultad baja)");
    printf("2.- Abismo (dificultad media)");
    printf("3.- Paramo (dificultad alta)");

}

void zona_catacumba(Inventario* inventario, Personaje* personaje){
    printf("Entras a la Catacumba... \n");
    printf("Caminas entre las paredes de pierda. No encuentras nada \n");
    printf("Entras en un pasillo oscuro. No ves nada \n");
    printf("Empiezas a tocar las paredes. ¡Encuentras un objeto! \n");
    
    Objeto antiseptico;
    objeto_inicializar(&antiseptico, 1, "antiseptico",  TIPO_POCION, 7);
    objeto_imprimir(&antiseptico);

    char res_antiseptico;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf("%c", &res_antiseptico);
    while(getchar() != '\n');
    if (res_antiseptico == 's' || res_antiseptico == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &antiseptico);
        if (resu_inven == INVENTARIO_OK){
            printf("Antiseptico agregado al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("Termina el pasillo oscuro. Entras a un cuarto \n");
    printf("¡Hay un enemigo esperandote en el cuarto! \n");
    printf("Enemigos:\n");
    printf("1. Furtivo (30 PV)\n");
    printf("Siguiente enemigo: Furtivo\n");

    ColaEnemigo cola = cola_enemigo_create();
    if (cola == NULL) {
        printf("Error al crear la cola de enemigos.\n");
        return;
    }

    Enemigo furtivo = crear_enemigo_tipo1(1, "Furtivo", 30, 5);
    cola_enemigo_enqueue(furtivo, cola);

    combate(personaje, &furtivo, cola, inventario);

    char res_exp;
    printf("¿Seguir explorando? (s/n): \n");
    scanf("%c", &res_exp);
    while (getchar() != '\n');
    if (res_exp != 's' || res_exp != 'S'){
        printf("Decides regresar. \n");
        return;
    }
    
    printf("Entras a otro cuarto. \n");
    printf("¡Encuentras un objeto en el suelo! \n");

    Objeto machete;
    objeto_inicializar(&machete, 4, "machete",  TIPO_ARMA, 10);
    objeto_imprimir(&machete);

    char res_mache;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf("%c", &res_mache);
    while(getchar() != '\n');
    if (res_mache == 's' || res_mache == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &machete);
        if (resu_inven == INVENTARIO_OK){
            printf("Machete agregado al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("Avanzas con cautela. Te encuentras en un pasillo estrecho \n");
    printf("Un grupo de enemigos bloquea el paso. \n");

    Enemigo furtivo2 = crear_enemigo_tipo1(1, "Furtivo", 30, 5);
    Enemigo mastin = crear_enemigo_tipo1(2, "Mastin", 38, 7);

    cola_enemigo_enqueue(furtivo2, cola);
    cola_enemigo_enqueue(mastin, cola);

    combate(personaje, &furtivo2, cola, inventario);

    cola_enemigo_delete(cola);

    printf("Sigues por el pasillo. \n");
    printf("¡Encuentras la salida de la catacumba! \n");
    printf("Felicidades :) \n");
}