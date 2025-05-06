#------------------------------------------------------------------------------
# File:   Makefile
# Author: Programación II-Unizar
# Date:   mayo 2025
# Coms:   Makefile para compilar Trbajo GSenku   
#------------------------------------------------------------------------------

#---------------------------------------------------------
# Definición de macros
CC = g++                   # compilador
CPPFLAGS = -std=c++11      # opciones de compilación
RM = rm -f                 # comando para borrar ficheros

all: mainGSenku
#-----------------------------------------------------------
# Compilacion
mainGsenku.o: mainGSenku.cpp GSenku.o
	${CC} -c mainGSenku.cpp -I ../TrabajoMamalonFtRumano_Prime ${CPPFLAGS}
GSenku.o: GSenku.hpp 
	${CC} -c GSenku.hpp -I ../TrabajoMamalonFtRumano_Prime ${CPPFLAGS}


# Linkado
mainGSenku: mainGSenku.o GSenku.o 
	${CC} mainGSenku.o GSenku.o -I ../TrabajoMamalonFtRumano_Prime -o mainGSenku

#-----------------------------------------------------------	
# LIMPIEZA de todo lo generado. Ojo: se borrarán sin preguntar
clean:
	${RM} mainGSenku.o GSenku.o mainGSenku
