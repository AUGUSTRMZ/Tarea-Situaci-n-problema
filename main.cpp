/*
* Integrantes:
 * Cesar Augusto Ramirez Davila | A01712439
 * Alexia Arteaga Mendoza |
 * Luis Hubert Madrian Valero |

 * 15/01/2025
 */
#include <iostream>
#include <vector>
#include "functions.h"

using namespace std;

int main()
{
  // vecotr para almacenar los registros de la bitacora
  vector<Registro> registros;

  // nombres de archivos
  string inputFile = "bitacora.txt";
  string outputFile = "bitacora_ordenada.txt";

  // variables para las fechas de busqueda
  string starDate, endDate;

  // variable para el ciclo switch
  int opcion;

  do // hacer lo siguiente
  {
    cout << "==== Menu principal ====" << endl;
    cout << endl;
    cout << "1.- Leer Archivo " << endl;
    cout << "2.- Ordenar registros " << endl;
    cout << "3.- Buscar registros por fechas " << endl;
    cout << "4.- Guardar registros ordenados " << endl;
    cout << "5.- Salir del programa " << endl;
    cout << "Ingresa el indice de tu eleccion: ";
    cin >> opcion;

    switch (opcion)
    {
    case 1:
      leerArchivo(inputFile, registros);
      break;

    case 2:
      orderMerge(registros);
      cout << "Registros ordenados con exito!" << endl;
      break;

    case 3:
      cout << "Ingrese la fecha de inicio (AAAAMMDDHHMMSS): ";
      cin >> starDate;
      cout << "Ingrese la fecha de fin (AAAAMMDDHHMMSS): ";
      cin >> endDate;
      buscarPorFechas(registros, starDate, endDate);
      break;

    case 4:
      guardarRegistro(outputFile, registros);
      cout << "Registros escritos y guardados en" << outputFile << " correctamente." << endl;
      break;

    case 5:
      cout << "Saliendo del programa " << endl;
      cout << "Nos vemos pronto! ;) " << endl;
      break;

    default:
      cout << "Opcion no valida, ingrese nuevamente.";
      break;
    }

  } while (opcion != 5); // mientras opcion no valga 5

  return 0;
}