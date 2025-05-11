#include "GSenku.hpp"
#include <iostream>
#include <fstream>

using namespace std;


const int DESPLAZAMIENTOS[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1},  // Superior izquierda, superior, superior derecha
    {0, -1},          {0, 1},    // Izquierda, derecha
    {1, -1}, {1, 0}, {1, 1}     // Inferior izquierda, inferior, inferior derecha
};

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
int buscaSolucion(tpTablero &tablero, const tpMovimientosValidos &movValidos, tpListaMovimientos &solucionParcial, const int retardo){
    
    tpPosicion pos;
    tpPosicion destino ;//posicion destino 
    tpPosicion salto;//posicion de la pieza que salta
    bool posValida;
    //Caso base
    if(comprobarTablero(tablero)){
        
        return 1;
        
    }else {
        
        for(int i = 0;i < tablero.nfils;i++){
            
            for(int j = 0;j < tablero.ncols;j++){
                pos.y = j;
                pos.x = i;
                if(tablero.matriz[pos.x][pos.y] == OCUPADA){    
                    
                    for(int w = 0; w < 8;w++){ //pa comprobar todos los movimientos
                        
                        if(movValidos.validos[w]){ // si se puede mover hace toda la logica 

                            
                            salto.x = pos.x + DESPLAZAMIENTOS[w][0];
                            salto.y = pos.y + DESPLAZAMIENTOS[w][1];
                            
                            destino.x = salto.x + DESPLAZAMIENTOS[w][0];
                            destino.y = salto.y + DESPLAZAMIENTOS[w][1];
                            //comprobar que la posicion esta dentro del tablero 
                            
                            if (destino.x >= 0 && destino.x < tablero.nfils &&
                                destino.y >= 0 && destino.y < tablero.ncols){ 
                                 
                                posValida = tablero.matriz[salto.x][salto.y] == OCUPADA && tablero.matriz[destino.x][destino.y] == VACIA; // mira a ver si puede hacer el salto 

                                if(posValida){
                                    //si la posicion es valida caambia todo a la nueva posible solucion
                                    tablero.matriz[pos.x][pos.y] = VACIA;
                                    tablero.matriz[salto.x][salto.y] = VACIA;
                                    tablero.matriz[destino.x][destino.y] = OCUPADA;

                                    solucionParcial.movs[solucionParcial.numMovs].origen = pos;
                                    solucionParcial.movs[solucionParcial.numMovs].destino = destino;
                                    solucionParcial.numMovs ++;
                                    //hace el siguiente estado
                                    int sol = buscaSolucion(tablero, movValidos, solucionParcial, retardo);
                                    
                                    if(sol == 1){
                                         //si es valido se mantine con los cambios 
                                        return sol;

                                    }
                                    //sino vuelve atras y sigue con los bucles
                                    solucionParcial.numMovs--;
                                    tablero.matriz[pos.x][pos.y] = OCUPADA;
                                    tablero.matriz[salto.x][salto.y] = OCUPADA;
                                    tablero.matriz[destino.x][destino.y] = VACIA;
                                    
                                }
                            }
                        }
                    }
                }
            }
        }        
    }
    return -1; //Arriba todas las veces que puede dar pos valida o que sirve lo que hace es return 1 por lo que si llega aqui si o si es pos invalida:
}


//Post: NOs dice si el tablero esta Vacio o No 
bool comprobarTablero(const tpTablero tablero){

    int nFichas = 0;

    for(int i = 0;i < tablero.nfils ;i++){
        for(int j = 0;j < tablero.ncols  ;j++){
            if(tablero.matriz[i][j] == OCUPADA){
                
                
                nFichas++;
            }
        }
    }
    return nFichas == 1;
}
// Pre: listaMovimientos contiene la lista de movimientos con la solucion 
// Post: escribe la lista de movimientos en el fichero que se le pasa como argumento siguiendo el 
//      formato especificado en el guión (si está vacía, se escribe un -1 en el fichero)
void escribeListaMovimientos (string nombreFichero, const tpListaMovimientos &solucion){
    ofstream f;
    f.open(nombreFichero);
    if(f.is_open()){
        for(unsigned i = 0; i < solucion.numMovs; i++){
            f << solucion.movs[i].origen.x << "," << solucion.movs[i].origen.y << ";" << solucion.movs[i].destino.x << "," << solucion.movs[i].destino.y << endl;
            
        }
        f.close();
    } else{
        cerr << "No se ha podido abrir el fichero: " << nombreFichero << endl;
    }
} 

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

    string nomTablero = "tableros_modelo/tableroEuropeo.txt";
    string nombreMov = "movimientos/movimientosCompletos.txt";
    string nombreSol = "solucion.txt";

    tpTablero tablero;
    
    tpListaMovimientos solParcial;
    int retardo = 0;
    tpMovimientosValidos movimientos;

    inicializarMovimientosValidos(nombreMov, movimientos);
    inicializarTablero(nomTablero, tablero);
    
    comprobarLeerMovsValidos(nombreMov, movimientos);
    mostrarTablero(tablero);
    int sol = buscaSolucion(tablero, movimientos, solParcial, retardo);
    cout << sol;
    escribeListaMovimientos(nombreSol, solParcial);
    
}
