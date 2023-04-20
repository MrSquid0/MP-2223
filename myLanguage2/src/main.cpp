/*
 * Metodología de la Programación: Language2
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

#include <iostream>
#include "Language.h"

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> " << std::endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally the resulting Language is saved in an output file. The 
 * program must have at least an input file and an output file. 
 * The output Language will have as language identifier, the one of the first
 * file (<file1.bgr>). If an input file <file*.bgr> has a language identifier
 * different from the one of the first file (<file1.bgr>), then it will not
 * be included in the union.
 * Running example:
 * > language2 <file1.bgr> [<file2.bgr> ... <filen.bgr>] <outputFile.bgr> 
 */
int main(int argc, char* argv[]) {
    if (argc < 3){
        std::cout << showEnglishHelp;
        exit(1);
    }
    
    int numberOfLanguages = argc - 2;
    int readLanguages = 1; //Languages that have been read
    
    Language firstLanguage;
    firstLanguage.load(argv[1]); //Loads the first language
    std::string languageOfTheFirstFile = firstLanguage.getLanguageId();
    readLanguages++;
    
    Language fusion = firstLanguage;
    for (int i=2; readLanguages != numberOfLanguages; i++){
        Language nextLanguage;
        nextLanguage.load(argv[i]); //Loads every language
        //Check if the current languageId is equal to the first one
        if (nextLanguage.getLanguageId() != languageOfTheFirstFile){
            readLanguages++; //Current language is ignored
        }
        else {
            fusion.join(nextLanguage); //Current language is mixed in the fusion
            readLanguages++;
        }
    }
    
    //Save the languages fusion into a file
    fusion.save(argv[argc-1]);
}

