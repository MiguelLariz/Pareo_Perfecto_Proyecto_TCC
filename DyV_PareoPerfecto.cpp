/*
    Universidad Autónoma de Aguascalientes

    Centro: Ciencias Básicas
    Materia: Teoría de la Complejidad Computacional
    Docente: Dr. Eunice Esther Ponce de León Sentí
    Alumnos:
        Kandy Fabiola López Flores 326912
        Miguel Ángel Durón Láriz 331992

    Actividad:
        Mediante la implementación del algoritmo glotón
        se llevo a cabo la solución al tan conocido problema
        del agente viajero, con el fin de obtener el 
        camino con el menor peso posible.

    Fecha: 08/abr/2024

*/

#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
using namespace std;


// Variables globales
int tamanioMatriz = 0;
int matriz[ 100 ][ 100 ];


// Prototipos
void vaciarMatriz( );
void imprimirMatriz( );


int main()
{
	system( "cls" ); // Limpiar consola
	system( "title Algoritmo Gloton" ); // Cambiar el titulo de la consola
	setlocale( LC_ALL , "" ); // Aceptar acentos

    vaciarMatriz( ); // Vaciar completamente la matriz global

    string nombreArchivo = "matriz_adyacencia.txt"; // Encontrar el archivo
    ifstream archivo( nombreArchivo.c_str() ); // Abrir el archivo

    string linea = "" , guardarNumero = "";
    int indice = 0;

    for ( int k = -1; getline( archivo , linea ); k++ )
    {

        if( linea == "" )
        {
            k--;
            continue;
        }

        if( k == -1 ) tamanioMatriz = stoi( linea );
        else
        {
            for ( int m = 0; m < linea.length(); m++ )
            {
                if ( linea[ m ] != ' ')
                {
                    guardarNumero += linea[ m ];
                }
                else
                {
                    matriz[ k ][ indice ] = stoi( guardarNumero );
                    indice++;
                    guardarNumero = "";
                }
            }
            indice = 0;
        }
    }

    cout << endl << "Matriz obtenida del documento.txt " << endl << endl;
    
    imprimirMatriz( ); // Mostrar la matriz obtenida del archivo


    cout << endl << endl; // Separador
    system( "pause" ); // Hacer que pare antes de terminar
	return 0; // Terminar el algoritmo
}


// Vaciar todas las posiciones por 0, para eliminar los valores basura
void vaciarMatriz( )
{
    for ( int i = 0; i < 100; i++ )
    {
        for ( int k = 0; k < 100; k++) matriz[ i ][ k ] = 0;
    }
}


void imprimirMatriz( )
{
    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        for ( int k = 0; k < tamanioMatriz; k++ ) cout << matriz[ i ][ k ] << " ";
        cout << endl;
    }
}