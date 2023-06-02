/*
 * Metodología de la Programación: Language5
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
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";

Language::Language(){
    _languageId = "unknown";
    _size = 0;
    _vectorBigramFreq = 0;
}

Language::Language(int numberOfBigrams){
    if (numberOfBigrams < 0){
        throw std::out_of_range("El número de bigramas debe ser mayor que 0.");
    }
    _size = numberOfBigrams;
    _vectorBigramFreq = new BigramFreq[_size];
}


Language::Language(const Language& orig){
    allocate(orig.getSize());
    copy(orig);
}

Language::~Language(){
    deallocate();
}

Language& Language::operator=(const Language& orig){
    if (this != &orig){
        deallocate();
        allocate(orig.getSize());
        copy(orig);
    }
    return *this;
}

void Language::allocate(int numberOfBigrams) {
    _size = numberOfBigrams;
    _vectorBigramFreq = new BigramFreq[_size];
}

void Language::deallocate() {
    if (_vectorBigramFreq != 0){
        delete [] _vectorBigramFreq;
        _vectorBigramFreq = 0;
        _size = 0;
    }
}

void Language::copy(const Language &language) {
    _languageId = language.getLanguageId();
    for (int i=0; i<_size; i++){
        this->_vectorBigramFreq[i] = language.at(i);
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

const double Language::getDistance(const Language otherLanguage) const{
    if (this->getSize() == 0){
        throw std::invalid_argument("El primer language no tiene bigramas.");
    }
    
    double sum = 0; //Sum of positions in absolute value
    
    for (int i=0; i<this->getSize(); i++){
        //If bigram exists in otherLanguage, that is, if it's != -1
        int posOtherLanguage = otherLanguage.findBigram((this->at(i)).getBigram());
        //If bigram doesn't exist, we assign to the 
        //ranking the size of first language
        if (posOtherLanguage == -1)
            posOtherLanguage = this->getSize();

        sum += abs(i-posOtherLanguage);
    }
    double distance = sum / (this->getSize() * this->getSize());
    return distance;
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
            if ((*this)[i].getFrequency() <= (*this)[j].getFrequency()){
                if ((*this)[i].getFrequency() == (*this)[j].getFrequency()){
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
        std::cout << *this;
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
        deallocate();
        std::cin >> *this;
        
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
        Language currentLanguage = new Language(*this);
        deallocate();
        allocate(currentLanguage.getSize()+1);
        for (int i=0; i<currentLanguage.getSize()-1; i++){
            (*this)[i] = currentLanguage[i];
        }
        (*this)[_size-1] = bigramFreq;
        delete currentLanguage;
        currentLanguage = 0;
    }
}

Language Language::operator+=(Language language){
    if (this != &language){
        for (int i=0; i<language.getSize(); i++)
            this->append(language.at(i));
        
        this->sort();
    }
    return *this;
}

const BigramFreq& Language::operator[](int index) const{
    return this->at(index);
}

BigramFreq& Language::operator[](int index){
    return this->at(index);
}

std::ostream& operator<<(std::ostream &os, const Language &language){
    os << language.toString();
    return os;
}

std::istream& operator>>(std::istream &is, Language &language){
    int numberOfBigramFreq;
    std::string languageId;
    is >> languageId >> numberOfBigramFreq;
    
    language = Language(numberOfBigramFreq);
    language.setLanguageId(languageId);
    
    for (int i=0; i<numberOfBigramFreq; i++){
        std::string textBigram;
        is >> textBigram;
        Bigram bigramInput(textBigram);
        int frequencyInput;
        is >> frequencyInput;
        language.at(i).setBigram(bigramInput);
        language.at(i).setFrequency(frequencyInput);
    }    
    
    return is;
}