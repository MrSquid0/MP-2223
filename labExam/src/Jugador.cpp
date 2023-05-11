/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Jugador.h"


Jugador::Jugador(){
    id = -1;
    nickname = "ANONIMOUS";
    puntuacion = 0;
}

Jugador::Jugador( long _id, const std::string &alias, double _puntuacion=0){
    id = _id;
    nickname = alias;
    puntuacion = _puntuacion;
}

unsigned Jugador::get_id()const{
    return id;
}
/**
 * @brief devuelve el alias del jugador
 * @return nickname , string
 */
std::string Jugador::get_nickName() const{
    return nickname;
}
/**
 * @brief devuelve la puntuacion del jugador
 * @return puntuacion , double
 */
double Jugador::get_puntuacion()const{
    return puntuacion;
}
/**
 * @brief establece los valores de un jugador todos los datos
 * @param _id identificador, unsigned
 * @param alias string
 * @param _puntuacion es 0 por defecto, el argumento puntuacion es un parametro opcional
 */
void Jugador::set_Jugador(long _id, const std::string &alias, double _puntuacion){
    id = _id;
    nickname = alias;
    puntuacion = _puntuacion;
}
