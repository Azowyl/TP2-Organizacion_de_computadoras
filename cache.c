#include "cache.h"

int cache_create(cache_t* self) {
	int index = 0;
	for (int i = 0; i < set_count; i++) {
		self->sets[i] = (set_t*) malloc(sizeof(set_t));
		if (!self->sets[i]) {
			fprintf(stderr, "%s%d\n", "Error al asingar memoria para el set: ", i);
		} else {
			set_create(self->sets[i], index++);		
		}
	}
	return SUCESS;
}

int cache_destroy(cache_t* self) {
	for (int i = 0; i < set_count; i++) {
		if (self->sets[i]) {
			set_destroy(self->sets[i]);	
			free(self->sets[i]);
		}
	}
	return SUCESS;
}	

bool cache_read_block(cache_t* self, metadata_t* metadata, void* data) {
	self->access++;

	int index = metadata_get_index(metadata);
	if (index < 0 || index > set_count){
		return false;
	}

	block_t* block = set_get_block(self->sets[index], metadata_get_tag(metadata));

	if (block) {
		if (block_get_valid(block)) {
			data = block_get_data(block);
			return true;	
		}
	}

	self->misses++;
	return false;
}

int cache_write_block(cache_t* self, metadata_t* info, void* data) {
	// TODO
	return 0;
}