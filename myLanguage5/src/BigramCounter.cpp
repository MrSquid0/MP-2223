/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 11:00
 */

#include "BigramCounter.h"

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(std::string validChars){
    _validCharacters = validChars;
    _frequency = new int*[_validCharacters.length()]; //Allocating rows
    for (int i = 0; i < _validCharacters.length(); ++i) {
        _frequency[i] = new int[_validCharacters.length()]; //Allocating columns
    }
    
    //Initiliaze to 0 each element of the matrix
    for (int i=0; i<_validCharacters.length(); i++){
        for (int j=0; j<_validCharacters.length(); j++){
            _frequency[i][j] = 0;
        }
    }
}

BigramCounter::BigramCounter(const BigramCounter &orig){
    allocate(orig._validCharacters.length());
    copy(orig);
}

void BigramCounter::allocate(const int rowsAndColumns) {
    // Allocate memory for rows
    _frequency = new int*[rowsAndColumns];

    // Allocate memory for columns of each row
    for (int i = 0; i < rowsAndColumns; ++i) {
        _frequency[i] = new int[rowsAndColumns];
    }
}

void BigramCounter::deallocate() {
    if (_frequency != 0){
        for (int i = 0; i < _validCharacters.length(); ++i)
            delete[] _frequency[i];
        delete[] _frequency;
        _frequency = 0;
    }
}

void BigramCounter::copy(const BigramCounter &bigramCounter){
    _validCharacters = bigramCounter._validCharacters;
    
    for (int i = 0; i < _validCharacters.length(); ++i) {
        for (int j = 0; j < _validCharacters.length(); ++j) {
            _frequency[i][j] = bigramCounter._frequency[i][j];
        }
    }
}

BigramCounter::~BigramCounter(){
    deallocate();
}

const int BigramCounter::getSize(){
    return _validCharacters.length();
}

int BigramCounter::getNumberActiveBigrams(){
    int activeBigrams = 0;
    
    for (int i=0; i<_validCharacters.length(); i++){
        for (int j=0; j<_validCharacters.length(); j++){
            if (_frequency[i][j] > 0)
                activeBigrams++;
        }
    }
    
    return activeBigrams;
}

bool BigramCounter::setFrequency(Bigram bigram, int frequency){
    bool found = false;
    
    std::size_t firstPosition = _validCharacters.find(bigram[0]);
    std::size_t secondPosition = _validCharacters.find(bigram[1]);
    
    if ((firstPosition && secondPosition) != std::string::npos){
        found = true;
        _frequency[firstPosition][secondPosition] = frequency;
    }
    return found;
}

void BigramCounter::increaseFrequency(Bigram bigram, int frequency){
    if (frequency == 0)
        frequency = 1;
    
    std::size_t firstPosition = _validCharacters.find(bigram[0]);
    std::size_t secondPosition = _validCharacters.find(bigram[1]);
    
    if ((firstPosition && secondPosition) != std::string::npos)
        _frequency[firstPosition][secondPosition] += frequency;
    else
        throw std::invalid_argument("El bigrama proporcionado no es válido.");
}

BigramCounter& BigramCounter::operator=(BigramCounter &orig){
    if (this != &orig){
        deallocate();
        allocate(orig.getSize());
        copy(orig);
    }
    return *this;   
}

BigramCounter& BigramCounter::operator+=(BigramCounter rhs){
    if (this != &rhs){
        for (int i=0; i<this->getSize(); i++){
            for (int j=0; j<this->getSize(); j++){
                Bigram bigram(rhs._validCharacters[i], rhs._validCharacters[j]);
                this->increaseFrequency(bigram, rhs(i,j));
            }
        }
    }
    return *this;
}

bool BigramCounter::calculateFrequencies(std::string fileName){
    bool fileRead = false;
    
    std::fstream bCounter;
    bCounter.open(fileName);
    
    if (bCounter){
        fileRead = true;
        char currentCharacter;
        char previousChar;
        bool primeraVez = true;
        while (bCounter.get(currentCharacter)) {
            if ((isValidCharacter(currentCharacter, _validCharacters)) && 
                    (isValidCharacter(previousChar, _validCharacters))){
                if (!primeraVez){
                    Bigram bigram(previousChar, currentCharacter);
                    this->increaseFrequency(bigram);
                }
            }
            previousChar = currentCharacter;
            primeraVez = false;
        }
        bCounter.close();
    }else{
        throw std::ios_base::failure(std::string("No se pudo abrir "
                "el archivo ") + fileName);
    }
    
    return fileRead;
}

Language BigramCounter::toLanguage(){
    Language language(getNumberActiveBigrams());
    
    int indiceObjetoLanguage=0;
    
    while (getNumberActiveBigrams() != indiceObjetoLanguage){
        for (int i=0; i<getSize(); i++){
            for (int j=0; j<getSize(); j++){
                if (_frequency[i][j] > 0){
                    Bigram bigram(_validCharacters[i], _validCharacters[j]);
                    BigramFreq bigramFreq;
                    bigramFreq.setBigram(bigram);
                    bigramFreq.setFrequency(_frequency[i][j]);
                    language.at(indiceObjetoLanguage) = bigramFreq;
                    indiceObjetoLanguage++;
                }
            }
        }
    }
    language.sort();
    
    return language;
}

const int BigramCounter::operator()(int row, int column) const{
    return _frequency[row][column];
}

int BigramCounter::operator()(int row, int column){
    return _frequency[row][column];
}