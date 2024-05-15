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
string pareoVertices[ 100 ];


// Prototipos
void vaciarMatriz( ); // Eliminar los valores basura
void imprimirMatriz( ); // Imprimir la matriz original
void imprimirMatrizClon( ); // Imprimir la matrizClon
void copiarMatriz( ); // Copiar de la matriz a la matrizClon
void ordenVertices( ); // Ordenar los vertices del menor conexiones al mayor
void pareo( ); // Pareo de vertices


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

    cout << endl << "Matriz obtenida del documento 'matriz_adyacencia.txt' " << endl << endl;
    imprimirMatriz( ); // Mostrar la matriz obtenida del archivo

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
        pareoVertices[ i ] = "";
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
    
    pareo( );
}


// Pareo de vertices para creación de individuos
void pareo( )
{
    int menorPeso = 0; // Menor peso del vertice 
    int verticePareo = 0; // Vertice con el que se parea
    int numeroIndividuo = 0; // Creación de individuo con el pareo
    int numeroVertice = 1; // Variable para guardar el valor de los vertices

    duplicarMatriz( ); // Duplicar la matriz con los valores originales

    // Titulo de lo que se hace
    cout << endl << endl << "Individuos que se generan: " << endl;

    // Recorrido de todas las posiciones del ordenPareo
    for ( int i = 0; i < tamanioMatriz; i++)
    {

        // Reiniciar la variable de comparaciones
        menorPeso = 100;

        // Si ya se hizo el pareo sigue avanzando
        if( ordenPareo[ i ] != -1 )
        {

            // Recorrer la matriz para encontrar le menos peso y después hacer pareo
            for ( int k = 0; k < tamanioMatriz; k++ )
            {

                // Buscar el menor peso y diferente de 0
                if ( matrizClon[ ordenPareo[ i ] ][ k ] < menorPeso && matrizClon[ ordenPareo[ i ] ][ k ] != 0 )
                {

                    // Cambiar el menor peso para seguir buscando
                    menorPeso = matrizClon[ ordenPareo[ i ] ][ k ];

                    // Guardar el vertice del menor peso
                    verticePareo = k;
                }
                
            }

            // Mostrar el individuo creado
            cout << endl << "Individuo " << ( numeroIndividuo + 1 ) << ": " << ( ordenPareo[ i ] + 1 ) << " - " << ( verticePareo + 1 );

            // Guardar el individuo para despues unirlo con los otros
            pareoVertices[ numeroIndividuo ] += "( V" + to_string( numeroVertice ) + ": " + to_string( ( ordenPareo[ i ] + 1 ) ) + " , ";
            numeroVertice++;

            pareoVertices[ numeroIndividuo ] += "V" + to_string( numeroVertice ) + ": " + to_string( ( verticePareo + 1 ) ) + " )";
            numeroVertice++;

            // Aumentar el indice de los individuos
            numeroIndividuo++;

            // Eliminar el renglon y columna de los 
            for ( int f = 0; f < tamanioMatriz; f++ )
            {
                matrizClon[ ordenPareo[ i ] ][ f ] = 0;
                matrizClon[ f ][ ordenPareo[ i ] ] = 0;
                matrizClon[ verticePareo ][ f ] = 0;
                matrizClon[ f ][ verticePareo ] = 0;
            }

            // Eliminarlo para que no sea tomado en cuenta para la siguiente vuelta
            ordenPareo[ i ] = -1;

            // Buscar y eliminar el vertice que hace pareo
            for ( int z = 0; z < tamanioMatriz; z++ )
            {
                if( ordenPareo[ z ] == verticePareo )
                {
                    ordenPareo[ z ] = -1;
                    break;
                }
            }
        }
    }

    // Imprimir el pareo de los vertices
    cout << endl << endl << "Union de individuos " << endl;

    // Mostrar resultados
    for ( int d = 0; d < numeroIndividuo; d++ )
    {
        cout << pareoVertices[ d ];
        if ( ( d + 1 ) != numeroIndividuo ) cout << " , ";
    }
}


