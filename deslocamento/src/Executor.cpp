/*
 * Executor.cpp
 *
 *  Created on: 29 de out de 2015
 *      Author: Manuela e Cremildo
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

struct InfoRF{
  short id; //o int do arduino é short
  short batimentos;
  short temperatura;
  boolean movimento;
};

int main (int argc, char** argv){

	//criar uma instancia da classe de comunicação
	//#ifdef __linux__
	//	Comunicacao com = Comunicacao("/dev/ttyACM0");
	//#endif
	//#ifdef _WIN32 || _WIN64
	//	Comunicacao com = Comunicacao("COM6");
	//#endif

		InfoRF info = {0};

		Comunicacao com = Comunicacao("COM6");

		com.iniciar();

		 //coloca zero para todas as posições
		while(true){
			if(com.ler((char*)&info, sizeof(InfoRF)) == 0){
				cout <<"id = "<< info.id << endl;
				cout <<"temp = "<< info.temperatura << endl;
				cout <<"batm = "<< info.batimentos << endl;
				cout <<"movimento = "<< info.movimento << endl;
			}

			Sleep(50);
		}
}