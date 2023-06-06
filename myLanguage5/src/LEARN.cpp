#include <iostream>
#include "BigramCounter.h"
#include <vector>

/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
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
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << std::endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << std::endl;
    outputStream << std::endl;
    outputStream << "Parameters:" << std::endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << std::endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << std::endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << std::endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << std::endl;
}

/**
 * Checks if a text file has the correct extension (.txt)
 * @param filename The std::string filename to be checked
 */

bool hasTxtExtension(const std::string& filename) {
    bool isTxtFormat = false;
    // Get the position of the last period in the file name
    std::size_t dotPos = filename.find_last_of(".");
    if (dotPos == std::string::npos) {
        return false; // There is no extension in the file name
    }

    // Get file extension
    std::string extension = filename.substr(dotPos + 1);
    if (extension == "txt")
        isTxtFormat = true;
    
    return isTxtFormat;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

int main(int argc, char* argv[]) {
    //Default values
    std::string mode = "-t";
    std::string languageId = "unknown";
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
        } else if (arg == "-l") {
            i++;
            if (i < argc) {
                languageId = argv[i];
            }
        } else if (arg == "-o") {
            i++;
            if (i < argc) {
                outputFile = argv[i];
            }
        } else {
            if (hasTxtExtension(arg)) {
                inputFiles.push_back(arg);
            } else {
                showEnglishHelp(std::cerr);
                return 1;
            }
        }
    }

    // Verify that at least one .txt file has been provided
    if (inputFiles.empty()) {
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    // Create a BigramCounter object
    BigramCounter bCounter;
    
    // Calculate all the frequencies of each .txt file and insert into bCounter
    for (int i=0; i<inputFiles.size(); i++){
        bCounter.calculateFrequencies(inputFiles[i]);
    }
    
    // Transform the BigramCounter object into a language object 
    // and assign the languageId
    Language languageObject = bCounter.toLanguage();
    languageObject.setLanguageId(languageId);
    
    // Save the language object into a .bgr file
    languageObject.save(outputFile.c_str());
}