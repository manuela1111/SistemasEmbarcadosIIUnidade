/*
 * Extern.h
 *
 *  Created on: 3 de dez de 2015
 *      Author: manuela
 */
#ifndef EXTERN_H_
#define EXTERN_H_

#ifdef __cplusplus
extern "C" {
#endif

int iniciar (char*porta);
int ler ();
int getInt();
int getVelocidade();
int getAltitude();
int getMovimento();
int finalizar();

#ifdef __cplusplus
}
#endif
#endif /* EXTERN_H_ */
