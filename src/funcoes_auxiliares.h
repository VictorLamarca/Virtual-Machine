/*
 * funcoes_auxiliares.h
 *
 *  Created on: 30 de jun de 2018
 *      Author: vlamarca
 */

#ifndef FUNCOES_AUXILIARES_H_
#define FUNCOES_AUXILIARES_H_

#include <bits/stdc++.h>
#include "memoria_e_registradores.h"
#include "interpretador_de_comandos.h"
#include "maquina_virtual.h"
#include "montador.h"
#include <unistd.h>
#include <dirent.h>
using namespace std;

extern bool idebug;
extern int oposto_checksum;

#define BYTE unsigned char
#define DOIS_BYTES unsigned short int

string tiraExtencao(string s);

void erro(string mnsgm);

//recebe uma string, identifica se eh hexadecimal, decimal ou binário e retorna o valor correspondente
int toVal(string s);

char letraHexa(BYTE val);

string byteToHexa(BYTE val);

bool isnum(string s);

#endif /* FUNCOES_AUXILIARES_H_ */
