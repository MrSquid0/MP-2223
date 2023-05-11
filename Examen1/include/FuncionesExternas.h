/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncionesExternas.h
 * Author: sihamtabik
 *
 * Created on 8 de mayo de 2023, 10:29
 */

#ifndef FUNCIONESEXTERNAS_H
#define FUNCIONESEXTERNAS_H


#include "Jugador.h"
 

void imprimirVector(const Jugador *v, int n) ;

Jugador * reservaM(int n) ;

void liberarM(Jugador *v) ;

void agnadeJugador(Jugador *&v, int &tam,  const Jugador nuevo);

int findJugador(const Jugador *v, int nutil, const Jugador &uno) ;
 
void interseccionEncuentros(const Jugador *v1, const int &n1, const Jugador *v2, const int &n2,  Jugador *&r, int &nr);

void leerArray(Jugador *&encuentro, int &tamanio);


#endif /* FUNCIONESEXTERNAS_H */

