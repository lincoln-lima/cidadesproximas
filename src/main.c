#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/youtube_episode_jsense/jsense.h"
#include "kd.c"

#define QTD_MUNICIPIOS 5570

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

int get_key_municipio(void * mun) {
	return (*((Municipio *) mun)).cod_ibge;
}

//a partir da passagem de parâmetros, constrói um "objeto" Município
void * aloca_municipio(int ibge, char * nome, double latitude, double longitude, int capital, int uf, int id, int ddd, char * fuso) {
    Municipio * municipio = malloc(sizeof(Municipio));

    municipio->cod_ibge = ibge;
    strcpy(municipio->nome, nome);
    municipio->coord[0]= latitude;
    municipio->coord[1]= longitude;
    municipio->capital = capital;
    municipio->cod_uf = uf;
    municipio->siafi_id = id;
    municipio->ddd = ddd;
    strcpy(municipio->fuso, fuso);

    return municipio;
}

//informe um ponteiro de Municipio e todas suas informações serão mostradas
void printa_municipio(void * cid) {
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
void salva_municipio_json_arv(JSENSE * arq, int pos, Arv * arv) {
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

    Municipio * mun = aloca_municipio(cod_ibge, nome, latitude, longitude, capital, cod_uf, siafi_id, ddd, fuso);

    insere_kd(arv, mun);
}

/*
void busca_municipio_arv(Arv * arv, int key) {
    Municipio * mun = busca_kd(arv, key);

    if(mun) printa_municipio(mun);
    else printf("Município não encontrado...\n");
}
*/

int main() {
    JSENSE * arq = jse_from_file("./file/municipios.json");
    
    Arv arv;
    constroi_kd(&arv, 2, distancia_municipios, compara_coord, printa_municipio, get_key_municipio);

    for(int i = 0; i < QTD_MUNICIPIOS; i++) salva_municipio_json_arv(arq, i, &arv);

    //printa_kd(&arv);
    Municipio * mun = aloca_municipio(4219853,"Zortéa",-27.4521,-51.552,0,42,950,49,"America/Sao_Paulo"); 
    
    n_proximos_kd(&arv,busca_kd(&arv, mun), 5);
    //busca_municipio_arv(&arv, mun);
    
    libera_kd(&arv);

    jse_free(arq);

    return EXIT_SUCCESS;
}
