#include "aventura.h"

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

    Enemigo furtivo = crear_enemigo_tipo1(1, "Furtivo", 30, 5, 30);
    cola_enemigo_enqueue(furtivo, cola);

    combate(personaje, cola, inventario);

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

    Enemigo furtivo2 = crear_enemigo_tipo1(1, "Furtivo", 30, 5, 30);
    Enemigo mastin = crear_enemigo_tipo1(2, "Mastin", 38, 7, 38);

    cola_enemigo_enqueue(furtivo2, cola);
    cola_enemigo_enqueue(mastin, cola);

    combate(personaje, cola, inventario);

    cola_enemigo_delete(cola);

    printf("Sigues por el pasillo. \n");
    printf("¡Encuentras la salida de la catacumba! \n");
    printf("Felicidades :) \n");
}

void zona_abismo(Inventario* inventario, Personaje* personaje){
    printf("Entras al Abismo... \n");
    printf("El suelo es rocoso y humedo. Te resbalas un poco. \n");
    printf("Avanzas por una grieta oscura. \n");
    printf("En una esquina humeda, ¡encuentras una prenda colgada! \n");
    
    Objeto impermeable;
    objeto_inicializar(&impermeable, 2, "impermeable", TIPO_ARMADURA, 5);
    objeto_imprimir(&impermeable);

    char res_imp;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf(" %c", &res_imp);
    while(getchar() != '\n');
    if (res_imp == 's' || res_imp == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &impermeable);
        if (resu_inven == INVENTARIO_OK){
            printf("Impermeable agregado al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("Cruzas la grieta y llegas a una caverna amplia. \n");
    printf("¡Un par de criaturas resguardan el camino! \n");
    printf("Enemigos:\n");
    printf("1. Mastin (38 PV)\n");
    printf("2. Vandalo (45 PV)\n");

    ColaEnemigo cola = cola_enemigo_create();
    if (cola == NULL) {
        printf("Error al crear la cola de enemigos.\n");
        return;
    }

    Enemigo mastin = crear_enemigo_tipo1(2, "Mastin", 38, 7, 38);
    Enemigo vandalo = crear_enemigo_tipo2(3, "Vandalo", 45, 10, 45);

    cola_enemigo_enqueue(mastin, cola);
    cola_enemigo_enqueue(vandalo, cola);

    combate(personaje, cola, inventario);

    char res_exp;
    printf("¿Seguir explorando? (s/n): \n");
    scanf(" %c", &res_exp);
    while (getchar() != '\n');
    if (res_exp != 's' || res_exp != 'S'){
        printf("Decides regresar. \n");
        cola_enemigo_delete(cola);
        return;
    }

    printf("Avanzas mas profundo en la oscuridad. \n");
    printf("¡Encuentras un pequeño maletin en el suelo! \n");

    Objeto adrenalina;
    objeto_inicializar(&adrenalina, 5, "adrenalina", TIPO_POCION, 15);
    objeto_imprimir(&adrenalina);

    char res_adr;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf(" %c", &res_adr);
    while(getchar() != '\n');
    if (res_adr == 's' || res_adr == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &adrenalina);
        if (resu_inven == INVENTARIO_OK){
            printf("Adrenalina agregada al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("¡Has superado los peligros del Abismo y encuentras el ascenso! \n");
    printf("Felicidades :) \n");

    cola_enemigo_delete(cola);
}

void zona_paramo(Inventario* inventario, Personaje* personaje){
    printf("Entras al Paramo... \n");
    printf("Vientos helados y ceniza cubren el paisaje desolado. \n");
    printf("Entre los restos de un campamento abandonado, ¡encuentras una caja fuerte abierta! \n");
    
    Objeto escopeta;
    objeto_inicializar(&escopeta, 3, "escopeta", TIPO_ARMA, 15);
    objeto_imprimir(&escopeta);

    char res_esc;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf(" %c", &res_esc);
    while(getchar() != '\n');
    if (res_esc == 's' || res_esc == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &escopeta);
        if (resu_inven == INVENTARIO_OK){
            printf("Escopeta agregada al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("A pocos metros, colgado de una estaca, ves equipo militar. \n");
    Objeto antidisturbio;
    objeto_inicializar(&antidisturbio, 6, "antidisturbio", TIPO_ARMADURA, 10);
    objeto_imprimir(&antidisturbio);

    char res_ant;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf(" %c", &res_ant);
    while(getchar() != '\n');
    if (res_ant == 's' || res_ant == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &antidisturbio);
        if (resu_inven == INVENTARIO_OK){
            printf("Antidisturbio agregado al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("El camino principal esta bloqueado por una horda final de enemigos. \n");
    printf("Antes de avanzar, revisas una caja metalica abandonada y ¡encuentras una bengala! \n");

    Objeto bengala;
    objeto_inicializar(&bengala, 7, "bengala", TIPO_OTRO, 0);
    objeto_imprimir(&bengala);

    char res_ben;
    printf("¿Deseas recogerlo? (s/n): \n");
    scanf(" %c", &res_ben);
    while(getchar() != '\n');
    if (res_ben == 's' || res_ben == 'S'){
        ResultadoInventario resu_inven = inventario_agregar(inventario, &bengala);
        if (resu_inven == INVENTARIO_OK){
            printf("Bengala agregada al inventario. \n");
        } else {
            printf("El objeto ya esta en el inventario. \n");
        }
    } else {
        printf("Dejas el objeto en el suelo. \n");
    }

    printf("Enemigos:\n");
    printf("1. Furtivo (30 PV)\n");
    printf("2. Mastin (38 PV)\n");
    printf("3. Vandalo (45 PV)\n");

    ColaEnemigo cola = cola_enemigo_create();
    if (cola == NULL) {
        printf("Error al crear la cola de enemigos.\n");
        return;
    }

    Enemigo furtivo = crear_enemigo_tipo1(1, "Furtivo", 30, 15, 30);
    Enemigo mastin = crear_enemigo_tipo2(2, "Mastin", 38, 7, 38);
    Enemigo vandalo = crear_enemigo_tipo3(3, "Vandalo", 45, 10, 45);

    cola_enemigo_enqueue(furtivo, cola);
    cola_enemigo_enqueue(mastin, cola);
    cola_enemigo_enqueue(vandalo, cola);

    combate(personaje, cola, inventario);

    printf("¡Has derrotado a los jefes y conquistado el Paramo! \n");
    printf("Felicidades :) \n");

    cola_enemigo_delete(cola);
}

void iniciar_zona(Inventario* inventario, Personaje* personaje){
    if (inventario == NULL || personaje == NULL){
        printf("Personaje o inventario no inicializados. \n");
        return;
    }

    int opcion_zona;

    printf("\n========================================\n");
    printf("         ZONA DE EXPLORACION            \n");
    printf("========================================\n");
    printf("1.- Catacumba (dificultad baja)");
    printf("2.- Abismo (dificultad media)");
    printf("3.- Paramo (dificultad alta)");
    printf("4.- Salir de la exploración\n");
    printf("Seleccione una zona: \n");

    if (scanf("%d", &opcion_zona) != 1) {
        printf("Error. Solo debe ingresar un numero.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    switch (opcion_zona){
    case 1:
        zona_catacumba(inventario, personaje);
        break;
    case 2:
        zona_abismo(inventario, personaje);
        break;
    case 3:
        zona_paramo(inventario, personaje);
        break;
    case 4:
        printf("Volviendo al menu principal. \n");
        //Volver al main
        break;
    default:
        printf("Opcion invalida. \n");
        break;
    }

}