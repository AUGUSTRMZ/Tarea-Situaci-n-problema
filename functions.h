
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//////////////////////////////////////////////////////////////////////////////////////////////////////
// bibliotecas necesarias para la implementacion de los metodos
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

//////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;

// Estructura de datos que almacena los registros
/*
 * Estructura Registro
 * Representa cada línea de la bitácora con:
 * - mes: Mes (formato 3 letras, ejemplo: "Aug")
 * - dia: Día como número entero
 * - hora: Hora completa en formato "hh:mm:ss"
 * - ip: Dirección IP con puerto (###.##.###.###:####)
 * - razon: Mensaje que describe la razón del evento
 * - fechaFormateada: Fecha en formato "AAAAMMDDHHMMSS" para facilitar ordenamiento
 */
//////////////////////////////////////////////////////////////////////////////////////////////////////

struct Registro
{
  string mes;   // mes del evento
  int dia;      // dia del evento
  string hora;  // hora del evento
  string ip;    // direccion ip y puerto del evento
  string razon; // descripcion del evento
  string fecha; // fecha en formato "AAAAMMDDHHMMSS"
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
void formatoFecha(Registro &registro);

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcion para leer el archivo y cargar los datos en el vector
void leerArchivo(const string &filename, vector<Registro> &registros)
{
  ifstream file(filename); // abrir el archivo en modo lectura
  if (!file.is_open())     // si el archivo no se abrio correctamente
  {
    cout << "Error: no se pudo abrir el archivo \"" << filename << "\"" << endl;
    return;
  }
  string linea;                // almacena cada linea del archivo a modo de variable auxiliar temporal
  while (getline(file, linea)) // lee linea por linea el archivo
  {
    istringstream stream(linea); // convierte cada linea en un flujo para poder procesarla
    Registro registro;           // creacion de un objeto donde almacenar los datos, un nuevo registro

    // Extreaer los valores siguiendo el formato
    stream >> registro.mes >> registro.dia >> registro.hora >> registro.ip;
    getline(stream, registro.razon); // el resto de la linea y la guarda como la razon completa.

    formatoFecha(registro);        // convertir la fecha al formato "AAAAMMDDHHMMSS"
    registros.push_back(registro); // almacena el registro en el vector
  }
  file.close(); // cierra el archivo cuando termina de leer todas las lineas
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcion para convertir fechas en el registro al formato "AAAAMMDDHHMMSS"
void formatoFecha(Registro &registro)
{
  static const map<string, string> mesToNum =
      {
          {"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, {"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, {"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}};
  string mes = mesToNum.at(registro.mes);                                                             // convertir el mes a su numero
  string dia = (registro.dia < 10 ? "0" : "") + to_string(registro.dia);                              // si el dia es menor a 10, se asegura de que tenga dos digitos poniendo un 0 a la izquierda
  string hora = registro.hora.substr(0, 2) + registro.hora.substr(3, 2) + registro.hora.substr(6, 2); // remover los ':'

  registro.fecha = "2023" + mes + dia + hora; // formato para guardar la fecha
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
// Funciones del algoritmo Merge

// Funcion principal para ordenar los registros

// declaracion de metodos para no generar errores de definicion
void mergeSplit(vector<Registro> &registros, vector<Registro> &aux, int left, int right);
void mergeArray(vector<Registro> &registros, vector<Registro> &aux, int left, int middle, int right);

void orderMerge(vector<Registro> &registros)
{
  vector<Registro> aux(registros.size());              // vector auxiliar del mismo tamaño que original
  mergeSplit(registros, aux, 0, registros.size() - 1); // llamada a la funcion recursiva que divide el vector
}
// divide el vector
void mergeSplit(vector<Registro> &registros, vector<Registro> &aux, int left, int right)
{
  if (left >= right) // si esta vacio o solo tiene un elemento
  {
    return; // no se hace nada
  }
  int middle = left + (right - left) / 2;          // punto medio
  mergeSplit(registros, aux, left, middle);        // mitad izquierda
  mergeSplit(registros, aux, middle + 1, right);   // mitad derecha
  mergeArray(registros, aux, left, middle, right); // combina las mitades ya ordenadas
}
// combina las mitades ordenadas
void mergeArray(vector<Registro> &registros, vector<Registro> &aux, int left, int middle, int right)
{

  int i = left;                     // indice que recorre la mitad izquierda
  int j = middle + 1;               // indice que recorre la mitad derecha
  int k = left;                     // indice que recorre el vector original
  while (i <= middle && j <= right) // mientras los indices no se salgan de sus mitades del arreglo
  {
    if (registros[i].fecha <= registros[j].fecha) // si la fecha en la mitad izquierda es menor que la derecha
    {
      aux[k++] = registros[i++]; // se pasa el de la izquierda al vector auxiliar
      // i y k aumentan en 1 para avanzar en ese indice y no copiar repetidos o pegarlos en el mismo lugar en el caso de k
    }
    else // de lo contrario
    {
      aux[k++] = registros[j++]; // pasa lo mismo pero con el lado derecho
    }
  }

  // en caso de elementos restantes en la izquierda
  while (i <= middle)
  {
    aux[k++] = registros[i++]; // se coloca y avanzan los indices para no pegar duplicados o en el mismo lugar de k
  }

  // en caso de elementos restantes en la derecha
  while (j <= right)
  {
    aux[k++] = registros[j++]; // se hace lo mismo pero con el indice j
  }

  // ciclo for que copia el vector auxiliar al original
  for (int x = left; x <= right; x++)
  {
    registros[x] = aux[x];
  }

  // * Notas para entender mi implementacion de merge sort
  /*
  * ACLARACION!!!!

  esta explicacion es para mi implementacion de merge sort original, la version en esta tarea fue
  re adaptada para funcionar en este codigo, sin embargo cambia muy poco por lo que la explicacion
  explica bastante bien estos pequeños cambios pero que podrian resultar confusos para quien vea este
  reppo o mi yo del futuro

  Asi a grandes rasgos lo que hace es que divide el arreglo en mitades cada vez mas pequenias
    y al final las acomoda y vuelve a unir estas mitades pero ya arregladas
    en este caso lo hice de forma recursiva, no se si se pueda hacer de otro modo pero por el momento
    esta jalo y pues ya mejor ni le muevas, se que lo que se te complica mas de las 3 mitades de entender es
    la funcion que ordena las mitades entonces pues basicamente esta funciona con un vector temporal y con 3 indices (i,j y k)
    los cuales representan el indice que va desde;
    i = mitad izquierda
    j = mitad derecha
    k = arreglo completo del orignal

    con un ciclo for voy pegando estos valores a uno temporal y al final se los paso al orignal
    ahora con un ciclo while lo que hiciste fue definir limites para cada indice de las mitades (i y j)
    donde pones que el ciclo se ejecuta hasta que estas no lleguen a su tamanio en este caso que la mitad izquierda no pase
    la mitad del arreglo y que la derecha no pase el indice derecho final luego mientras esto se cumpla
    se evalua si el vector auxiliar que tiene los datos se va pasando por las dos mitades con los indices i y j si el de la
    izquierda osea el indice i es menor que el del indice j de la mitad derecha entonces ese valor se pasa al arreglo orignal
    y ambos indices crecen para poder pegar en el siguiente espacio y no haya datos repetidos por parte de i y que no se este
    pegando todo en el mismo lugar por parte de j
    de caso contrario pues lo mismo pero en lugar de i es j.

    te pongo un ejemplo mas visual de como funciona esto
    por ejemplo tenemos un arreglo auxiliar y uno original
1.

            i         j
    aux[] ={0, 7, 5 , 6 , 3 , 8}

             k
    arr[] = {0}
    i solo llega hasta el 5 que es su limite en el while y j hasta el 8, van avanzando mientras se van comparando, si i es menor que j entonces el valor de i
    se pega en el arreglo original e i pasa el siguiente elemento

2.
                i           j
    aux[] ={0,  7,  5 , 6 , 3 , 8} 
    de nuevo se vuelve a hacer la comparacion y asi sucesivamente
    
               k
    arr[] ={0, 3}

    IMPORTANTE
    si el que resulto mayor no es el que se imprime ese indice no avanza al siguiente por ejemplo i
    no se mueve de 7 hasta que se comprare con el siguiente de j para evitar saltarte datos en el arreglo
    o pegarlos en el mismo lugar con el indice k
  */
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcion para buscar los registros por fechas
void buscarPorFechas(const vector<Registro> &registros, const string &start_date, const string &end_date);

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcion que escribe los registros ordenados en un nuevo archivo
void guardarRegistro(const string &filename, const vector<Registro> &registros);

//////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
