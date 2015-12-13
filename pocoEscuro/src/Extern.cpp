/*
 * Extern.cpp

 *
 *  Created on: 3 de dez de 2015
 *      Author: manuela
 */

#include <comunicacao.h>
#include <Extern.h>

struct InfoRF {
	short id; //o int do arduino é short
	short batimentos;
	short temperatura;
	short movimento;
} infoRF;

Comunicacao com = NULL;

int iniciar(char*porta) {
	com = Comunicacao(porta);
	return com.iniciar();

}

//recebe as letas "i" e "f"
int ler() {
	char ai, at;
	int resultado;
	//int resultado = EXIT_FAILURE;
	resultado = com.ler((char*)&ai, sizeof(ai));
	if ((resultado == EXIT_SUCCESS) && (ai == 'I')) {
		//se a leitura de 'A' correr bem
		//ler a altitude
		resultado = com.ler((char*) &infoRF, sizeof(infoRF));
		if (resultado == EXIT_SUCCESS) {
			//se a leitura da altitude correr bem
			resultado = com.ler((char*) &at, sizeof(at));
			if (resultado == EXIT_SUCCESS && (at == 'T')) {
				//não precisa mais do cout que quem vai imprimir é o java
				//cout << "id = " << info.id << endl;
				//cout << "temp = " << info.temperatura << endl;
				//cout << "batm = " << info.batimentos << endl;
				//cout << "movimento = " << info.movimento << endl;
				resultado = EXIT_SUCCESS;
			}
		}
	}
	return resultado;
}
int getInt() {
	return infoRF.id;
}
int getBatimentos() {
	return infoRF.batimentos;
}
int getTemperatura() {
	return infoRF.temperatura;
}
int getMovimento() {
	return infoRF.movimento;
}
int finalizar() {
	return com.finalizar();
}

