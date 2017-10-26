#ifndef __METADATA_H__
#define __METADATA_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define metadata_bit_count 32

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
// metadata debe contener 16 caracters binarios que corresponden
// a tag, index y block offset
int metadata_create(metadata_t* self, unsigned short int address);

// inicializa self
// Pre: self inicializada con metadata_create
int metadata_destroy(metadata_t* self);

// compara el tag, retorna true si son el mismo, false en caso contrario
// Pre: self inicializada con metadata_create
int metadata_get_tag(metadata_t* self);

// compara el indice, retorna true si son el mismo, false en caso contrario
// Pre: self inicializada con metadata_create
int metadata_get_index(metadata_t* self);

// retorna el offset, puede ser 0, 1, 2 o 3
// Pre: self inicializada con metadata_create
int metadata_get_offset(metadata_t* self);

#endif /* __METADATA_H__ */