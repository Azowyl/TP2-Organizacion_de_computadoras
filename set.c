#include "set.h"

int set_create(set_t* self, int index) {
	self-> index = index;
	for (int i = 0; i < block_count; i++) {
		self->blocks[i] = NULL;
	}
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
		if (self->blocks[i]) {
			if (block_get_tag(self->blocks[i]) == tag) {
			self->last_recent_used = i;
			return self->blocks[i];
			}
		}
	}
	return NULL;
}

int set_insert_block(set_t* self, block_t* block) {
	for (int i = 0; i < block_count; i++) {
		if (!self->blocks[i]) {
			self->blocks[i] = (block_t*) malloc(sizeof(block_t));
			memcpy(self->blocks[i], block, sizeof(block_t));
			return SUCESS;
		}
	}

	// LRU
	int index;
	if (self->last_recent_used == 0) {
		// remplaza el segundo
		index = 1;
	} else { index = 0; }

	// Write Back
	if (block_get_dirty_bit(self->blocks[index])) { 
		// si esta dirty lo escribe en memoria
		for (int i = 0; i < block_size; i++) {
			// se esbriben 4 bytes comenzando en address con offset 0 
			int address = metadata_build(block_get_tag(self->blocks[index]), self->index, 0);
			block_get_data(self->blocks[index], i, &memory[address]);
		}
	}
	block_destroy(self->blocks[index]);
	memcpy(self->blocks[index], block, sizeof(block_t));
	return SUCESS;
}
