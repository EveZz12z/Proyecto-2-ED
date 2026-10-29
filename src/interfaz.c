#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaz.h"
#include "personaje.h"
#include "inventario.h"
#include "uso_objeto.h"
#include "guardado.h"
#include "aventura.h"
#include "historial.h"

#define LARGO_RUTA 256

/**
 * @brief Descarta lo que quede en la linea de entrada (hasta '\n' o EOF).
 */
static void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Solicita un numero entero al usuario de forma segura.
 *
 * @param mensaje Texto a mostrar antes de leer.
 * @param valor Donde se guarda el numero leido.
 * @return 1 si se leyo un numero, 0 si la entrada se cerro (EOF, Ctrl+D).
 */
static int leer_entero(const char* mensaje, int* valor) {
    int leidos;
    do {
        printf("%s", mensaje);
        leidos = scanf("%d", valor);
        if (leidos == EOF) {
            return 0;
        }
        limpiar_buffer();
        if (leidos != 1) {
            printf("Error: Entrada inválida. Por favor, ingresa un número.\n");
        }
    } while (leidos != 1);
    return 1;
}

/**
 * @brief Solicita una cadena sin espacios al usuario (para guardados y nombres).
 *        Lee como maximo limite - 1 caracteres, asi que nunca desborda el buffer.
 *
 * @param mensaje Texto a mostrar antes de leer.
 * @param buffer Arreglo donde se guarda la cadena.
 * @param limite Tamanio total del buffer (incluye el '\0').
 * @return 1 si se leyo una cadena, 0 si la entrada se cerro (EOF, Ctrl+D).
 */
static int leer_cadena(const char* mensaje, char* buffer, int limite) {
    char formato[16];

    printf("%s", mensaje);
    // Arma el formato "%<limite-1>s" para que scanf no escriba mas alla del arreglo
    snprintf(formato, sizeof(formato), "%%%ds", limite - 1);
    if (scanf(formato, buffer) != 1) {
        return 0;
    }
    limpiar_buffer();
    return 1;
}

/* ========================================================================== */
/*                              LÓGICA DEL MENÚ                               */
/* ========================================================================== */

/**
 * @brief Menu inicial: crear personaje nuevo o cargar partida.
 * @return Personaje creado/cargado, o NULL si la entrada se cerro.
 */
static Personaje* menu_creacion_personaje(Inventario* inventario) {
    Personaje* p = NULL;
    int opcion;
    char nombre[LARGO_NOMBRE_PERSONAJE];
    char ruta[LARGO_RUTA];
    ResultadoGuardado res;

    printf("=== BIENVENIDO AL RPG ===\n");
    printf("1. Nuevo Personaje\n");
    printf("2. Cargar Partida\n");
    
    do {
        if (!leer_entero("Elige una opción (1-2): ", &opcion)) {
            return NULL;
        }

        if (opcion == 1) {
            if (!leer_cadena("Ingresa el nombre de tu personaje (sin espacios): ",
                             nombre, LARGO_NOMBRE_PERSONAJE)) {
                return NULL;
            }
            p = crear_personaje(nombre, 100, 15, 5); // Valores base iniciales
            if (p != NULL) {
                printf("¡Personaje %s creado con éxito!\n", p->nombre);
            }
        } else if (opcion == 2) {
            if (!leer_cadena("Ingresa el nombre del archivo a cargar (ej. partida.txt): ",
                             ruta, LARGO_RUTA)) {
                return NULL;
            }
            p = crear_personaje("Temp", 1, 1, 1); // Personaje temporal para sobreescribir
            if (p != NULL) {
                res = cargar_partida(ruta, p, inventario); // Carga directa al inventario y personaje
                if (res == GUARDADO_OK) {
                    printf("Partida cargada correctamente.\n");
                } else {
                    printf("Error al cargar la partida. Código: %d\n", res);
                    free(p);
                    p = NULL;
                }
            }
        } else {
            printf("Opción no válida.\n");
        }
    } while (p == NULL);

    return p;
}

void iniciar_juego(void) {
    Personaje* jugador = NULL;
    Inventario inventario;
    PilaHistorial* historial = NULL;
    int salir = 0;
    int opcion;

    // Inicialización de sistemas core
    if (inventario_inicializar(&inventario) != INVENTARIO_OK) {
        printf("Error fatal al inicializar el inventario.\n");
        return;
    }
    historial = historial_crear();

    jugador = menu_creacion_personaje(&inventario);
    if (jugador == NULL) {
        printf("\nNo se pudo iniciar la partida.\n");
        inventario_liberar(&inventario);
        historial_liberar(historial);
        return;
    }

    // Bucle principal
    while (!salir && jugador->puntos_vida > 0) {
        printf("\n===================================\n");
        mostrar_estado(jugador);
        printf("===================================\n");
        printf("1. Explorar Zona\n");
        printf("2. Ver Inventario\n");
        printf("3. Usar / Equipar Objeto\n");
        printf("4. Ver Historial de Acciones\n");
        printf("5. Guardar Partida\n");
        printf("6. Salir del Juego\n");
        printf("===================================\n");
        
        if (!leer_entero("¿Qué deseas hacer?: ", &opcion)) {
            printf("\nEntrada cerrada. Saliendo del juego...\n");
            break;
        }

        switch (opcion) {
            case 1:
                iniciar_zona(&inventario, jugador);
                historial_registrar(historial, ACCION_EXPLORACION, "Exploró una zona", NULL);
                break;

            case 2:
                inventario_listar(&inventario);
                break;

            case 3:
                inventario_listar(&inventario);
                if (inventario.cantidad > 0) {
                    int id_obj;
                    if (!leer_entero("Ingresa el ID del objeto a usar (0 para cancelar): ", &id_obj)) {
                        salir = 1;
                        break;
                    }
                    if (id_obj != 0) {
                        Objeto* obj = inventario_buscar_por_id(&inventario, id_obj);
                        if (obj != NULL) {
                            Objeto copia_obj = *obj; // Copia para el historial antes de consumirse
                            ResultadoUso res = usar_objeto(&inventario, id_obj, jugador);
                            if (res == USO_OK || res == USO_OK_ENEMIGO_DISTRAIDO) {
                                historial_registrar(historial, ACCION_USAR_OBJETO, "Se usó/equipó un objeto", &copia_obj);
                            } else {
                                printf("No se pudo usar el objeto (Código de error: %d).\n", res);
                            }
                        } else {
                            printf("Objeto no encontrado en el inventario.\n");
                        }
                    }
                }
                break;

            case 4:
                historial_mostrar(historial);
                break;

            case 5:
            {
                char ruta_guardado[LARGO_RUTA];
                if (!leer_cadena("Ingresa el nombre del archivo para guardar (ej. partida.txt): ",
                                 ruta_guardado, LARGO_RUTA)) {
                    salir = 1;
                    break;
                }
                if (guardar_partida(ruta_guardado, jugador, &inventario) == GUARDADO_OK) {
                    printf("¡Partida guardada con éxito!\n");
                    // ACCION_OTRO: ACCION_VACIA queda reservada para "pila vacia" en historial_desapilar
                    historial_registrar(historial, ACCION_OTRO, "Guardó la partida", NULL);
                } else {
                    printf("Ocurrió un error al guardar la partida.\n");
                }
                break;
            }
            case 6:
                printf("Saliendo del juego...\n");
                salir = 1;
                break;

            default:
                printf("Opción inválida. Intenta nuevamente.\n");
                break;
        }

        if (jugador->puntos_vida <= 0) {
            printf("\n¡Has caído en combate! Fin de la partida.\n");
        }
    }

    // Limpieza de memoria general
    printf("Limpiando memoria...\n");
    inventario_liberar(&inventario);
    historial_liberar(historial);
    free(jugador);
    printf("gracias por jugaaarrr\n");
}