/*
 * Metodología de la Programación: Language3
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

#include "Language.h"
#include <cstring>

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
    double currentMaxDistance = language.getDistance(array[0]);
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
    if (operation = 'm'){ //If minimum distance
        returnValue = min;
    } else{ //If maximum distance
        returnValue = max;
    }
    return returnValue;
}

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc)
 */
void showEnglishHelp(std::ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << std::endl;
    outputStream << "language3 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << std::endl;
}

/**
 * This program reads an undefined number of Language objects from the set of
 * files passed as parameters to main(). All the Languages object, except the
 * first one, must be stored in a dynamic array of Language objects. Then,
 * for each Language in the dynamic array, this program prints to the
 * standard output the name of the file of that Language and the distance from
 * the first Language to the current Language.
 * Finally, the program should print in the standard output, the name of
 * the file with the Language with the minimum|maximum distance to the Language
 * of the first file and its language identifier.
 *
 * At least, two Language files are required to run this program.
 * Running example:
 * > language3 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>]
 */
int main(int argc, char* argv[]) {
    char operation = 'm'; // CALCULAR MIN DISTANCE;
    int first=0;
    int nFicherosAComparar;
    if (argc < 3) {
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    if (argv[1][0] == '-') {
        if (strcmp(argv[1], "-t") == 0) {
            if (strcmp(argv[2], "min") == 0) {
                // operation CALCULAR MIN DISTANCE
                operation = 'm';
            } else if (strcmp(argv[2], "max") == 0) {
                // operation CALCULAR MAX DISTANCE
                operation = 'M';
            } else {
                showEnglishHelp(std::cerr);
                return 1;
            }
            //
        } else {
            showEnglishHelp(std::cerr);
            return 1;
        }
        nFicherosAComparar = argc-4;
        first = 4;
    }
    else{
        
        nFicherosAComparar = argc-2;
        first = 2;
    }
    if(nFicherosAComparar<1){
        showEnglishHelp(std::cerr);
        return 1;
    }
    
    // Crear el array dinámico de Language con  nFicherosAComparar elementos
    // Reservamos memoria
    Language *array = new Language[nFicherosAComparar];
    
    // Leer el primer fichero
    Language firstLanguage;
    firstLanguage.load(argv[first-1]); //Loads the first language
    
    // Bucle para leer los nFicherosAComparar
    // Cargar con load() cada en uno en una posición del array dinámico
    for (int i=0; i<nFicherosAComparar; i++){
        Language nextLanguage;
        nextLanguage.load(argv[i+first]);
        array[i] = nextLanguage;
    }
    
    // Calcular la posición donde está el más cercano/lejano del primero fichero a
    // los del array
    int languageMinMax = posMinMaxLanguage(firstLanguage, array, 
            nFicherosAComparar, operation);
    
    // Mostrar la información adecuada
    for (int i=0; i<nFicherosAComparar; i++){
        std::cout << "Distance to " << argv[i+first] << ": " 
                << firstLanguage.getDistance(array[i]) << std::endl;
    }
    
    if (operation == 'm'){ //Operation by default
        std::cout << "Nearest language file: " << argv[languageMinMax+first] << 
                ". Identifier of the nearest language: " 
                << array[languageMinMax].getLanguageId() << std::endl;
    }else{
        std::cout << "Farthest language file: " << argv[languageMinMax+first] 
                << ". Identifier of the farthest language: " 
                << array[languageMinMax].getLanguageId() << std::endl;
    }
    
    //Liberar la memoria reservada
    for (int i=0; i<nFicherosAComparar; i++){
        delete [] array;
    }
}
