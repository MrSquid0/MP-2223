/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "FuncionesExternas.h"
#include <iostream>
#include <string>

using namespace std;
/******************************* FUNCIONES EXTERNAS */

/**
 * @brief muestra por pantalla el contenido de un vector de jugadores
 * @param v, vector de jugadores
 * @param n numero de jugadores reales en el vector, nutils
 */

void imprimirVector(const Jugador *v, int n)  {
	for (int i=0; i<n; i++)
		std::cout << v[i].get_id() << "->(" << v[i].get_nickName() << "," << v[i].get_puntuacion()<< ")," << std::endl;
}

/**
 * @brief reserva memoria para n jugadors,
 * @param n número de jugadors a reservar
 * @return direcion de inicio de memoria reservada
 */


Jugador * reservaM(int n) {
    Jugador *jugadores = new Jugador[n];
    return jugadores;
}

/**
 * @brief Libera la memoria correspondiente a un vector de Jugadores
 * @param v direccion de comienzo del vector dinamico que hay que liberar, 
 * el contenido se ve alterado
 */


void liberarM(Jugador *v) {
    if (v != 0){
        delete [] v;
        v = 0;
    }
}

/**
 * @brief crea un nuevo vector con un jugador adicional, para lo que ha de
 * volcar todos los jugadoress anteriores y añadir el nuevo jugador
 * @param devuelve un nuevo vector redimensionado
 * @param devuelve el nuevo tamaño del vector
 */

void agnadeJugador(Jugador *&v, int &tam,  const Jugador nuevo) {
   
    // reservar memoria para un array auxiliar llamado temp
    Jugador *temp = reservaM(tam+1);
    
    // copiar todos los tam elementos de v en temp
    for (int i=0; i<tam; i++){
        temp[i] = v[i];
    }
    
    // copiar  nuevo en la posición apropiada de temp
    temp[tam] = nuevo;
    
    // liberar memoria de v
    liberarM(v);
    
    // asignar temp a v
    v = temp;
    
    // actualizar tam correctamente
    tam++;
}


/**
 * 
 * @param v vector de Jugadores donde buscar
 * @param nutil, numero de elementos de v
 * @param uno Jugador que se busca
 * @return posicion con valores entre 0 y nutils-1 si se encuentra o bien -1 si no está
 */


int findJugador(const Jugador *v, int nutil, const Jugador &uno) {
    int pos = -1;
    
    for (int i = 0; i < nutil && pos == -1; i++) {
        if (v[i].get_id() == uno.get_id())
            pos = i;
    }
    return pos;
}


/**
 * 
 * @param v1 vector1 de jugadores 
 * @param n1 nutil de vector1
 * @param v2 vector2 de jugadores 
 * @param n2 nutil de vector2
 * @param r  vector resultado
 * @param nr nutil de vector resultado
 * NB: revisar la forma de pasar los argumentos (por valor, referencia etc.)  
 */

void interseccionEncuentros(const Jugador *v1, const int &n1, const Jugador *v2, const int &n2,  Jugador *&r, int &nr){
    for (int i=0; i<n1; i++){
        int posEncontrada = findJugador(v2, n2, v1[i]);
        if (posEncontrada != -1){
            if (v2[posEncontrada].get_puntuacion() >= v1[i].get_puntuacion())
                agnadeJugador(r, nr, v2[posEncontrada]);
            else {
                agnadeJugador(r, nr, v1[i]);
            }
        }
    }
}

void leerArray(Jugador *&encuentro, int &tamanio){
    int _id;
    string alias;
    double _puntuacion;
    cout << "id (-1 para terminar):";
    cin >> _id;
    while (_id != -1){
        cin >> alias >>  _puntuacion;
        Jugador jugador;
        jugador.set_Jugador(_id, alias, _puntuacion);
        agnadeJugador(encuentro, tamanio, jugador);
        cout << "id (-1 para terminar):";
        cin >> _id;
    }
}