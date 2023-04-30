/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */

#include "Language.h"

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

Language::Language(){
    _languageId = "unknown";
    _size = 0;
}

Language::Language(int numberBigrams){
    if (numberBigrams > DIM_VECTOR_BIGRAM_FREQ || numberBigrams < 0){
        throw std::out_of_range("El número de bigramas debe ser menor que "
                + std::to_string(DIM_VECTOR_BIGRAM_FREQ) + " y mayor que 0.");
    }    
    
    Language language;
    _size = numberBigrams;
    
    for (int i=0; i<numberBigrams; i++){
        _vectorBigramFreq[i] = BigramFreq();
    }
}

const std::string& Language::getLanguageId() const{
    return _languageId;
}

void Language::setLanguageId(const std::string& id){
    _languageId = id;
}

const BigramFreq& Language::at(int index) const{
    if (index >= _size || index < 0){
        throw std::out_of_range("El índice no es válido");
    }
    return _vectorBigramFreq[index];
}

BigramFreq& Language::at(int index){
    if (index >= _size || index < 0){
        throw std::out_of_range("El índice no es válido");
    }
    
    return _vectorBigramFreq[index];    
}

int Language::getSize() const{
    return _size;
}

int Language::findBigram(const Bigram& bigram) const{
    int value = -1;
    for (int i=0; i<_size; i++){
        if (bigram.getText() == _vectorBigramFreq[i].getBigram().getText()){
            value = i;
        }
    }
    return value;
}

std::string Language::toString() const{
    std::string content;
    
    content = MAGIC_STRING_T + "\n";
    content += _languageId + "\n";
    content += std::to_string(_size) + "\n";
    
    for (int i=0; i<_size; i++){
        content += _vectorBigramFreq[i].getBigram().getText() + " " +
                std::to_string(_vectorBigramFreq[i].getFrequency()) + "\n";
    }
    return content;
}

void Language::swapElementsArrayBigramFreq(BigramFreq array[], int nElements, 
        int first, int second){
    if (first >= nElements || second >= nElements){
        throw std::out_of_range("El elemento primero " 
                + std::to_string (first) + " y segundo " +
                std::to_string(second) + " tienen que ser menor"
                " a " + std::to_string(nElements));        
    }
    
    BigramFreq arrayAuxiliar = array[first];
    array[first] = array[second];
    array[second] = arrayAuxiliar;
}

char Language::sortDraw(const BigramFreq bigram[], const int i, const int j){
    char chosenLetter;
    if (bigram[i].getBigram().getText() >= bigram[j].getBigram().getText()){
        chosenLetter = 'i';
    } else {
        chosenLetter = 'j';
    }
    return chosenLetter;
}

void Language::sort(){
    for (int i=0; i<_size; i++){
        for (int j=i+1; j<_size; j++){
            if (_vectorBigramFreq[i].getFrequency() <= _vectorBigramFreq[j].getFrequency()){
                //E
                if (_vectorBigramFreq[i].getFrequency() == _vectorBigramFreq[j].getFrequency()){
                    char swap = sortDraw(_vectorBigramFreq, i, j);
                    if (swap == 'i'){
                        swapElementsArrayBigramFreq(_vectorBigramFreq, _size, i, j);
                    }
                }
                else {
                    swapElementsArrayBigramFreq(_vectorBigramFreq, _size, i, j);
                }
            }
        }
    }
}

void Language::save(const char fileName[]) const{
    //Create the given file
    std::ofstream language(fileName);
    
    if (language){
        language << this->toString();
        if (!language){
        throw std::ios_base::failure(string("No se pudo escribir "
                "en el archivo ") + fileName);
        }
        language.close();
    }else{
        throw std::ios_base::failure(string("No se pudo abrir "
                "el archivo ") + fileName);
    }
}

void Language::load(const char fileName[]){
    std::fstream language;
    language.open(fileName);
    
    if (language){
        std::string magicString;
        language >> magicString;
        if (magicString != MAGIC_STRING_T){
            throw std::invalid_argument("La primera línea "
                    "del documento no es válida. No es el "
                    "formato de un fichero language.");
        }
        language >> this->_languageId;
        language >> this->_size;
        
        for (int i=0; i<_size; i++){
            std::string textBigram;
            language >> textBigram;
            Bigram bigramInput(textBigram);
            int frequencyInput;
            language >> frequencyInput;
            _vectorBigramFreq[i].setBigram(bigramInput);
            _vectorBigramFreq[i].setFrequency(frequencyInput);
        }
        
        if (!language){
        throw std::ios_base::failure(string("No se pudo escribir "
                "en el archivo ") + fileName);
        }
        language.close();
    }else{
        throw std::ios_base::failure(string("No se pudo abrir "
                "el archivo ") + fileName);
    }
    
}

void Language::append(const BigramFreq& bigramFreq){
    int value = findBigram(bigramFreq.getBigram());
    if (value != -1){ //If the bigram exists
        int newFrequency = _vectorBigramFreq[value].getFrequency() 
        + bigramFreq.getFrequency();
        
        _vectorBigramFreq[value].setFrequency(newFrequency);
    } else { //If the bigram doesn't exist
        if (_size == DIM_VECTOR_BIGRAM_FREQ){ //If array is full
            throw std::out_of_range("El array está lleno.");
        }
        _vectorBigramFreq[_size] = bigramFreq;
        _size++;
    }
}

void Language::join(const Language& language){
    for (int i=0; i<language.getSize(); i++){
        this->append(language.at(i));
    }
    this->sort();
}