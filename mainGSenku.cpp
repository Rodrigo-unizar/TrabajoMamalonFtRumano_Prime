#include <iostream>
#include <fstream>
#include "GSenku.hpp"


using namespace std;

int main(int argc, char* argv[]){

    string carpetaTab = "tableros_modelo/";
    string carpetaMov = "movimientos/"; 
    string FicheroTablero;
    string FicheroMovs;
    int retardo;
    string FicheroSalida = "solucion.txt";

    FicheroTablero = argv[1];
    FicheroMovs = argv[2];
    retardo = atoi(argv[3]);
    if(argc == 5){ 
        FicheroSalida = argv[4];
    }

    tpTablero tablero;
    tpListaMovimientos solParcial;
    tpMovimientosValidos movimientos;

    string nomTablero = carpetaTab + FicheroTablero;
    string nombreMov = carpetaMov + FicheroMovs;

    inicializarMovimientosValidos(nombreMov, movimientos);
    inicializarTablero(nomTablero, tablero);
    mostrarTablero(tablero);
    buscaSolucion(tablero, movimientos, solParcial, retardo);
    escribeListaMovimientos(FicheroSalida, solParcial);

}