#ifndef __METADATA_H__
#define __METADATA_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define metadata_bit_count 16

#define tag_size 5
#define index_size 9
#define offset_size 2

#define SUCESS 0
#define ERROR -1

typedef struct {
	unsigned short int metadata;
} metadata_t;

// inicializa self con metadata
// Pre: self apunta a un sector valido de memoria
int metadata_create(metadata_t* self, unsigned short int address);

// inicializa self
// Pre: self inicializada con metadata_create
int metadata_destroy(metadata_t* self);

// Pre: self inicializada con metadata_create
int metadata_get_tag(metadata_t* self);

// Pre: self inicializada con metadata_create
int metadata_get_index(metadata_t* self);

// retorna el offset, puede ser 0, 1, 2 o 3
// Pre: self inicializada con metadata_create
int metadata_get_offset(metadata_t* self);

// Pre: self inicializada con metadata_create
unsigned short int metadata_get_address(metadata_t* self);

// construye una direccion a partir de los parametros
int metadata_build(int tag, int index, int offset);

#endif /* __METADATA_H__ */