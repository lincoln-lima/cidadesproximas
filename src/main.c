#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/youtube_episode_jsense/jsense.h"
#include "hash.c"
#include "kd.c"

#define QTD_MUNICIPIOS 5570
#define TAM_HASH 11139
/*
 * tamanho baseado na quantidade de dados
 * multiplicado por 2 associado ao primo mais próximo
*/

typedef struct {
    int cod_ibge;
    char nome[35];
    double coord[2];
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
void * aloca_municipio(int ibge, char * nome, double latitude, double longitude, int capital, int uf, int id, int ddd, char * fuso) {
    Municipio * mun = malloc(sizeof(Municipio));

    mun->cod_ibge = ibge;
    strcpy(mun->nome, nome);
    mun->coord[0]= latitude;
    mun->coord[1]= longitude;
    mun->capital = capital;
    mun->cod_uf = uf;
    mun->siafi_id = id;
    mun->ddd = ddd;
    strcpy(mun->fuso, fuso);

    return mun;
}

//informe um ponteiro de Municipio e todas suas informações serão mostradas
void exibe_municipio(void * cid) {
    Municipio * mun = (Municipio *) cid;

    printf("------------------------------\n");
    printf("\n");
    printf("EXIBINDO DADOS...\n\n");
    printf("codigo_ibge: %d\n", mun->cod_ibge);
    printf("nome: %s\n", mun->nome);
    printf("latitude: %f\n", mun->coord[0]);
    printf("longitude: %f\n", mun->coord[1]);
    printf("capital: %d\n", mun->capital);
    printf("codigo_uf: %d\n", mun->cod_uf);
    printf("siafi_id: %d\n", mun->siafi_id);
    printf("ddd: %d\n", mun->ddd);
    printf("fuso_horario: %s\n", mun->fuso);
    printf("\n");
}

double distancia_municipios(void * cid1, void * cid2) {
    Municipio * mun1 = (Municipio *) cid1;
    Municipio * mun2 = (Municipio *) cid2;

    double aux;
    double dist = 0;

    for(int i = 0; i < 2; i++) {
	    aux = mun1->coord[i] - mun2->coord[i];
	    aux *= aux;
	    dist += aux;
    }

    return sqrt(dist);
}

double compara_coord(void * cid1, void * cid2, int eixo) {
    return ((Municipio *) cid1)->coord[eixo] - ((Municipio *) cid2)->coord[eixo];
}	

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
void busca_municipio_hash(thash * arv, int key) {
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
    constroi_kd(&arv, 2, distancia_municipios, compara_coord, exibe_municipio);

    for(int i = 0; i < QTD_MUNICIPIOS; i++) {
		insere_hash(&hash, acessa_municipio_json(arq, i));
		insere_kd(&arv, acessa_municipio_json(arq, i));
	}

	//printf("distancia: %f\n", distancia_municipios(busca_hash(&hash, 2114007), &(arv.raiz)));

	int cod_ibge = 2114007;
//	do {
//		printf("----------------------------------------------------\n");
//		printf("Informe o código do IBGE da cidade desejada: ");
//		scanf("%d", &cod_ibge);

		Municipio * mun = busca_hash(&hash, cod_ibge);

		if(mun)	n_proximos_kd(&arv, mun, 5);
		else printf("Município não encontrado...\n");

		//busca_municipio_hash(&hash, cod_ibge);

	//} while(cod_ibge > 0);

    //exibe_kd(&arv);
    
    //busca_municipio_arv(&arv, mun);
    
	libera_hash(&hash);
    libera_kd(&arv);

    jse_free(arq);

    return EXIT_SUCCESS;
}
