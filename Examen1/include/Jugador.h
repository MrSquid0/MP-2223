/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.h
 * Author: sihamtabik
 *
 * Created on 8 de mayo de 2023, 11:19
 */

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>

class Jugador{
    unsigned id;
    std::string nickname;
    double puntuacion;
public:
    /**
     * @brief Constructor base
     */
    Jugador();
    Jugador(long _id);
    Jugador(long _id, const std::string &alias, double _puntuacion);

    /**
     * @brief Devuelve el id del jugador
     * @return nombre
     */
    unsigned get_id() const;
    /**
     * @brief Devuelve el alias  del jugador
     * @return string con el nickname
     */
    std::string get_nickName() const;
  
    /**
     * @brief Devuelve puntuacion  del jugador
     * @return puntuacion
    */
    double get_puntuacion() const;
    /**
     * @brief Actualiza los datos del jugador, si la longitud adecuada,
     *  en otro caso, no se actualiza
     * @param id, alias y puntuacion
     */
    void set_Jugador(long _id, const std::string &alias, double _puntuacion );

};
#endif /* JUGADOR_H */

