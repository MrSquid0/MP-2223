#include "BigramFreq.h"

BigramFreq::BigramFreq(){
    _bigram = "__";
    _frequency = 0;
}

Bigram BigramFreq::getBigram() const{
    return _bigram;
}

int BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram (Bigram bigram){
    _bigram = bigram;
}

void BigramFreq::setFrequency (const int frequency){
    if (frequency < 0){
        throw std::out_of_range("La frequencia dada de " 
                + std::to_string(frequency) + " no puede ser negativa.");
    }  
    _frequency = frequency;
}

std::string BigramFreq::toString() const{
    std::string bigramWithFreq = "";
    
    bigramWithFreq += this->_bigram.toString();
    bigramWithFreq += " " + std::to_string(this->_frequency);
    
    return bigramWithFreq;
}