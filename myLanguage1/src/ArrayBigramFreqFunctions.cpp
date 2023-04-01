#include "ArrayBigramFreqFunctions.h"

void readArrayBigramFreq(const BigramFreq array[], int dim, int &nElements){
    if (nElements > dim){
        nElements = dim;
    }
    
    if (nElements < 0){
        nElements = 0;
    }
}

void printArrayBigramFreq(const BigramFreq array[], int nElements){
    std::cout << nElements << std::endl;
    for (int i=0; i<nElements; i++){
        std::cout << array[i].getBigram().toString() << " " 
                << std::to_string(array[i].getFrequency()) << std::endl;
    }
}

void swapElementsArrayBigramFreq(BigramFreq array[], int nElements, 
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

char sortDraw(const BigramFreq bigram[], const int i, const int j){
    char chosenLetter;
    if (bigram[i].getBigram().getText() >= bigram[j].getBigram().getText()){
        chosenLetter = 'i';
    } else {
        chosenLetter = 'j';
    }
    return chosenLetter;
}

/*
char sortDraw(BigramFreq bigram[], const int i, const int j){
    if (bigram[i].getBigram().at(0) >= bigram[j].getBigram().at(0)){
        if (bigram[i].getBigram().at(0) == bigram[j].getBigram().at(0)){
            if (bigram[i].getBigram().at(1) >= bigram[j].getBigram().at(1)){
                return 'i';
            } else{
                return 'j';
            }
        } else {
            return 'i';
        }
    } else {
        return 'j';
    }
}*/

void sortArrayBigramFreq(BigramFreq array[], int nElements){
    for (int i=0; i<nElements; i++){
        for (int j=i+1; j<nElements; j++){
            if (array[i].getFrequency() <= array[j].getFrequency()){
                //E
                if (array[i].getFrequency() == array[j].getFrequency()){
                    char swap = sortDraw(array, i, j);
                    if (swap == 'i'){
                        swapElementsArrayBigramFreq(array, nElements, i, j);
                    }
                }
                else {
                    swapElementsArrayBigramFreq(array, nElements, i, j);
                }
            }
        }
    }
}

void toUpperArrayBigramFreq(BigramFreq array[], int nElements){
    for (int i=0; i<nElements; i++){
        Bigram bigram = array[i].getBigram();
        bigram.toUpper();
        array[i].setBigram(bigram);
    }
}