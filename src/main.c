#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/youtube_episode_jsense/jsense.h"
#include "hash.c"

#define QTD_CIDADES 5570
#define TAM_HASH 11139
/* 
 * tamanho baseado na quantidade de dados
 * multiplicado por 2 associado ao primo mais próximo
*/

typedef struct {
	int cod_ibge;
	char nome[35];
	float latitude;
	float longitude;
	int capital;
	int cod_uf;
	int siafi_id;
	int ddd;
	char fuso[50];
} Municipio;

//define a chave de cada município
int get_key_municipio(void * mun) {
	return (*((Municipio *) mun)).cod_ibge;
}

//a partir da passagem de parâmetros, constrói um "objeto" Município
void * aloca_municipio(int ibge, char * nome, float latitude, float longitude, int capital, int uf, int id, int ddd, char * fuso) {
	Municipio * cidade = malloc(sizeof(Municipio));

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

//informe um ponteiro de Municipio e todas suas informações serão mostradas
void printa_municipio(Municipio * mun) {
	printf("EXIBINDO DADOS...\n\n");
	printf("codigo_ibge: %d\n", mun->cod_ibge);
	printf("nome: %s\n", mun->nome);
	printf("latitude: %f\n", mun->latitude);
	printf("longitude: %f\n", mun->longitude);
	printf("capital: %d\n", mun->capital);
	printf("codigo_uf: %d\n", mun->cod_uf);
	printf("siafi_id: %d\n", mun->siafi_id);
	printf("ddd: %d\n", mun->ddd);
	printf("fuso_horario: %s\n", mun->fuso);
}

//informe o json JSENSE e a posição da cidade no arquivo
void salva_municipio_json_hash(JSENSE * arq, int pos, thash * hash) {
	int error;

	char * campos[9] = 
	{
	"codigo_ibge",
	"nome",
	"latitude",
	"longitude",
	"capital",
	"codigo_uf",
	"siafi_id",
	"ddd",
	"fuso_horario"
	};

	char operacao[20];
	
	int cod_ibge, capital, cod_uf, siafi_id, ddd;
	char nome[35];
	char fuso[50];
	float latitude, longitude;

	for(int i = 0; i < 9; i++) {
		sprintf(operacao, "[%d].%s", pos, campos[i]);

		switch(i) {
			case 0:
				cod_ibge = tec_string_to_int(jse_get(arq, operacao));
			break;
			case 1:
				strcpy(nome, jse_get(arq, operacao));
			break;
			case 2:
				latitude = tec_string_to_double(jse_get(arq, operacao), &error);
			break;
			case 3:
				longitude = tec_string_to_double(jse_get(arq, operacao), &error);
			break;
			case 4:
				capital = tec_string_to_int(jse_get(arq, operacao));
			break;
			case 5:
				cod_uf = tec_string_to_int(jse_get(arq, operacao));
			break;
			case 6:
				siafi_id = tec_string_to_int(jse_get(arq, operacao));
			break;
			case 7:
				ddd = tec_string_to_int(jse_get(arq, operacao));
			break;
			case 8:
				strcpy(fuso, jse_get(arq, operacao));
			break;
		}
	}

	Municipio * mun = aloca_municipio(cod_ibge, nome, latitude, longitude, capital, cod_uf, siafi_id, ddd, fuso);

	insere_hash(hash, mun);
}

void busca_municipio_hash(thash * hash, int key) {
	Municipio * mun = busca_hash(hash, key);

	if(mun) printa_municipio(mun);
	else printf("Município não encontrado...\n");
}

int main() {
	JSENSE * arq = jse_from_file("./file/municipios.json");
	
	thash hash;
	constroi_hash(&hash, TAM_HASH, get_key_municipio);

	for(int i = 0; i < QTD_CIDADES; i++) salva_municipio_json_hash(arq, i, &hash);

	printa_hash(&hash);

	busca_municipio_hash(&hash, 3100104);

	apaga_hash(&hash);

	jse_free(arq);

	return EXIT_SUCCESS;
}
