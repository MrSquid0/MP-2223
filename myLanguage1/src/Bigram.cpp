/** 
 * @file Bigram.cpp
 * @author Gonzalo José López Castilla <gonzalo0@correo.ugr.es>
 * 
 * Created on 12 March 2023, 10:53
 */

#include "Bigram.h"
#include <cstring>

Bigram::Bigram(const std::string& text){
    if (text.size() != 2){
        _text[0] = '_';
        _text[1] = '_';
        _text[2] = '\0';
        std::cerr << std::endl << "ERROR: el bigrama tiene que ser de 2 caracteres. ";
        exit(1);
    } else {
        strcpy(_text, text.c_str());
        _text[2] = '\0';
    }
}

Bigram::Bigram(char first, char second) : Bigram(std::string(1, first) + std::string(1, second)){

}

Bigram::Bigram(const char text[]){
    int longitud = 0;
    for (int i=0; text[i] != '\0'; i++){
        longitud++;
    }
    
    if (longitud != 2){
        _text[0] = '_';
        _text[1] = '_';
        _text[2] = '\0';
        std::cerr << std::endl << "ERROR: el bigrama tiene que ser de 2 caracteres. ";
        exit(1);
    } else {
        for (int i=0; i<longitud; i++){ //longitud es 2
            _text[i] = text[i];
        }
        _text[2] = '\0';
    }
}

std::string Bigram::getText() const{
    return _text;
}

std::string Bigram::toString() const{
    return std::string(1,at(0)) + std::string(1,at(1));
}

const char& Bigram::at(int index) const{
    if (index !=0 && index !=1){
        throw std::out_of_range("El índice " + std::to_string(index) + " está fuera de rango");
    }
    return _text[index];
}

char& Bigram::at(int index){
    if (index !=0 && index !=1){
        throw std::out_of_range("El índice " + std::to_string(index) + "está fuera de rango");
    }
    return _text[index];
}

bool isValidCharacter(char character, const std::string& validCharacters){
    bool isValid = false;
    for (int i=0; i<validCharacters.size(); i++){
        if (character == validCharacters[i])
            isValid = true;
    }
    return isValid;
}

void Bigram::toUpper(){
    this->at(0) = toupper(this->at(0));
    this->at(1) = toupper(this->at(1));
}