/*
 * executor.cpp


 *
 *  Created on: 26 de nov de 2015
 *      Author: manuela
 */

#include <iostream>
#include "comunicacao.h"

using namespace std;

struct InfoRF {
	short id; //o int do arduino � short
	short movimento;
	short velocidade;
	short altitude;
};

int main(char **argv, int argc) {

	InfoRF info = { 0 };
	char ai, at;

	//criar uma instancia da classe de comunicacao
#ifdef __linux__
	Comunicacao com = Comunicacao("/dev/ttyACM0");
#endif
#ifdef _WIN32 || _WIN64
	Comunicacao com = Comunicacao("COM6");
#endif

	com.iniciar();
	//realizar a leitura do caracter "A" (Inicial)
	int resultado;

	resultado = com.ler((char*) &ai, sizeof(ai));

	//coloca zero para todas as posicoes
	/*while(true){
	 if(com.ler((char*)&info, sizeof(InfoRF)) == 0){
	 cout <<"id = "<< info.id << endl;
	 cout <<"temp = "<< info.temperatura << endl;
	 cout <<"batm = "<< info.batimentos << endl;
	 cout <<"movimento = "<< info.movimento << endl;
	 }

	 Sleep(50);
	 }*/
	while (true) {
		if ((resultado == EXIT_SUCCESS) && (ai == 'I')) {
			//se a leitura de 'A' correr bem
			//ler a altitude
			resultado = com.ler((char*) &info, sizeof(info));
			if (resultado == EXIT_SUCCESS) {
				//se a leitura da altitude correr bem
				resultado = com.ler((char*) &at, sizeof(at));
				if (resultado == EXIT_SUCCESS && (at == 'T')) {
					cout << "id = " << info.id << endl;
					cout << "velocidade = " << info.velocidade << endl;
					cout << "altitude = " << info.altitude << endl;
					cout << "movimento = " << info.movimento << endl;
				}
			}
		}

		Sleep(50);
	}
	return 0;
}

