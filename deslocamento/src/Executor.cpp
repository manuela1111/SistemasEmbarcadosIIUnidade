/*
 * Executor.cpp
 *
 *  Created on: 29 de out de 2015
 *      Author: manuela
 */
#include <stdlib.h>
#include <iostream>

using namespace std;

int main (int argc, char** argv){

	int temperatura = 36;
	int pressaoSistolica = 8;
	int pressaoDiastolica = 12;
	int batimentos = 100;

	//o int do c++ é o long do arduino
	int info = 0;

	//o sizeof do int é 4 bytes
	cout <<"tam = "<<sizeof(info)<<endl;

	//esse | não é de condicional é de operação binária entre o info e cada um
	//int info             00000000 00000000 00000000 00000000
	//temp é 36 em binário 00100100 preenche com os zeros
	//o próximo deslocamento é 16
	//pressao Sistolica             00001000

	info = info | (temperatura << 24);
	info = info | (pressaoSistolica << 16);
	info = info | (pressaoDiastolica << 8);
	info = info | batimentos;

	cout <<"info = "<<info<<endl;

	//informação enviada pelo RF Transmissor

	//vamos recuperar as informações usando o & lógico
	//4278190000 equivale a 11111111 00000000 00000000 00000000
	//16711680 equivale
	int temperaturaRec = (info & 4278190000)>>24;
	//para pegar a pressão sistolica desloca o 1111111 para a direita
	int pressaoSistolicaRec = (info & 16711680)>>16;
	int pressaoDiastolicaRec = (info & 65280)>>8;
	int batimentosRec = (info & 255);

	//informação decodifcada pelo receptor
	cout <<"Temperatura = "<<temperaturaRec<<endl;
	cout <<" Pressão Sistólica = "<<pressaoSistolicaRec<<endl;
	cout <<"Pressão Diastólica = "<<pressaoDiastolicaRec<<endl;
	cout <<"Batimentos = "<<batimentosRec<<endl;
}









