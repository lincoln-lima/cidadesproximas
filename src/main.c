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
	cidade->nome = nome;
	cidade->latitude = latitude;
	cidade->longitude = longitude;
	cidade->capital = capital;
	cidade->cod_uf = uf;
	cidade->siafi_id = id;
	cidade->ddd = ddd;
	cidade->fuso = fuso;

	return cidade;
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

	free(mun);
}

char * converte_pos(int num) {
	//'\0' ao fim
	char begin[2], end[3], num_s[5];
	char final[7] = "";
	
	//tamanho da string em bytes, para bits na passagem do buffer
	tec_string_from_int(num, num_s, sizeof(num_s)*8);
 
	strcpy(begin, "[");
	strcpy(end, "].");
	strcpy(num_s, "5569");
	  
	strcat(final, begin);
	strcat(final, num_s);
	strcat(final, end);
	  
	printf("%s\n", final);

	return final;
}

void salvando_municipio(JSENSE * arq, int num) {
	int error;

	char num_s[4];
	
	char * campos[9] = 
	{
	"codigo_ibge","nome","latitude","longitude","capital","codigo_uf","siafi_id","ddd","fuso_horario"
	};

	int cod_ibge = tec_string_to_int(jse_get(arq, "[0].codigo_ibge"));
        char * nome = jse_get(arq, "[0].nome");
        float latitude = tec_string_to_double(jse_get(arq, "[0].latitude"), &error);
        float longitude = tec_string_to_double(jse_get(arq, "[0].longitude"), &error);
        int capital = tec_string_to_int(jse_get(arq, "[0].capital"));
        int cod_uf = tec_string_to_int(jse_get(arq, "[0].codigo_uf"));
        int siafi_id = tec_string_to_int(jse_get(arq, "[0].siafi_id"));
        int ddd = tec_string_to_int(jse_get(arq, "[0].ddd"));
        char * fuso = jse_get(arq, "[0].fuso_horario");

	Municipio * cidade = aloca_municipio(cod_ibge, nome, latitude, longitude, capital, cod_uf, siafi_id, ddd, fuso);

	printa_municipio(cidade);
}

int main() {
	JSENSE * arq = jse_from_file("./file/municipios.json");

	//salvando_municipio(arq, 0);
	
	//printf("%s\n", converte_pos(5569));

	char * txt = "jooj";
	while(*txt) {
		printf("%s\n", txt);
		*txt++;
	}
	
	//printf("%s\n", jse_get(arq, "[0].nome"));
	jse_free(arq);

	return EXIT_SUCCESS;
}
