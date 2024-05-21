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
#include <cstdlib>
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

// LLenado de valores de matriz
void matrizAleatoria( ); // Se llena con valores aleatorios
void leerArchivo( ); // Se lee un archivo txt para llenar la matriz
void valoresManual( ); // Llenar la matriz con valores manualmente
bool matrizCorrecta( ); // Revisar si esta correcta la matriz


// Funcion principal
int main()
{
	system( "cls" ); // Limpiar consola
	system( "title Algoritmo Gloton" ); // Cambiar el titulo de la consola
	setlocale( LC_ALL , "" ); // Aceptar acentos
    srand (time(NULL)); // Para generar los numeros aleatorios

    bool terminar = true , error = false;
    char salir;
    char opcion;

    while( terminar )
    {

        // Reiniciar la variable si hay algun error
        error = false;

        do
        {

            // Limpiar consola
            system( "cls" );

            // Opcion diferente a las mostradas
            if ( error ) cout << " Opcion incorrecta. ";

            // Titulo
            cout << " Lectura de matriz: " << endl;

            // Opciones
            cout << " 1) Matriz aleatoria. " << endl;
            cout << " 2) Lectura de archivo de texto. " << endl;
            cout << " 3) Ingresar valores manualmente. " << endl;

            // Lectura de opcion
            cout << "Opcion: "; cin >> opcion;

            // Por si hay algun error
            error = true;

        // Valir la opcion
        } while ( opcion != '1' && opcion != '2' && opcion != '3' );

        vaciarMatriz( );

        switch ( opcion )
        {
            // Opcion 1 para llenado de matriz aleatoria
            case '1': matrizAleatoria( ); break;

            // Opcion 2 para leer un archivo de texto txt
            case '2': leerArchivo( ); break;

            // Opcion 3 para llenar valores manualmente
            case '3': valoresManual( ); break;
            
            // Opcion por defecto (nunca se hace)
            default: break;
        }

        if ( matrizCorrecta( ) )
        {

            // Iniciar con el algoritmo
            cout << "Matriz aceptada" << endl;

            // Acomodar los vertices para que se hagan en el orden correcto
            // del que tenga menro numero de aristas al que tenga mas
            ordenVertices( );

            // Separador
            cout << endl << endl;

            system( "pause" );

            // Opcion de salida, solo acepta la letra 'y' o 'n'
            do
            {
                system( "cls" );
                cout << "Quieres terminar el algoritmo? (y/n) "; cin >> salir;
            } while ( salir != 'y' && salir != 'n' );

            // Si terminarlo
            if ( salir == 'y') terminar = false;

            // No terminarlo y reiniciar el algoritmo
            if ( salir == 'n' ) cout << "Reiniciando..." << endl << endl , system( "pause" );

        }
        else
        {

            system( "cls" ); // Limpiar consola

            // Matriz con valores erroneos
            cout << " Matriz con valores incorrectos " << endl;

            // Posibles errones
            cout << " Posibles erores: Algún vertice no tiene aristas o tiene peso negativo " << endl;

            // Esperar una tecla
            system( "pause" );

            // Seguir con las iteraciones del ciclo
            continue;
        }

    }

    system( "cls" ); // Limpiar consola
    cout << "Saliendo...";

    cout << endl << endl; // Separador
    system( "pause" ); // Hacer que pare antes de terminar
	return 0; // Terminar el algoritmo
}


// Matriz llenada aleatoriamente
void matrizAleatoria( )
{

    // Titulo de la funcion seleccionada
    cout << "Matriz aleatoria" << endl;

    // Por si hay un error
    bool valorCorrecto = false;

    // Si el renglon generado es todo ceros
    bool todoCeros = true;

    // Variable para agregar ceros a la matriz
    int randomCero = 0;

    // Cambiar peso de arista
    int cambioPeso = -1;

    do
    {
        system( "cls" ); // Limpiar consola

        // Tamanio menor a 0 o mayor a 100
        if ( valorCorrecto ) cout << " El valor ingresado es incorrecto, intenta con otro " << endl;

        // Lectura del tamanio de la matriz
        cout << "Tamanio de la matriz: "; cin >> tamanioMatriz;

        // Error en el tamanio
        valorCorrecto = true;

    // Valir la lectura
    } while ( tamanioMatriz <= 0 || tamanioMatriz >= 101 || ( tamanioMatriz % 2 ) != 0 );


    // Generacion de numeros aleatorios
    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        for ( int k = ( i + 1 ); k < tamanioMatriz; k++ )
        {
            // Generar random para aumentar el tamanio de los 0
            randomCero = rand( ) % 100;

            // La diagonal principal sigue siendo cero
            if ( k != i )
            {
                if ( randomCero <= 30 ) matriz[ i ][ k ] = 0;
                else matriz[ i ][ k ] = 1 + rand() % 10;
            }
            

            // Generar valores entre 0 y 10
            
        }

        // Reiniciar variables por si todo el renglon es 0
        todoCeros = true;

        // Recorrec todo el renglon
        for ( int m = ( i + 1 ); m < tamanioMatriz; m++ )
        {
            if ( matriz[ i ][ m ] != 0 ) todoCeros = false;
        }

        // Si es la ultima posicion
        if ( ( i + 1 ) == tamanioMatriz ) todoCeros = false;

        // Cambiar algun peso por 1 si es todo 0
        if ( todoCeros && ( i + 1 ) != tamanioMatriz )
        {
            while ( cambioPeso == i)
            {
                cambioPeso = i + rand() % ( tamanioMatriz - i );
            }
            
            matriz[ i ][ cambioPeso ] = 1;
        }
    }

    // Triangular inferior
    for ( int i = 0; i < tamanioMatriz; i++ )
    {

        // Hacer espejo de la matriz
        for ( int k = ( i + 1 ); k < tamanioMatriz; k++ )
        {
            matriz[ k ][ i ] = matriz[ i ][ k ];
        }
    }

    // Mostrar la matriz generada
    cout << endl << " Matriz generada " << endl;
    imprimirMatriz( );

    // Detener
    system( "pause" );
}

// Debe existir un archivo en la misma carpeta que el codigo para poder funcionar
// el archivo se debe llamar "matriz_adyacencia.txt"
void leerArchivo( )
{

    // Lectura del archivo
    cout << "Lectura del archivo externo txt" << endl;

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

        // Tamanio de la matriz, se le suma 1 porque el ciclo for empieza en el 0
        tamanioMatriz = k + 1;
        indice = 0;
    }

    // Titulo de la lectura
    cout << endl << "Matriz obtenida del documento 'matriz_adyacencia.txt' " << endl << endl;
    imprimirMatriz( ); // Mostrar la matriz obtenida del archivo
}


// Llenar la matriz de manera manual
void valoresManual( )
{

    // Titulo de la opcion selccionada
    cout << " Lectura de valores manualmente " << endl;

    bool valorCorrecto = false;

    do
    {
        system( "cls" ); // Limpiar consola

        // Valores menor a 0 o mayor a 100
        if ( valorCorrecto ) cout << " El valor ingresado es incorrecto, intenta con otro " << endl;

        // Lectura del tamanio de la matriz
        cout << "Tamanio de la matriz:"; cin >> tamanioMatriz;

        // Por si hay un error en el valor
        valorCorrecto = true;
    } while ( tamanioMatriz <= 0 || tamanioMatriz >= 101 || ( tamanioMatriz % 2 ) != 0 );

    // Titulo para empezar con el llenado de la matriz
    cout << " Ingresar la matriz de adyacencia " << endl << endl;

    // Lectura de los valores
    for ( int i = 0; i < tamanioMatriz; i++ )
    {
        for ( int k = 0; k < tamanioMatriz; k++ )
        {
            cout << endl << "[" << i <<"][" << k << "]: "; cin >> matriz[ i ][ k ];
        }
    }
}


// Revisar si la matriz tiene valores correctos
bool matrizCorrecta( )
{

    // Comprobar si un vertice no tiene aristas
    bool todoCeros = true;

    // Comprobar si alguna arista tiene peso negativo
    bool numeroNegativo = false;

    // Recorrer toda la matriz
    for ( int i = 0; i < tamanioMatriz; i++ )
    {

        // Reiniciar la variable en cada renglon
        todoCeros = true;

        // Recorrer las columnas
        for ( int k = 0; k < tamanioMatriz; k++ )
        {
            // Regresar false si hay valor negativo
            if ( matriz[ i ][ k ] < 0 ) numeroNegativo = true;

            // Regresar false si hay todo ceros
            if( matriz[ i ][ k ] > 0 ) todoCeros = false;
        }

        // No aceptar la matriz
        if ( todoCeros || numeroNegativo )  return false;
    }

    return true;
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


