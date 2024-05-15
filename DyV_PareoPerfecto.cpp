/*
    Universidad Autónoma de Aguascalientes

    Centro: Ciencias Básicas
    Materia: Teoría de la Complejidad Computacional
    Docente: Dr. Eunice Esther Ponce de León Sentí
    Alumnos:
        Kandy Fabiola López Flores 326912
        Miguel Ángel Durón Láriz 331992
        Guillermo Gonzalez Lara 237864

    Actividad:
        Pareo perfecto con un grago pesado y un numero de vertices par,
        utiliznado el metodo de Divide y Venceras

    Fecha: 15/May/2024

*/


// Librerias
#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
using namespace std;


// Variables globales
int tamanioMatriz = 0; // Tamanio de la matriz utilizada
int matriz[ 100 ][ 100 ]; // Matriz para guardar los valore originales
int matrizClon[ 100 ][ 100 ]; // Matriz para poder trabajar sin perder valores originales
int ordenPareo[ 100 ]; // Ordenar le menor al mayor conexiones los vertices


// Prototipos
void vaciarMatriz( ); // Eliminar los valores basura
void imprimirMatriz( ); // Imprimir la matriz original
void imprimirMatrizClon( ); // Imprimir la matrizClon
void copiarMatriz( ); // Copiar de la matriz a la matrizClon
void ordenVertices( ); // Ordenar los vertices del menor conexiones al mayor


// Funcion principal
int main()
{
	system( "cls" ); // Limpiar consola
	system( "title Algoritmo Gloton" ); // Cambiar el titulo de la consola
	setlocale( LC_ALL , "" ); // Aceptar acentos

    vaciarMatriz( ); // Vaciar completamente la matriz global

    string nombreArchivo = "matriz_adyacencia.txt"; // Encontrar el archivo
    ifstream archivo( nombreArchivo.c_str() ); // Abrir el archivo

    string linea = "" ; // Leer linea por linea el archivo txt
    string guardarNumero = ""; // Leer el numero del archivo
    int indice = 0; // Aumentar la posicion de la matriz

    // Leer todos los renglones del archivo txt
    for ( int k = 0; getline( archivo , linea ); k++ )
    {
        for ( int m = 0; m < linea.length(); m++ )
        {
            if ( linea[ m ] != ' ') guardarNumero += linea[ m ];
            else
            {
                matriz[ k ][ indice ] = stoi( guardarNumero );
                indice++;
                guardarNumero = "";    
            }

        }
            
        tamanioMatriz = k + 1;
        indice = 0;
    }

    // cout << endl << "Matriz obtenida del documento.txt " << endl << endl;
    // imprimirMatriz( ); // Mostrar la matriz obtenida del archivo

    ordenVertices( );

    cout << endl << endl; // Separador
    system( "pause" ); // Hacer que pare antes de terminar
	return 0; // Terminar el algoritmo
}


// Vaciar todas las posiciones por 0, para eliminar los valores basura
void vaciarMatriz( )
{
    for ( int i = 0; i < 100; i++ )
    {
        for ( int k = 0; k < 100; k++) matriz[ i ][ k ] = 0 , matrizClon[ i ][ k ];
        ordenPareo[ i ] = false;
    }
}


// Mostrar los valores de la matriz
void imprimirMatriz( )
{
    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        for ( int k = 0; k < tamanioMatriz; k++ ) cout << matriz[ i ][ k ] << " ";
        cout << endl;
    }
}


// Imprimir los valores de la matrizClons
void imprimirMatrizClon( )
{
    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        for ( int k = 0; k < tamanioMatriz; k++ ) cout << matrizClon[ i ][ k ] << " ";
        cout << endl;
    }
}


// Duplicar la matriz original en una copia de la matriz
void duplicarMatriz( )
{
    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        for ( int k = 0; k < tamanioMatriz; k++ ) matrizClon[ i ][ k ] = matriz[ i ][ k ];
    }
}


// Ordenar los vertices por los que tengan menos conexiones
void ordenVertices( )
{

    // Duplicar los valores para no perder los originales
    duplicarMatriz( );

    // Variables para el funcionamientos
    int menor = 0 , contar = 0 , posicion = 0;

    for ( int i = 0; i < tamanioMatriz; i++ )
    {

        // Reiniciar la variable para cada vuelta
        menor = 100;
        

        // Recorrer todas las posiciones
        for ( int k = 0; k < tamanioMatriz; k++ )
        {

            // Reiniciar el contador
            contar = 0;

            // Contar cuantas conexiones tiene cada renglon
            for ( int m = 0; m < tamanioMatriz; m++ ) if ( matrizClon[ k ][ m ] != 0 ) contar++; 


            // Guardar momentaneamente la posicion del vertice que tiene menos conexiones
            if ( menor > contar && contar != 0 )
            {
                menor = contar;
                posicion = k;
            }
        }

        // Guardar el lugar y avanzar
        ordenPareo[ i ] = posicion;

        // Eliminar ese renglon para que no se tome en cuenta
        for ( int l = 0; l < tamanioMatriz; l++ ) matrizClon[ posicion ][ l ] = 0;
        
    }

    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        cout << ordenPareo[ i ] << " ";
    }
    
}


