#include <iostream>
#include <MatrizOrtogonal.h>

using namespace std;

int main()
{
    Matriz * matriz = new Matriz();
    matriz->insertar(1, 0, "Silla");
    matriz->insertar(2, 1, "Arbol");
    matriz->insertar(0, 1, "Casa");
    matriz->insertar(3, 3, "123");
    matriz->insertar(1, 2, "Zapato");
    matriz->insertar(0, 2, "Mesa");
    matriz->insertar(0, 0, "Avion");
    matriz->insertar(1, 1, "Hola");
    matriz->insertar(0, 3, "xD");
    matriz->insertar(1, 3, "algo");
    matriz->insertar(3, 1, "Tucan");

    matriz->recorrerFilas();
    matriz->recorrerColumnas();

    matriz->eliminar(0, 0, "Avion");
    matriz->recorrerFilas();
    matriz->recorrerColumnas();
    matriz->insertar(0,0, "Avion");
    matriz->recorrerFilas();
    matriz->recorrerColumnas();

    matriz->eliminar(1, 2, "Zapato");
    matriz->recorrerColumnas();
    delete matriz;
    return 0;
}

