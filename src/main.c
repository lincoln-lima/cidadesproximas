#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/youtube_episode_jsense/jsense.h"
#include "../include/mun.h"
#include "../include/hash_int.h"
#include "../include/hash_string.h"
#include "../include/kd.h"

#define QTD_MUNICIPIOS 5570
#define TAM_HASH 11139
/*
 * tamanho baseado na quantidade de dados
 * multiplicado por 2 associado ao primo mais próximo
*/

//informe o json JSENSE e a posição do municipio no arquivo
Municipio * acessa_municipio_json(JSENSE * arq, int pos) {
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
    double latitude, longitude;

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

    return aloca_municipio(cod_ibge, nome, latitude, longitude, capital, cod_uf, siafi_id, ddd, fuso);
}

int main() {
	JSENSE * arq = jse_from_file("./file/municipios.json");

	HashInt hash_int;
	constroi_hash_int(&hash_int, TAM_HASH, get_key_municipio_cod_ibge);

	Arv arv;
	constroi_kd(&arv, 2);

	HashString hash_string;
	constroi_hash_string(&hash_string, TAM_HASH, get_key_municipio_nome);

	for(int i = 0; i < QTD_MUNICIPIOS; i++) {
		insere_hash_int(&hash_int, acessa_municipio_json(arq, i));
		insere_kd(&arv, acessa_municipio_json(arq, i));
		insere_hash_string(&hash_string, acessa_municipio_json(arq, i));
	}

	char nome[35];

	printf("----------------------------------------------------\n");
	printf("INFORME\n");
	printf("Nome da cidade desejada: ");
	scanf(" %[^\n]", nome);

	Municipio * mun = NULL;
	Municipio ** muns = (Municipio **) busca_hash_string(&hash_string, nome);

	int qtd_muns = 0;
	while(muns[qtd_muns++]);

	qtd_muns--;

	if(qtd_muns > 1) {
		int op = 0;

		for(int i = 0; i < qtd_muns; i++) {
			exibe_municipio(muns[i]);
			printf("OPÇÃO: %d\n", i+1);
		}
		
		while(op < 1 || op > qtd_muns) {
			printf("\nEscolha a opção desejada: ");
			scanf("%d", &op);

			if(op < 1 || op > qtd_muns) printf("\n!!!Opção inválida!!!\n");
		}

		mun = (Municipio *) muns[op-1];
		free(muns);
	}
	else if(qtd_muns == 1) mun = (Municipio *) muns[0];

	if(mun) {
		int qtd_prox;
		printf("\nQuantidade de cidades mais próximas: ");
		scanf("%d", &qtd_prox);

		int * proximos = n_proximos_kd(&arv, mun, qtd_prox);

		printf("\n");
		printf("Dados da(s) %d cidade(s) mais próxima(s):\n", qtd_prox);
		for(int * p = proximos; p < proximos + qtd_prox; p++) exibe_municipio(busca_hash_int(&hash_int, *p)); 

		free(proximos);
	}
	else printf("\n!!!Município não encontrado!!!\n");
		
    libera_hash_int(&hash_int);
    libera_kd(&arv);
    libera_hash_string(&hash_string);

    jse_free(arq);

    return EXIT_SUCCESS;
}
