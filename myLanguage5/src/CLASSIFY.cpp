#include <iostream>
#include "BigramCounter.h"
#include <vector>

/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 29 January 2023, 11:00
 */


/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */

void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << std::endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << std::endl;
    outputStream << std::endl;
}

/**
 * Checks if a language file has the correct extension (.bgr or .txt)
 * @param filename The std::string filename to be checked
 * @param expectedExtension The std::string extension to be checked
 * @return true if the extension of the file is expectedExtension; 
 * false otherwise
 */
bool hasExpectedExtension(const std::string& filename, const std::string& expectedExtension) {
    bool isExpectedExtension = false;
    std::size_t dotPos = filename.find_last_of(".");
    if (dotPos != std::string::npos) {
        std::string extension = filename.substr(dotPos + 1);
        if (extension == expectedExtension)
            isExpectedExtension = true;
    }
    return isExpectedExtension;
}

/**
 * It returns the index of the array that the distance is the nearest
 * or the farthest to the first language.
 * @param language The first language given
 * @param array[] The array of languages given (not the first one included)
 * @param nElements The number of elements of the array
 * @param operation The operation to be done (minimum or maximum distance)
 */
int posMinMaxLanguage(const Language& language, const Language array[],
                      int nElements, char operation ){
    int min = 0, max = 0;
    double currentMinDistance = language.getDistance(array[0]);
    double currentMaxDistance = currentMinDistance;
    for (int i=1; i<nElements; i++){
        double currentDistance = language.getDistance(array[i]);
        if (currentDistance < currentMinDistance){
            min = i;
            currentMinDistance = currentDistance;
        }
        
        if (currentDistance > currentMaxDistance){
            max = i;
            currentMaxDistance = currentDistance;
        }
    }
    
    int returnValue;
    if (operation == 'm'){ //If minimum distance
        returnValue = min;
    } else{ //If maximum distance
        returnValue = max;
    }
    return returnValue;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */


int main(int argc, char* argv[]) {
    // Checks that enough arguments have been supplied
    if (argc < 3) {
        showEnglishHelp(std::cerr);
        return 1;
    }

    // Gets the name of the text file
    std::string textFile = argv[1];

    // Checks the extension of the text file
    if (!hasExpectedExtension(textFile, "txt")) {
        showEnglishHelp(std::cerr);
        return 1;
    }

    // Gets the names of the language files
    std::vector<std::string> languageFiles;
    for (int i = 2; i < argc; i++) {
        std::string langFile = argv[i];

        // Checks the extension of the language file
        if (!hasExpectedExtension(langFile, "bgr")) {
            showEnglishHelp(std::cerr);
            return 1;
        }

        languageFiles.push_back(langFile);
    }
    
    // Create a BigramCounter object
    BigramCounter bCounter;
    
    // Calculate all the frequencies of each .txt file and insert into bCounter
    for (int i=0; i<languageFiles.size(); i++){
        bCounter.calculateFrequencies(languageFiles[i]);
    }
    
    // Transform the BigramCounter object into a Language object 
    // and assign the languageId
    Language languageObject = bCounter.toLanguage();
    languageObject.setLanguageId("unknown");
    
    // Create the dynamic array of Language with languageFiles.size() Elements
    // Allocate memory
    Language *array = new Language[languageFiles.size()];
    
    // Reads the rest of language files and loads them into the dynamic array
    for (int i=0; i<languageFiles.size(); i++)
        array[i].load(languageFiles[i].c_str());
    
    std::cout << array[0];
    
    // Calculate the position where the closest of the first Language is
    int languageMinMax = posMinMaxLanguage(languageObject, array, 
            languageFiles.size(), 'm');
    
    // Assigns the correct language to the Language object
    languageObject.setLanguageId(array[languageMinMax].getLanguageId());
    
    // Prints to the terminal
    std::cout << "Final decision: language " 
            << languageObject.getLanguageId() << " with a distance of "  
            << languageObject.getDistance(array[languageMinMax]) << std::endl;
    
    //Deallocate dynamic memory
    delete [] array;
    array = 0;

    return 0;
}