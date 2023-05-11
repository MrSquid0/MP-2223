/* Se trata de gestionar la información de jugadores de videojuegos, esto es, 
 * vectores de jugadores y hacer operaciones con ellos.
 * Cada jugador tiene un id, un nickname, y una puntuacion obtenida.
 * Con la ayuda de la clase Jugador ya definida se pide:
 * crear un vector de jugadores, encuentro1, con el tamanio necesario para 
 * leer y cargar en él una serie de jugadores (lectura desde el teclado)
 * dimensionar otro vector de jugadores, encuentro2, en las mismas condiciones.
 * Se quiere obtener un vector final con los jugadores que han participado en 
 * AMBOS encuentros y guardar la máxima puntuacion obtenida en los dos encuentros.  
 * 
 * Para la lectura de los datos de un encuentro, se leen los datos de un jugador
 *  mientras el id no sea -1, condicion de parada,
 * Se ha preparado el fichero jugadores.dat con los datos siguientes:

1 Xman 10.5
3 dragon 30.2
5 covid19 13.2
8 snack 18.1
9 aceituno 15.3
12 protozoo 21.5
-1
3 dragon 29.8
4 moskito 33.2
9 aceituno 40.7
11 peligro 39.9
2 oreja 13.8
-1

 *****  Resultado:

Vector de jugadores en los 2 encuentros 
3->(dragon,30.2),
9->(aceituno,40.7),

*/

/*
Tareas a realizar
 * 
1. Escribe tu nombre y apellidos en el fichero fuente, junto al token // Alumno: 
2. Completar las funciones:
reservarM
liberarM
agnadeJugador
interseccionEncuentros
completar el main
definir cualquier funcion adicional que considere necesaria

3. Revisar las cabeceras de las funciones externas el número y tipos son los correctos.
La forma de pasar los argumentos (por valor, referencia etc.) lo decides tu, constante o no
*/

// Alumno: Lopez Castilla Gonzalo Jose

#include <cstdlib>
#include <iostream>
#include <string>
#include "FuncionesExternas.h"

using namespace std;




int main(int argc, char** argv)  {

    Jugador *encuentro1 = 0; // vector de jugadores del primer encuentro
    Jugador *encuentro2 = 0; // vector de jugadores del segundo encuentro
    Jugador *participantes = 0; //vector de jugadores que han participado en
                            //ambos encuentros
    
    int nutil1 = 0, nutil2 = 0, nparticipantes = 0; // longitudes respectivas
    
    //Lee el array encuentro1
    leerArray(encuentro1, nutil1);
    
    //Lee el array encuentro2
    leerArray(encuentro2, nutil2);
     
    //  muestra los datos de encuentro 1
    cout << "Vector de jugadores del encuentro 1 " << endl;   
    imprimirVector(encuentro1, nutil1);

    //   muestra los datos de encuentro2
    cout << "Vector de jugadores del encuentro 2 " << endl;
    imprimirVector(encuentro2, nutil2);
    
    // encuentra los jugadores que han participado en ambos encuentros 
    interseccionEncuentros(encuentro1, nutil1, encuentro2, nutil2, participantes, nparticipantes);
    
    cout << "Vector de jugadores en los 2 encuentros " << endl;
    imprimirVector(participantes, nparticipantes);

    // liberar espacio si procede
    liberarM(encuentro1);
    liberarM(encuentro2);
    liberarM(participantes);
    
    return 0;
}
