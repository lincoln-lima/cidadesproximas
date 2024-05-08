#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/youtube_episode_jsense/jsense.h"
#include "../include/mun.h"
#include "../include/hash.h"
#include "../include/kd.h"

#define QTD_MUNICIPIOS 5570
#define TAM_HASH 11139
/*
 * tamanho baseado na quantidade de dados
 * multiplicado por 2 associado ao primo mais próximo
*/

//informe o json JSENSE e a posição da municipio no arquivo
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

/*
void busca_municipio_hash(thash * hash, int key) {
    Municipio * mun = busca_hash(hash, key);

    if(mun) exibe_municipio(mun);
    else printf("Município não encontrado...\n");
}
*/

/*
void busca_municipio_arv(Arv * arv, int key) {
    Municipio * mun = busca_kd(arv, key);

    if(mun) exibe_municipio(mun);
    else printf("Município não encontrado...\n");
}
*/

int main() {
    JSENSE * arq = jse_from_file("./file/municipios.json");
    
    thash hash;
    constroi_hash(&hash, TAM_HASH, get_key_municipio);

    //exibe_hash(&hash);

    Arv arv;
    constroi_kd(&arv, 2);

    for(int i = 0; i < QTD_MUNICIPIOS; i++) {
		insere_hash(&hash, acessa_municipio_json(arq, i));
		insere_kd(&arv, acessa_municipio_json(arq, i));
    }

    int cod_ibge, qtd;
    do {
		printf("----------------------------------------------------\n");
		printf("INFORME\n");
		printf("Código do IBGE da cidade desejada: ");
		scanf("%d", &cod_ibge);

		Municipio * mun = busca_hash(&hash, cod_ibge);

		if(mun) {
			exibe_municipio(mun);

			printf("Quantidade de cidades mais próximas: ");
			scanf("%d", &qtd);
			int * proximos = n_proximos_kd(&arv, mun, qtd);

			printf("\n");

			printf("Código(s) IBGE da(s) %d cidade(s) mais próxima(s):\n", qtd);
			for(int * p = proximos; p < proximos + qtd ; p++) printf("%d\n", *p);

			printf("\n");

			free(proximos);
		}
		else printf("\n!!!Município não encontrado!!!\n");

    } while(cod_ibge > 0);

    //exibe_kd(&arv);
		
    libera_hash(&hash);
    libera_kd(&arv);

    jse_free(arq);

    return EXIT_SUCCESS;
}
