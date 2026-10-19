#ifndef LISTAE_H
#define LISTAE_H

#include <stddef.h>

#define CAPACIDAD_LISTA 100

typedef struct {
	int elementos[CAPACIDAD_LISTA];
	size_t cantidad;
} Lista;

void init(Lista *lista);
int isempty(const Lista *lista);
int isfull(const Lista *lista);
size_t size(const Lista *lista);
int get(const Lista *lista, size_t posicion, int *valor);
int insert(Lista *lista, size_t posicion, int valor);
int push_front(Lista *lista, int valor);
int push(Lista *lista, int valor);
int remove_at(Lista *lista, size_t posicion, int *valor);
int pop_front(Lista *lista, int *valor);
int pop(Lista *lista, int *valor);
int peek(const Lista *lista, int *valor);
int find(const Lista *lista, int valor, size_t *posicion);
void print(const Lista *lista);

#endif
