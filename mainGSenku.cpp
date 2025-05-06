#include "GSenku.hpp"
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
        f >> tablero.ncols;

        for(int i = 0; i < tablero.nfils;i++){
            for(int j = 0; j < tablero.ncols;j++){
                f.get(estado);
                if(estado == '-'){
                    tablero.matriz[i][j] = NO_USADA;
                } else if(estado == 'x'){
                    tablero.matriz[i][j] = VACIA;
                } else if(estado == 'o'){
                    tablero.matriz[i][j] = OCUPADA;
                }else{
                    f.close();
                    return false;
                }
            }
        }

    }else{
        cerr << "No se ha podido abrir el fichero " << nombreFichero << endl;
        return false;
    }

    f.close();
    return true;
}

// Pre: true 
// Post: lee los movimientos válidos del fichero que se le pasa como argumento 
//      inicializando la estructura y devolviendo true si todo ha ido bien y false si ha habido algún error
bool inicializarMovimientosValidos(const string nombreFichero, tpMovimientosValidos &movimientos);

// Pre: tablero contiene el estado actual de la ejecución de la búsqueda de la solución
// Post: Se ha mostrado el tablero por pantalla
void mostrarTablero(const tpTablero & tablero){
    
}

// Pre: tablero contiene el estado inicial del que se parte para la búsqueda, 
//      movimientosValidos contiene los movimientos que están permitidos, 
//      solucionParcial contiene la solución actual como lista de movimientos, En el tablero se han colocada las n primeras piezas de vEntrada, en la columnas indicadas respectivamente en vSalida
// Post: solucionParcial contendrá la lista de movimientos completa (si no se llega a una solución, estará vacía, numMovs == 0)
//       Devuelve 1 si encuentra solución, -1 si no la encuentra.
int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo=0);


// Pre: listaMovimientos contiene la lista de movimientos con la solucion 
// Post: escribe la lista de movimientos en el fichero que se le pasa como argumento siguiendo el 
//      formato especificado en el guión (si está vacía, se escribe un -1 en el fichero)
void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion); 


int main(){

}