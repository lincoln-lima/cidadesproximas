#include <stdio.h>
#include "../include/youtube_episode_jsense/jsense.h"

typedef struct {
	int cod_ibge;
	char * nome;
	int latitude;
	int longitude;
	int capital;
	int cod_uf;
	int siafi_id;
	int ddd;
	char * fuso;
} Municipio;

void * aloca_municipio(int ibge, char * nome, int latitude, int longitude, int capital, int uf, int id, int ddd, char * fuso) {
	Municipio * cidade = malloc(sizeof(Municipio));

	//usar strpcy
	cidade->cod_ibge = ibge;
	cidade->nome = nome;
	cidade->latitude = latitude;
	cidade->longitude = longitude;
	cidade->capital = capital;
	cidade->cod_uf = uf;
	cidade->siafi_id = id;
	cidade->ddd = ddd
	cidade->fuso = fuso;

	return cidade;
}

int main() {
	JSENSE * arq = jse_from_file("./file/municipios.json");

	printf("%s\n", jse_get(arq, "[0].nome"));
	jse_free(arq);

	return EXIT_SUCCESS;
}
