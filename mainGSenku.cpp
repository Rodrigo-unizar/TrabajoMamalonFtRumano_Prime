/*Autores:  Razvan Ghita Calangiu 927460
*           Rodrigo Herce Alonso 935413
*/         

#include <iostream>
#include <fstream>
#include "GSenku.hpp"

using namespace std;

int main(int argc, char* argv[]){

    string carpetaTab = "tableros_modelo/";
    string carpetaMov = "movimientos/"; 
    string FicheroTablero;
    string FicheroMovs;
    int retardo = -1;
    string FicheroSalida = "solucion";
    string txt = ".txt";

    FicheroTablero = argv[1];
    FicheroMovs = argv[2];
    retardo = atoi(argv[3]);
    if(argc == 5){ 
        FicheroSalida = argv[4];
    }

    tpTablero tablero;
    tpListaMovimientos solParcial;
    tpMovimientosValidos movimientos;

    string nomTablero = carpetaTab + FicheroTablero + txt;
    string nombreMov = carpetaMov + FicheroMovs + txt;
    FicheroSalida = FicheroSalida + txt;

    inicializarMovimientosValidos(nombreMov, movimientos);
    inicializarTablero(nomTablero, tablero);
    mostrarTablero(tablero);
    buscaSolucion(tablero, movimientos, solParcial, retardo);
    escribeListaMovimientos(FicheroSalida, solParcial);

}