/*
 * Metodología de la Programación: Language1
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */


/**
 * This program reads from the stardard input, an integer n (number of elements) 
 * and a list of n pairs bigram-frequency. The pairs are stored in an array, 
 * and then it is sorted in decreasing order of frequency. After that, 
 * all the bigrams are changed to uppercase. The sorted array is finally shown 
 * in the stardard output. 
 * Running example:
 * > language1 < data/miniquijotebigrams.txt 
 */

#include <iostream>
#include <cstring>

using namespace std;

#include "ArrayBigramFreqFunctions.h"

int main(){

    //Declaration of variables for the main program
    const int NUM_MAX_BIGRAMS = 1000;
    int nElements;
    char text[3];
    int frequency;
    BigramFreq bigrams[NUM_MAX_BIGRAMS];

    //Input of number of Elements
    std::cin >> nElements;

    //Input of each bigram of frequency
    for (int i=0; i<nElements; i++){
        std::cin >> text;
        std::cin >> frequency;
        bigrams[i].setBigram(text);
        bigrams[i].setFrequency(frequency);
    }

    //Reading nElements and the capacity of the bigram of frequency
    readArrayBigramFreq(bigrams, NUM_MAX_BIGRAMS, nElements);

    //Sorting the array of Bigram of Frequency
    sortArrayBigramFreq(bigrams, nElements);
    
    //Capitalizing each Bigram of Frequency
    toUpperArrayBigramFreq(bigrams, nElements);
    
    //Priting each Bigram of Frequency
    printArrayBigramFreq(bigrams, nElements);
}