#include "tree.h"
#include <iostream>

using namespace std;

int main() {
    Tree<int> mafia;

    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║     SISTEMA DE SUCESIÓN MAFIOSA        ║" << endl;
    cout << "║     Familia Corleone y aliados         ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "Cargando datos desde CSV..." << endl;

    if (!mafia.loadFromCSV("../bin/data.csv")) {
        cout << "Error fatal: No se pudieron cargar los datos" << endl;
        cout << "Verifique que el archivo data.csv existe en la carpeta bin/" << endl;
        return 1;
    }

    cout << "Sistema iniciado correctamente" << endl;
    mafia.run();

    return 0;
}
