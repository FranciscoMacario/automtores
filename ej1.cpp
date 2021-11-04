#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct repuestos{
    char codigo_marca[10];
    char descripcion[20];
};

int main(){
    struct repuestos repuesto;

    int salida = -1;
    char comparacion[2] = "0";

    while(salida != 0){
        cout << "Ingrese el codigo de marca(ingrese 0 para finalizar la carga)" << endl;
        cin >> repuesto.codigo_marca;
        if(strcmp(comparacion, repuesto.codigo_marca) == 0){
            salida = 0;
        } else {
            ofstream arc;
            arc.open("repuestos_marcas.dat", ios::binary);

            cout << "Ingrese una descripcion" << endl;
            cin >> repuesto.descripcion;

            arc.write((char*) &repuesto, sizeof(repuesto));
        }
    }

    return 0;
}