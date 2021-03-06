#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define block_size 4 // bytes
#define ERROR -1
#define SUCESS 0

typedef struct {
	char* data;
	int tag;
	bool valid;
	bool dirty;
} block_t;

// inicializa un bloque de cache
// Pre: self apunta a un sector valido de memoria
int block_create(block_t* self, int tag);

// destruye self liberando sus recursos
// Pre: self inicializada con block_create
int block_destroy(block_t* self);

bool block_get_dirty_bit(block_t* self);

bool block_get_valid_bit(block_t* self);

void block_set_dirty(block_t* self, bool is_dirty);

// retorna el tag asignado, -1 si no tiene tag
// Pre: self inicializada con block_create
int block_get_tag(block_t* self);

// guarda data en el bloque
// Pre: self inicializada con block_create
// data apunta a un sector valido de memoria y 
// tiene un tamaño menor o igual a block_size
int block_set_data(block_t* self, char* data);

// Pre: self inicializada con block_create
// data apunta a un sector valido de memoria
int block_get_data(block_t* self, int offset, char* data);

#endif /* __BLOCK_H__ */