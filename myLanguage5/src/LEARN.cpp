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


bool hasTxtExtension(const std::string& filename) {
    bool isTxtFormat = false;
    // Obtener la posición del último punto en el nombre del archivo
    std::size_t dotPos = filename.find_last_of(".");
    if (dotPos == std::string::npos) {
        return false; // No hay extensión en el nombre del archivo
    }

    // Obtener la extensión del archivo
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
    std::string mode = "-t"; // Valor por defecto
    std::string language = "unknown"; // Valor por defecto
    std::string outputFile = "output.bgr"; // Valor por defecto
    std::vector<std::string> inputFiles;

    // Verificar que se hayan proporcionado suficientes argumentos
    if (argc < 2) {
        showEnglishHelp(std::cerr);
        return 1;
    }

    // Procesar los argumentos de línea de comandos
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-t" || arg == "-b") {
            mode = arg;
        } else if (arg == "-l") {
            i++;
            if (i < argc) {
                language = argv[i];
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

    // Verificar que se haya proporcionado al menos un archivo .txt
    if (inputFiles.empty()) {
        showEnglishHelp(std::cerr);
        return 1;
    }

    // Imprimir los valores de los parámetros
    std::cout << "Modo: " << mode << std::endl;
    std::cout << "Idioma: " << language << std::endl;
    std::cout << "Archivo de salida: " << outputFile << std::endl;
    std::cout << "Archivos de entrada: ";
    
    for (int i=0; i<inputFiles.size(); i++){
        std::cout << inputFiles[i] << " ";
    }
    std::cout << std::endl;

    // Resto del código del programa...

    return 0;
}