#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct repuesto{
    char codigo_marca[10];
    char descripcion[20];
}repuesto;

struct indice{
    char codigo[10];
    int posicion;
}indice;

int main(){

    ifstream arcM;
    ofstream arcI;

    arcM.open("repuestos_marcas.dat", ios::binary);
    arcI.open("marcas_indice.inx", ios::binary | ios::app);

    while(!arcM.read((char*)  &repuesto, sizeof(repuesto)).eof()){

        indice.posicion = arcM.tellg();
        strcpy(indice.codigo, repuesto.codigo_marca);
        arcI.write((char*) &indice, sizeof(indice));
    }

    arcM.close();
    arcI.close();

    return 0;
}