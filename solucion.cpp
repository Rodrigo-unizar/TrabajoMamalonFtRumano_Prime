#include "GSenku.hpp"
#include "solucion.hpp"

void movSupDer(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.x = movPieza.origen.x + 2;
    movPieza.destino.y = movPieza.origen.y - 2;

}

void movSup(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.y = movPieza.origen.y - 2;

}

void movSupIzq(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.x = movPieza.origen.x - 2;
    movPieza.destino.y = movPieza.origen.y - 2;

}

void movDer(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.x = movPieza.origen.x + 2;

}

void movIzq(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.x = movPieza.origen.x- 2;

}

void movInfDer(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.x = movPieza.origen.x + 2;
    movPieza.destino.y = movPieza.origen.y + 2;


}

void movInf(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.y = movPieza.origen.y + 2;

}

void movSInfIzq(tpMovimientoPieza &movPieza, tpTablero solParcial){

    movPieza.destino.x = movPieza.origen.x - 2;
    movPieza.destino.y = movPieza.origen.y + 2;


}

bool comprobarPosicion(tpPosicion posicion, tpTablero solParcial){

    if(solParcial.matriz[posicion.x][posicion.y] == OCUPADA){
        return true;
    }else {
        return false;
    }

}
