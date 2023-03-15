/*
 * Metodología de la Programación: Language0
 * Curso 2022/2023
 */

#include <iostream>
#include <string>
#include "Bigram.h"

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 2 de febrero de 2023, 12:23
 */


/**
 * This program reads a text (without spaces) with a undefined number of 
 * characters and a text with two characters (bigram). It finds the bigrams 
 * contained in the first text, storing them in an array of Bigram. 
 * After that, the bigrams of the array are shown in the standard output. 
 * Then it converts to uppercase the bigrams in the array that are equals to the 
 * bigram of the second text. Finally the bigrams of the array are shown again 
 * in the standard output. 
 * Running example:
 * > language0 < data/SimpleText.txt
 */
int main(int argc, char* argv[]) {
    // This string contains the list of characters that are considered as
    // valid within a word. The rest of characters are considered as
    // separators
    const std::string validCharacters = "abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
    
    std::string cadena1, cadena2; //cadena1 --> texto     cadena2 --> bigrama
    const int NUM_MAX_BIGRAMS = 1000;
    char first, second;
    int numBigrams = 0;
    Bigram bigrams[NUM_MAX_BIGRAMS];
    
    // Read a text and a bigram (text with two characters)
    //std::cout << "Inserta un texto y un bigrama: ";
    std::cin >> cadena1 >> cadena2;
    cadena2.at(0) = tolower(cadena2.at(0));
    cadena2.at(1) = tolower(cadena2.at(1));
    Bigram bigram(cadena2);
    
    // Find the bigrams in text and put them in an array of Bigrams
    if (cadena1.length() >= 2){
        first = cadena1.at(0);
        for (int i=1; i<cadena1.size(); i++){
            second = cadena1.at(i);
            first = tolower(first);
            second = tolower(second);
            if (isValidCharacter(first, validCharacters) && isValidCharacter(second, validCharacters)){
                bigrams[numBigrams] = Bigram(first, second);
                numBigrams++;
            }
            first = second;
        }
    }
   
    
    // Show the bigrams stored in the array
    std::cout << numBigrams << std::endl;
    for (int i=0; i<numBigrams; i++){
        std::cout << bigrams[i].toString() << std::endl;
    }
    
    // Convert to uppercase the bigrams in the array that are equals to input bigram
    for (int i=0; i<numBigrams; i++){
        if (bigrams[i].getText() == bigram.getText()){
            toUpper(bigrams[i]);
        }
    }
    
    
    // Show again the bigrams stored in the array
    std::cout << std::endl << numBigrams << std::endl;
    for (int i=0; i<numBigrams; i++){
        std::cout << bigrams[i].toString() << std::endl;
    }
}