#include <stdio.h>
#include <string.h>
#include "../include/youtube_episode_jsense/jsense.h"

typedef struct {
	int cod_ibge;
	char * nome;
	float latitude;
	float longitude;
	int capital;
	int cod_uf;
	int siafi_id;
	int ddd;
	char * fuso;
} Municipio;

void * aloca_municipio(int ibge, char * nome, float latitude, float longitude, int capital, int uf, int id, int ddd, char * fuso) {
	Municipio * cidade = malloc(sizeof(Municipio));

	//usar strpcy
	cidade->cod_ibge = ibge;
	strcpy(cidade->nome, nome);
	cidade->latitude = latitude;
	cidade->longitude = longitude;
	cidade->capital = capital;
	cidade->cod_uf = uf;
	cidade->siafi_id = id;
	cidade->ddd = ddd;
	strcpy(cidade->fuso, fuso);

	return cidade;
}

void salvando_municipio(JSENSE * arq) {
	int cod_ibge = jse_get(arq, "[0].codigo_ibge");
        char * nome = jse_get(arq, "[0].nome");
        float latitude = jse_get(arq, "[0].latitude");
        float longitude = jse_get(arq, "[0].longitude");
        int capital = jse_get(arq, "[0].capital");
        int cod_uf = jse_get(arq, "[0].codigo_uf");
        int siafi_id = jse_get(arq, "[0].siafi_id");
        int ddd = jse_get(arq, "[0].ddd");
        char * fuso = jse_get(arq, "[0].fuso_horario");

	Municipio * cidade = aloca_municipio(cod_ibge, nome, latitude, longitude, capital, cod_uf, siafi_id, ddd, fuso);

	printa_municipio(cidade);
}

void printa_municipio(Municipio * mun) {
	printf("%d\n", mun->cod_ibge);
	printf("%s\n", mun->nome);
	printf("%f\n", mun->latitude);
	printf("%f\n", mun->longitude);
	printf("%d\n", mun->capital);
	printf("%d\n", mun->cod_uf);
	printf("%d\n", mun->siafi_id);
	printf("%d\n", mun->ddd);
	printf("%s\n", mun->fuso);	
}

int main() {
	JSENSE * arq = jse_from_file("./file/municipios.json");

	salvando_municipio(arq);
	jse_free(arq);

	/*
	printf("%s\n", jse_get(arq, "[0].nome"));
	jse_free(arq);
	*/
	return EXIT_SUCCESS;
}
