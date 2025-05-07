#include "GSenku.hpp"
#include "solucion.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// Pre: true
// Post: lee la configuración y el estado del tablero del fichero de configuración que se le pasa como argumento
//      inicializando tablero y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarTablero(const string nombreFichero, tpTablero &tablero){

    ifstream f;
    char estado;
    f.open(nombreFichero);
    if(f.is_open()){
        f >> tablero.nfils;
        f.ignore();
        f >> tablero.ncols;
        f.ignore();
        
        for(int i = 0; i < tablero.nfils; i++){
            for(int j = 0; j < tablero.ncols; j++){
                f >> estado;
                if(estado == '-'){
                    tablero.matriz[i][j] = NO_USADA; 
                                
                } else if(estado == 'x'){
                    tablero.matriz[i][j] = VACIA;
                    
                } else if(estado == 'o'){
                    tablero.matriz[i][j] = OCUPADA;
                    
                }  
                 
            }
            f.ignore();
            
        }
        f.close();
        return true;

    }  else {
        cerr << "No se ha podido abrir el fichero " << nombreFichero << endl;
        return false;
    }

}

// Pre: true 
// Post: lee los movimientos válidos del fichero que se le pasa como argumento 
//      inicializando la estructura y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarMovimientosValidos(const string nombreFichero, tpMovimientosValidos &movimientos){
    ifstream f;
    char estado;
    int cuenta = 0;

    f.open(nombreFichero);
    if(f.is_open()){

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                f >> estado;
                if(estado == '-'){
                    movimientos.validos[cuenta] = false;
                    cuenta++;
                } else if(estado == '+'){
                    movimientos.validos[cuenta] = true;
                    cuenta++;
                } else {
                   
                    continue;
                }

            }
            f.ignore();
        }
        f.close();
        return true;

    } else {
        cerr << "No se ha podido abrir el fichero " << nombreFichero << endl;
        return false;
    }

}

// Pre: tablero contiene el estado actual de la ejecución de la búsqueda de la solución
// Post: Se ha mostrado el tablero por pantalla
void mostrarTablero(const tpTablero &tablero){
    
    for(int i = 0;i < tablero.nfils;i++){
        for(int j = 0;j < tablero.ncols;j++){
            if(tablero.matriz[i][j] == NO_USADA){
                cout << "- ";
            }else if(tablero.matriz[i][j] == VACIA){
                cout << "x ";
            }else if(tablero.matriz[i][j] == OCUPADA){
                cout << "o ";
            }
        }
        cout << endl;
    }

}

// Pre: tablero contiene el estado inicial del que se parte para la búsqueda, 
//      movimientosValidos contiene los movimientos que están permitidos, 
//      solucionParcial contiene la solución actual como lista de movimientos, En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: solucionParcial contendrá la lista de movimientos completa (si no se llega a una solución, estará vacía, numMovs == 0)
//       Devuelve 1 si encuentra solución, -1 si no la encuentra.
int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo=0){

    tpPosicion posicion;
    //definir posicion inicial 
    tpMovimientoPieza movPieza;
    movPieza.origen = posicion;

    int sol = -1;

    for(int i = 1; i < 8; i++){

        if(movValidos.validos[i]){

            //logica que no se como hacer para discernir casos de manera que no ocupe 800 lineas

            if(comprobarPosicion(movPieza, solucionParcial)){

                sol = buscarSolucion(tablero, movValidos, solucionParcial, retardo);
                

            }
            
        }

    }

}


// Pre: listaMovimientos contiene la lista de movimientos con la solucion 
// Post: escribe la lista de movimientos en el fichero que se le pasa como argumento siguiendo el 
//      formato especificado en el guión (si está vacía, se escribe un -1 en el fichero)
//void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion); 


void comprobarLeerMovsValidos(const string nombreFichero, tpMovimientosValidos &movimientos){
    int cuenta = 0;
    for(int i = 0;i < 3;i++){
        for(int j = 0;j < 3; j++){
            if(i == 1 && j==1){
                cout << "  ";
            } else if(movimientos.validos[cuenta] == false){
                cout << "- ";
                cuenta++;
            }else if(movimientos.validos[cuenta] == true){
                cout << "+ ";
                cuenta++;
            }   
        }
        cout << endl;
    }
}

int main(){

    

    string nomTablero = "tableros_modelo/tableroRaroArriba.txt";
    string nombreMov = "movimientos/movimientosClasicos.txt";

    tpTablero tablero;
    

    tpMovimientosValidos movimientos;

    inicializarMovimientosValidos(nombreMov, movimientos);
    inicializarTablero(nomTablero, tablero);
    
    comprobarLeerMovsValidos(nombreMov, movimientos);
    mostrarTablero(tablero);
}
