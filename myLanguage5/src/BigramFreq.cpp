#include "BigramFreq.h"

BigramFreq::BigramFreq(){
    _bigram = "__";
    _frequency = 0;
}

const Bigram& BigramFreq::getBigram() const{
    return _bigram;
}

int BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram (const Bigram &bigram){
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

void BigramFreq::serialize(std::ostream& outputStream){
    // Serialize the bigram
    outputStream.write(reinterpret_cast<const char*>(&_bigram), sizeof(Bigram));
    
    // Serialize the frequency
    outputStream.write(reinterpret_cast<const char*>(&_frequency), sizeof(int));
}

void BigramFreq::deserialize(std::istream& inputStream){
    // Deserialize the bigram
    inputStream.read(reinterpret_cast<char*>(&_bigram), sizeof(Bigram));
    
    // Deserialize the frequency
    inputStream.read(reinterpret_cast<char*>(&_frequency), sizeof(int));    
}

std::ostream& operator<<(std::ostream &os, const BigramFreq &bigramFreq){
    os << bigramFreq.toString();
    return os;
}

std::istream& operator>>(std::istream &is, BigramFreq &bigramFreq){
    Bigram bigram;
    int frequency;
    
    is >> bigram >> frequency;
    
    bigramFreq.setBigram(bigram);
    bigramFreq.setFrequency(frequency);
    
    return is;
}

bool operator>(BigramFreq bigramFreq1, BigramFreq bigramFreq2){
    bool isGreater = false;
    if (bigramFreq1.getFrequency() > bigramFreq2.getFrequency()){
        isGreater = true;
    } else if (bigramFreq1.getFrequency() == bigramFreq2.getFrequency()){
        if (bigramFreq1.getBigram().getText() > bigramFreq2.getBigram().getText()){
            isGreater = true;
        }
    }
    return isGreater;
}

bool operator<(BigramFreq bigramFreq1, BigramFreq bigramFreq2){
    bool isLower = false;
    if (!(bigramFreq1 > bigramFreq2))
        isLower = true;
    return isLower;
}

bool operator==(BigramFreq bigramFreq1, BigramFreq bigramFreq2){
    bool isEqual = false;
    if (bigramFreq1.getBigram().getText() == bigramFreq2.getBigram().getText()){
        if (bigramFreq1.getFrequency() == bigramFreq2.getFrequency())
            isEqual = true;
    }
    return isEqual;
}

bool operator!=(BigramFreq bigramFreq1, BigramFreq bigramFreq2){
    bool isNotEqual = false;
    if (!(bigramFreq1 == bigramFreq2))
        isNotEqual = true;
    return isNotEqual;
        
}

bool operator<=(BigramFreq &bigramFreq1, BigramFreq bigramFreq2){
    bool isLowerOrEqual = false;
    if ((bigramFreq1 < bigramFreq2) || (bigramFreq1 == bigramFreq2))
        isLowerOrEqual = true;
    return isLowerOrEqual;
}

bool operator>=(BigramFreq bigramFreq1, BigramFreq bigramFreq2){
    bool isGreaterOrEqual = false;
    if ((bigramFreq1 > bigramFreq2) || (bigramFreq1 == bigramFreq2))
        isGreaterOrEqual = true;
    return isGreaterOrEqual;
}