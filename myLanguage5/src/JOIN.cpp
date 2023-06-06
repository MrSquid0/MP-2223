#include <iostream>
#include "BigramCounter.h"
#include <vector>

/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
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
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << std::endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << std::endl;
    outputStream << std::endl;
    outputStream << "Parameters:" << std::endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << std::endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << std::endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << std::endl;
}

/**
 * Checks if a language file has the correct extension (.bgr)
 * @param filename The std::string filename to be checked
 * @return true if the extension of the file is .bgr; false otherwise
 */

bool hasBgrExtension(const std::string& filename) {
    bool isBgrFormat = false;
    // Get the position of the last period in the file name
    std::size_t dotPos = filename.find_last_of(".");
    if (dotPos == std::string::npos) {
        return false; // There is no extension in the file name
    }

    // Get file extension
    std::string extension = filename.substr(dotPos + 1);
    if (extension == "bgr")
        isBgrFormat = true;
    
    return isBgrFormat;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an output file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char* argv[]) {
    //Default values
    std::string mode = "-t";
    std::string outputFile = "output.bgr";
    std::vector<std::string> inputFiles;

    // Check that enough arguments have been supplied
    if (argc < 2) {
        showEnglishHelp(std::cerr);
        return 1;
    }

    // Process command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-t" || arg == "-b") {
            mode = arg;
        } else if (arg == "-o") {
            i++;
            if (i < argc) {
                if (hasBgrExtension(argv[i]))
                    outputFile = argv[i];
                else
                    showEnglishHelp(std::cerr);
            }
        } else {
            if (hasBgrExtension(arg)) {
                inputFiles.push_back(arg);
            } else {
                showEnglishHelp(std::cerr);
                return 1;
            }
        }
    }

    // Verify that at least one .bgr file has been provided
    if (inputFiles.empty()) {
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    int readLanguages = 0; //Languages that have been read, one (the first)
                           //by default
    
    Language firstLanguage;
    firstLanguage.load(inputFiles[0].c_str()); //Loads the first language
    std::string languageOfTheFirstFile = firstLanguage.getLanguageId();
    readLanguages++;
    
    Language fusion = firstLanguage;
    for (int i=1; i<inputFiles.size(); i++){
        Language nextLanguage;
        nextLanguage.load(inputFiles[i].c_str()); //Loads every language
        
        //Checks if the current languageId is equal to the first one
        if (nextLanguage.getLanguageId() == languageOfTheFirstFile){
            fusion += nextLanguage; //Current language is mixed in the fusion
        }
    }
    
    //Save the languages fusion into a file
    fusion.save(outputFile.c_str());
    
    return 0;
}