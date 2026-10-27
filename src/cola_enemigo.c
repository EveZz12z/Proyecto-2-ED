#include "cola_enemigo.h"

ColaEnemigo cola_enemigo_create(){
    ColaEnemigo q = (ColaEnemigo)malloc(sizeof(struct _ColaEnemigo));
    if (q == NULL){
        printf("Error: falta de memoria (cola enemigo) \n");
        return NULL;
    }

    q->front = NULL;
    q->rear = NULL;
    q->tamanio = 0;

    return q;
}

ColaEnemigo cola_enemigo_make_empty(ColaEnemigo q){
    if (q != NULL){
        NodoEnemigo* actual = q->front;
        while (actual != NULL){
            NodoEnemigo* siguiente_nodo = actual->siguiente;
            free(actual);
            actual = siguiente_nodo;
        }
        
        q->front = NULL;
        q->rear = NULL;
        q->tamanio = 0;
    }

    return q;
}

int cola_enemigo_is_empty(ColaEnemigo q){
    return(q == NULL || q->front == NULL);
}

ColaEnemigo cola_enemigo_enqueue(Enemigo e, ColaEnemigo q){
    if (q == NULL){
        return q;
    }

    NodoEnemigo* nuevo_nodo = (NodoEnemigo*)malloc(sizeof(NodoEnemigo));
    if (nuevo_nodo == NULL){
        printf("Error: falta de memoria (nuevo nodo enemigo) \n");
        return q;
    }
    
    nuevo_nodo->enemigo = e;
    nuevo_nodo->siguiente = NULL;

    if (cola_enemigo_is_empty(q)){
        q->front = nuevo_nodo;
    }else{
        q->rear->siguiente = nuevo_nodo;
    }
    q->rear = nuevo_nodo;
    q->tamanio++;

    return q;
}

Enemigo cola_enemigo_dequeue(ColaEnemigo q){
    if (cola_enemigo_is_empty(q)){
        printf("La cola enemigo esta vacia \n");
        return (Enemigo){-1, "Desconocido", 0, 0};
    }
    
    NodoEnemigo* nodo_eliminar = q->front;
    Enemigo e = nodo_eliminar->enemigo;

    q->front = q->front->siguiente;

    if (q->front == NULL){
        q->rear = NULL;
    }
    
    free(nodo_eliminar);
    q->tamanio--;

    return e;
}

Enemigo cola_enemigo_front(ColaEnemigo q){
    if (cola_enemigo_is_empty(q)){
        printf("La cola de enemigo esta vacia (front) \n");
        return (Enemigo){-1, "Desconocido", 0, 0};
    }
    return q->front->enemigo;
}

int cola_enemigo_size(ColaEnemigo q){
    if (q == NULL){
        return 0;
    }

    return q->tamanio;
}

void cola_enemigo_delete(ColaEnemigo q){
    if (q != NULL){
        cola_enemigo_make_empty(q);
        free(q);
    }
}