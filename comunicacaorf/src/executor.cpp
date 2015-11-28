/*
 * executor.cpp


 *
 *  Created on: 26 de nov de 2015
 *      Author: manuela
 */

#include <iostream>
#include "Comunicacao.h"

using namespace std;

struct InfoRF{
  short id; //o int do arduino � short
  short batimentos;
  short temperatura;
  boolean movimento;
};


int main(char **argv, int argc){

	//criar uma instancia da classe de comunica��o
	//#ifdef __linux__
	//	Comunicacao com = Comunicacao("/dev/ttyACM0");
	//#endif
	//#ifdef _WIN32 || _WIN64
	//	Comunicacao com = Comunicacao("COM6");
	//#endif

		InfoRF info = {0};

		Comunicacao com = Comunicacao("COM6");

		com.iniciar();

		 //coloca zero para todas as posi��es
		while(true){
			if(com.ler((char*)&info, sizeof(InfoRF)) == 0){
				cout <<"id = "<< info.id << endl;
				cout <<"temp = "<< info.temperatura << endl;
				cout <<"batm = "<< info.batimentos << endl;
				cout <<"movimento = "<< info.movimento << endl;
			}

			Sleep(50);
		}

		//Sleep(50);
	return 0;
}


