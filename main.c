#include "cache.h"

#define memory_size 65536 // 64K

char memory[memory_size];
cache_t cache;

void init() { 
	cache_create(&cache);
	for (int i = 0; i < memory_size; i++) {
		memory[i] = 0;
	}
}

int read_byte(int address) {
	char byte_readed;
	metadata_t metadata;
	metadata_create(&metadata, address);

	int result = cache_read_data(&cache, &metadata, &byte_readed);
	if (result == HIT) {
		return (int)byte_readed; // <-- esto no se si esta bien
	}
	// si no es un hit, cache_read_data se encarga de cargar el bloque
	return -1;
}

int write_byte(int address, char value) {
	metadata_t metadata;
	metadata_create(&metadata, address);

	int result = cache_write_data(&cache, &metadata, &value);
	if (result == HIT) {
		return 0;
	}
	// si no es un hit, cache_write_data se encarga de cargar el bloque
	return -1;
}

int get_miss_rate() {
	return cache_get_miss_rate(&cache);
}

int main(int argc, char* argv[]) { 
	init();
	write_byte(0, 1);
	printf("%d\n", read_byte(0));
	/* Leer archivo parsear y operar */
	return 0;
}
