/** 
 * @file Bigram.cpp
 * @author Gonzalo José López Castilla <gonzalo0@correo.ugr.es>
 * 
 * Created on 12 March 2023, 10:53
 */

#include "Bigram.h"

Bigram::Bigram(const std::string& text){
    if (text.size() != 2){
        _text = "__";
        std::cerr << std::endl << "ERROR: el bigrama tiene que ser de 2 caracteres. ";
        exit(1);
    } else {
        _text = text;
    }
}

Bigram::Bigram(char first, char second) : Bigram(std::string(1, first) + std::string(1, second)){

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
    return _text.at(index);
}

char& Bigram::at(int index){
    if (index !=0 && index !=1){
        throw std::out_of_range("El índice " + std::to_string(index) + "está fuera de rango");
    }
    return _text.at(index);
}

bool isValidCharacter(char character, const std::string& validCharacters){
    bool isValid = false;
    for (int i=0; i<validCharacters.size(); i++){
        if (character == validCharacters[i])
            isValid = true;
    }
    return isValid;
}

void toUpper(Bigram &bigram){
    bigram.at(0) = toupper(bigram.at(0));
    bigram.at(1) = toupper(bigram.at(1));
}