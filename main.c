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

float get_miss_rate() {
	return cache_get_miss_rate(&cache);
}

int main(int argc, char* argv[]) { 
	if (argc != 2) { return ERROR; }

	init();

	FILE* file = fopen(argv[1], "rt");
	if (!file) {
		fprintf(stderr, "%s\n", "Error al abrir el archivo");
		cache_destroy(&cache);
		return ERROR;
	}

	char buffer[15];
	int lines_counter = 0;
	while (!feof(file)) {
		if (fgets(buffer, 15, file) == NULL) { break; }
		char operation = 0;
		int address;
		int value;
		sscanf(buffer, "%c%d%d", &operation, &address, &value);
		lines_counter++;
		switch (operation) {
			case 'R':
				read_byte(address);
				break;
			case 'W':
				write_byte(address, value);
				break;
			case 'M':
				printf("%0.f\n", get_miss_rate());
				break;
			default:
				if (operation == '\n') { continue; }
				fprintf(stderr, "%s%d\n", "Comando invalido en la linea: ", lines_counter);
				continue;
		}
	}
	cache_destroy(&cache);
	fclose(file);
	return 0;
}
