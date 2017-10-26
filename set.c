#include "set.h"

int set_create(set_t* self, int index) {
	for (int i = 0; i < block_count; i++) {
		self->blocks[i] = (block_t*) malloc(sizeof(block_t));
		if (!self->blocks[i]) {
			fprintf(stderr, "%s%d\n", "Error al asingar memoria para el bloque: ", i);
		} else {
			block_create(self->blocks[i]);		
		}
	}
	self-> index = index;
	return SUCESS;
}

int set_destroy(set_t* self) {
	for (int i = 0; i < block_count; i++) {
		if (self->blocks[i]) {
			block_destroy(self->blocks[i]);	
			free(self->blocks[i]);
		}
	}
	self->index = -1;
	return SUCESS;
}

block_t* set_get_block(set_t* self, int tag) {
	for (int i = 0; i < block_count; i++) {
		if (block_get_tag(self->blocks[i]) == tag) {
			return self->blocks[i];
		}
	}
	return NULL;
}