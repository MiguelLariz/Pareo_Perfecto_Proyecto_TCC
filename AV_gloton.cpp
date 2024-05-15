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
int matriz[ 50 ][ 50 ];
bool ciudadRecorrida[ 50 ];
int caminoCiudad[ 50 ];
int indice = 0;
int tamanioMatriz = 50;


void vaciarMatriz( ) // Vaciado de matriz y de vector de recorrido booleano
{
    for (int i = 0; i < tamanioMatriz; i++)
    {
        for (int k = 0; k < tamanioMatriz; k++)
        {
            matriz[ i ][ k ] = -1;
        }

        ciudadRecorrida[ i ] = true;
        caminoCiudad[ i ] = -1;

    }
}

void imprimirMatriz( int dimesion )
{
    for (int i = ( dimesion - 1 ); i >= 0; i--)
    {
        if( i >= 10 ) cout << i << " ";
        else cout << " " << i << " ";

        cout << "|";

        for (int k = 0; k < dimesion; k++)
        {
            if( matriz[ i ][ k ] == -1 ) cout << "   ";
            else if( matriz[ i ][ k ] >= 10 ) cout << matriz[ i ][ k ] << " ";
            else cout << " " << matriz[ i ][ k ] << " ";
        }
        cout << endl;
    }

    cout << "    --------------------------------------------" << endl << "    ";


    for (int i = 0; i < tamanioMatriz; i++)
    {
        if( i >= 10 ) cout << i << " ";
        else cout << " " << i << " ";
    }
}

int coordenadasX( int ciudad )
{
    int x = 0 , y = 0;
    for (int i = 0; i < tamanioMatriz; i++)
    {
        for (int k = 0; k < tamanioMatriz; k++)
        {
            if( matriz[ i ][ k ] == ciudad ) x = i;
        }
        
        if( x != 0) break;
    }

    return x;
}

int coordenadasY( int ciudad )
{
    int x = 0 , y = 0;
    for (int i = 0; i < tamanioMatriz; i++)
    {
        for (int k = 0; k < tamanioMatriz; k++)
        {
            if( matriz[ i ][ k ] == ciudad ) y = k;
        }
        
        if( y != 0) break;
    }

    return y;
}

float distanciaCiudades( int a0 , int b0 , int a1 , int b1 )
{
    float a = abs( a0 - a1 );
    float b = abs( b0 - b1 );

    a = pow( a , 2 );
    b = pow( b , 2 );

    float c = pow( (a + b) , ( 0.5 ) );

    return c;
}


void mostrarCiudadesRecorridas( )
{
    // cout << endl << " Ciudades Recorridas " << endl;

    // for (int i = 0; i < 15; i++)
    // {
    //     cout << ciudadRecorrida[ i ] << "   ";
    // }

    cout << endl << endl << " Camino Ciudades " << endl;
    for (int i = 0; i < tamanioMatriz; i++)
    {
        if( caminoCiudad[ i ] != -1 ) cout << caminoCiudad[ i ] << "   ";
    }
    
    cout << "0 " << endl << endl;
}


int ciudadMasCerca( int ciudad )
{
    int siguienteCiudad = 0;

    // cout << " Ciudad: " << ciudad << endl;
    int a0 = coordenadasX( ciudad );
    int b0 = coordenadasY( ciudad );

    // cout << " a0: " << a0 << endl;
    // cout << " b0: " << b0 << endl;

    int a1 = 0, b1 = 0 , aComparacion = 0 , bComparacion = 0;
    float menorDistancia = 1000.0, nuevaDistancia = 0.0;

    for (int i = 0; i < tamanioMatriz; i++)
    {
        if( ciudadRecorrida[ i ] ) 
        {
            // cout << " Ciudad: " << i << endl;
            aComparacion = coordenadasX( i );
            bComparacion = coordenadasY( i );

            // cout << " aNueva: " << aComparacion << endl;
            // cout << " bNueva: " << bComparacion << endl;


            nuevaDistancia = distanciaCiudades( a0 , b0 , aComparacion , bComparacion );

            // cout << " NuevaDistancia: " << nuevaDistancia << endl;

            // system( "pause" );

            if( nuevaDistancia < menorDistancia )
            {
                a1 = aComparacion;
                b1 = bComparacion;
                siguienteCiudad = i;
                menorDistancia = nuevaDistancia;
            }
        }

    }
    
    return siguienteCiudad;

}


void marcarCiudad( int ciudad )
{
    caminoCiudad[ indice ] = ciudad;
    indice++;
    ciudadRecorrida[ ciudad ] = false;
}

int main()
{
	system("cls");
	system("title Algoritmo Gloton");
	setlocale(LC_ALL, "");

    vaciarMatriz( );

    string nombreArchivo = "agenteViajero.txt";
    ifstream archivo( nombreArchivo.c_str() );

    string linea = "" , x = "" , y = "";
    bool espacio = true;


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
            x = "";
            y = "";
            espacio = true;
            for (int m = 0; m < linea.length(); m++)
            {
                
                if ( espacio ) x+= linea[ m ];
                else y += linea[ m ];
                
                if ( linea[ m ] == ',' ) espacio = false;
            }

            // cout << " x: " << x << endl;
            // cout << " y: " << y << endl;

            matriz[ stoi( x ) ][ stoi( y ) ] = k;
        }

        // cout << linea << endl;

    }

    cout << endl;

    
    imprimirMatriz( tamanioMatriz );
    

    int ciudad = 0;

    for( int m = 0; m < tamanioMatriz; m++ )
    {

        marcarCiudad( ciudad );

        ciudad = ciudadMasCerca( ciudad );
    

        // cout << " siguienteCiudad: " << siguienteCiudad << endl;

        //marcarCiudad( siguienteCiudad );

    }


    mostrarCiudadesRecorridas( );



	return 0;	
}
