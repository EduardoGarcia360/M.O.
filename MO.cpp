#include <MatrizOrtogonal.h>
#include <stdlib.h>
#include <iostream>
#include "string.h"

using namespace std;

Nodo::Nodo(int fila, int columna, char * valor)
{
    this->fila = fila;
    this->columna = columna;
    this->valor = valor;
}

Encabezado::Encabezado(int id)
{
    this->id = id;
}

void ListaEncabezados::insertar(Encabezado * nuevo)
{
    if(primero == NULL)
    {
       primero = nuevo;
    }
    else
    {
        if(nuevo->id < primero->id) //Inserción al inicio
        {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
        else
        {
            Encabezado * actual = primero;
            while(actual->siguiente != NULL)
            {
                if(nuevo->id < actual->siguiente->id) //Inserción en el medio
                {
                    nuevo->siguiente = actual->siguiente;
                    actual->siguiente->anterior = nuevo;
                    nuevo->anterior = actual;
                    actual->siguiente = nuevo;
                    break;
                }

                actual = actual->siguiente;
            }

            if(actual->siguiente == NULL) //Inserción al final
            {
                actual->siguiente = nuevo;
                nuevo->anterior = actual;
            }
        }
    }
}

Encabezado * ListaEncabezados::getEncabezado(int id)
{
    Encabezado * actual = primero;
    while(actual != NULL)
    {
        if(actual->id == id)
        {
            return actual;
        }

        actual = actual->siguiente;
    }

    return NULL;
}

Matriz::Matriz()
{
    this->eFilas = new ListaEncabezados();
    this->eColumnas = new ListaEncabezados();
}

void Matriz::insertar(int fila, int columna, char * valor)
{
    Nodo * nuevo = new Nodo(fila, columna, valor);

    //INSERCION_FILAS
    Encabezado * eFila = eFilas->getEncabezado(fila);
    if(eFila == NULL) //Si no existe encabezado se crea.
    {
        eFila = new Encabezado(fila);
        eFilas->insertar(eFila);
        eFila->acceso = nuevo;
    }
    else
    {
        if(nuevo->columna < eFila->acceso->columna) //Inserción al inicio
        {
            nuevo->derecha = eFila->acceso;
            eFila->acceso->izquierda = nuevo;
            eFila->acceso = nuevo;
        }
        else
        {
            Nodo * actual = eFila->acceso;
            while(actual->derecha != NULL)
            {
                if(nuevo->columna < actual->derecha->columna) //Inserción en el medio
                {
                    nuevo->derecha = actual->derecha;
                    actual->derecha->izquierda = nuevo;
                    nuevo->izquierda = actual;
                    actual->derecha = nuevo;
                    break;
                }

                actual = actual->derecha;
            }

            if(actual->derecha == NULL) //Inserción al final
            {
                actual->derecha = nuevo;
                nuevo->izquierda = actual;
            }
        }
    }
    //FIN_FILAS

    //INSERCION_COLUMNAS
    Encabezado * eColumna = eColumnas->getEncabezado(columna);
    if(eColumna == NULL) //Si no existe encabezado se crea.
    {
        eColumna = new Encabezado(columna);
        eColumnas->insertar(eColumna);
        eColumna->acceso = nuevo;
    }
    else
    {
        if(nuevo->fila < eColumna->acceso->fila) //Inserción al inicio
        {
            nuevo->abajo = eColumna->acceso;
            eColumna->acceso->arriba = nuevo;
            eColumna->acceso = nuevo;
        }
        else
        {
            Nodo * actual = eColumna->acceso;
            while(actual->abajo != NULL)
            {
                if(nuevo->fila < actual->abajo->fila) //Inserción en el medio
                {
                    nuevo->abajo = actual->abajo;
                    actual->abajo->arriba = nuevo;
                    nuevo->arriba = actual;
                    actual->abajo = nuevo;
                    break;
                }

                actual = actual->abajo;
            }

            if(actual->abajo == NULL) //Inserción al final
            {
                actual->abajo = nuevo;
                nuevo->arriba = actual;
            }
        }
    }
    //FIN_COLUMNAS
}

void Matriz::eliminar(int fila, int columna, char *dato){
    Encabezado * eColumna = eColumnas->primero;
    Encabezado * eFila = eFilas->primero;
    bool correcto = false;
    cout << "Eliminando:" <<endl;

    while(eColumna != NULL)
    {
        Nodo * actual = eColumna->acceso;
        if(strcmp(actual->valor, dato) == 0 && actual->fila == fila && actual->columna == columna){
            /*verificamos si es el primer dato de la columna*/

            if(actual->fila == 0 && actual->columna == 0){
                //1er. caso: sea el nodo en la posicion (0,0)

                //moviendo hacia abajo
                eColumna->acceso = actual->abajo;
                Nodo * ab = actual->abajo;
                ab->arriba = eColumna->acceso;

                //moviendo hacia los lados
                eFila->acceso = actual->derecha;
                Nodo * der = actual->derecha;
                der->izquierda = eFila->acceso;

                //se elimina el nodo
                correcto = true;
                free(actual);
                break;
            }else if(actual->abajo != NULL && actual->derecha != NULL){
                //2do caso: tiene nodos a la derecha y abajo

                //moviendo vertical
                eColumna->acceso = actual->abajo;
                Nodo * ab = actual->abajo;
                ab->arriba = eColumna->acceso;

                //moviendo horizontal
                Nodo * der = actual->derecha;
                Nodo * izq = actual->izquierda;
                der->izquierda = izq;
                izq->derecha = der;

                //se elimina el nodo
                correcto = true;
                free(actual);
                break;
            }else if(actual->abajo != NULL && actual->derecha == NULL){
                //3er caso: tiene nodos hacia abajo pero no a la derecha.

                //movimiento vertical
                eColumna->acceso = actual->abajo;
                Nodo * ab = actual->abajo;
                ab->arriba = eColumna->acceso;

                //movimiento horizontal
                Nodo * izq = actual->izquierda;
                izq->derecha = NULL;

                //se elimina el nodo
                correcto = true;
                free(actual);
                break;
            }else if(actual->abajo == NULL && actual->derecha != NULL){
                //4to caso: tiene nodos hacia la derecha pero no hacia abajo.

                if(actual->columna == columna && actual->fila != fila){
                    while(eFila->id != fila){
                        eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                    }
                }

                //movimiento vertical
                eColumna->acceso->abajo = NULL;

                //movimiento horizontal
                Nodo * der = actual->derecha;
                der->izquierda = actual->izquierda;
                actual->izquierda = der;

                //se elimina el nodo
                correcto = true;
                free(actual);
                break;
            }else{
                //5to caso: no tiene nodos a la derecha ni hacia abajo.

                if(actual->columna == columna && actual->fila != fila){
                    while(eFila->id != fila){
                        eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                    }
                }

                //movimiento vertical
                eColumna->acceso->abajo = NULL;

                //movimiento horizontal
                Nodo * izq = actual->izquierda;
                izq->derecha = NULL;

                //se elimina el nodo
                correcto = true;
                free(actual);
                break;
            }
        }else{
            /*como no es el primero recorremos el resto de la matriz*/

            while(actual != NULL)
            {
                if(strcmp(actual->valor, dato) == 0 && actual->fila == fila && actual->columna == columna){
                    /*encuentra el dato*/

                    if(actual->abajo != NULL && actual->derecha != NULL){
                        //1er caso: tiene nodos a la derecha y abajo.

                        //moviendo vertical
                        Nodo * ar = actual->arriba;
                        Nodo * ab = actual->abajo;
                        ar->abajo = ab;
                        ab->arriba = ar;

                        //movimiento horizontal
                        Nodo * de = actual->derecha;
                        Nodo * izq = actual->izquierda;
                        de->izquierda = izq;
                        izq->derecha = de;

                        //eliminar nodo
                        correcto = true;
                        free(actual);
                        break;
                    }else if(actual->abajo != NULL && actual->derecha == NULL){
                        //2do caso: tiene nodos hacia abajo pero no a la derecha.

                        //movimiento vertical
                        Nodo * ar = actual->arriba;
                        Nodo * ab = actual->abajo;
                        ar->abajo = ab;
                        ab->arriba = ar;

                        //movimiento horizontal
                        Nodo * izq = actual->izquierda;
                        izq->derecha = NULL;

                        //eliminar nodo
                        correcto = true;
                        free(actual);
                        break;
                    }else if(actual->abajo == NULL && actual->derecha != NULL){
                        //3er caso: tiene nodos hacia la derecha pero no hacia abajo.

                        if(actual->columna == columna && actual->fila != fila){
                            while(eFila->id != fila){
                                eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                            }
                        }

                        if(actual->izquierda == eFila->acceso){
                            //movimiento vertical
                            Nodo * ar = actual->arriba;
                            ar->abajo = NULL;

                            //movimiento horizontal
                            Nodo * de = actual->derecha;
                            de->izquierda = eFila->acceso;
                            eFila->acceso->derecha = de;

                            //eliminar nodo
                            correcto = true;
                            free(actual);
                            break;
                        }else{
                            //movimiento vertical
                            Nodo * ar = actual->arriba;
                            ar->abajo = NULL;

                            //movimiento horizontal
                            Nodo * izq = actual->izquierda;
                            Nodo * de = actual->derecha;
                            izq->derecha = de;
                            de->izquierda = izq;

                            //eliminar nodo
                            correcto = true;
                            free(actual);
                            break;
                        }
                    }else if(actual->derecha == NULL && actual->abajo == NULL){
                        //4to caso: no tiene nodos a la derecha ni hacia abajo.
                        if(actual->columna == columna && actual->fila != fila){
                            while(eFila->id != fila){
                                eFila = eFila->siguiente; //se mueve la ubicacion de la fila
                            }
                        }

                        if(actual->arriba == eColumna->acceso){
                            //unico nodo en la columna

                            //movimiento vertical
                            eColumna->acceso->abajo = NULL;

                            //movimiento horizontal
                            Nodo * izq = actual->izquierda;
                            izq->derecha = NULL;

                            //eliminar nodo
                            correcto = true;
                            free(actual);
                            break;
                        }else{
                            //arriba del nodo hay otro nodo

                            //movimiento vertical
                            Nodo * ar = actual->arriba;
                            ar->abajo = NULL;

                            //movimiento horizontal
                            Nodo * izq = actual->izquierda;
                            izq->derecha = NULL;

                            //eliminar nodo
                            correcto = true;
                            free(actual);
                            break;
                        }
                    }else{
                        cout << "falta validacion" << endl;
                    }
                }else{
                    /*el dato no coincide continua hacia abajo de la columna
                     * y se avanza el numero de fila
                     * */

                    actual = actual->abajo;
                    eFila = eFila->siguiente;
                }
            }//fin segundo while

        }//fin primer if

        if(correcto == true){
            /*borro el nodo detiene el primer while*/
            break;
        }else{
            /*no encontro nada en una columna avanza a la siguiente*/
            eColumna = eColumna->siguiente;
            eFila = eFilas->primero;
        }

    }//fin primer while
}

void Matriz::recorrerFilas()
{
    Encabezado * eFila = eFilas->primero;
    cout << "Recorrido Por Filas: ";

    while(eFila != NULL)
    {
        Nodo * actual = eFila->acceso;
        while(actual != NULL)
        {
            cout << actual->valor;

            if(eFila->siguiente != NULL || actual->derecha != NULL)
            {
                cout << "->";
            }

            actual = actual->derecha;
        }

        eFila = eFila->siguiente;
    }

    cout << endl;
}

void Matriz::recorrerColumnas()
{
    Encabezado * eColumna = eColumnas->primero;
    cout << "Recorrido Por Columnas: ";

    while(eColumna != NULL)
    {
        Nodo * actual = eColumna->acceso;
        while(actual != NULL)
        {
            cout << actual->valor;

            if(eColumna->siguiente != NULL || actual->abajo != NULL)
            {
                cout << "->";
            }

            actual = actual->abajo;
        }

        eColumna = eColumna->siguiente;
    }

    cout << endl;
}
