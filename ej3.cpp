#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

struct repuestoR{
    char codigoA[10];
    char descripcion[50];
    char codigo_marca[10];
} repuesto;

struct Indice {
    char codigo[10];
    int posicion;
} indice;

void registro(string nombre);
void generarInxA(string nombre);
void generarInxB(string nombre);
void busquedaMenu();
void busquedaBinaria(string rubro, char codigo_busqueda[10]);

int main(){
    string nombre;
    nombre = "";
    char decision[2];

    do{
        cout << "Registrar repuestos por rubro" << endl;
        cout << "Automotor [A]" << endl;
        cout << "Motos     [M]" << endl;
        cout << "Nautica   [N]" << endl;
        cout << "Varios    [V]" << endl;
        cout << "Salir     [S]" << endl;

        cin >> decision; 

        if(strcmp(decision, "A") == 0){
            nombre = "automotor";
            registro(nombre);
            generarInxB(nombre);
        } else if(strcmp(decision, "M") == 0){
            nombre = "motos";
            registro(nombre);
            generarInxB(nombre);
        } else if(strcmp(decision, "N") == 0){
            nombre = "nautica";
            registro(nombre);
            generarInxB(nombre);
        } else if(strcmp(decision, "V") == 0){
            nombre = "varios";
            registro(nombre);
            generarInxB(nombre);
        } else if(strcmp(decision, "S") == 0){
            cout << "Programa finalizado" << endl;
        } else {
            cout << "Opcion incorrecta" << endl;
        }

        

    }while(strcmp(decision, "S") == 0);

    return 0;
}

void registro(string nombre){
    ofstream arch;
    arch.open(nombre + ".dat", ios::binary);

    cout << "Ingrese codigo" << endl;
    cin >> repuesto.codigoA;
    cout << "Ingrese descripcion del repuesto" << endl;
    cin >> repuesto.descripcion;
    cout << "Ingrese el codigo de la marca" << endl;
    cin >> repuesto.codigo_marca;

    arch.write((char*) &repuesto, sizeof(repuesto));
    arch.close();
    generarInxA(nombre);
}

void generarInxA(string nombre){
    ifstream arch;
    ofstream archI;

    arch.open(nombre + ".dat", ios::binary);
    archI.open(nombre + ".inx", ios::binary | ios::app);

    while(!arch.read((char*) &repuesto, sizeof(repuesto)).eof()){

        indice.posicion = arch.tellg();
        strcpy(indice.codigo, repuesto.codigoA);
        archI.write((char*) &indice, sizeof(indice));
    }

    arch.close();
    archI.close();
}

void generarInxB(string nombre){
    ifstream archR;
    ofstream archI;

    archR.open(nombre + ".dat", ios::binary);
    archI.open("indice_unico.inx", ios::binary | ios::app);

    while(!archR.read((char*) &repuesto, sizeof(repuesto)).eof()){
        indice.posicion = archR.tellg();
        strcpy(indice.codigo, repuesto.codigoA);
        archI.write((char*) &indice, sizeof(indice));
    }

}

void ordenamiento(string nombre){
    struct Indice inx;
    struct Indice inxAux;

    fstream archInx;
    archInx.open(nombre + ".inx", ios::in | ios::out |  ios::binary | ios::app | ios::ate);

    int i, j;
    int ielementos = archInx.tellg() / sizeof(Indice);

    for(i = 1; i < ielementos; i++){
        for(j = 0; j < ielementos-i; j++){

            archInx.seekg(j*sizeof(Indice));
            archInx.read((char*) &inxAux, sizeof(Indice));
            archInx.read((char*) &inx, sizeof(Indice));

            if(strcmp(inxAux.codigo, inx.codigo) == -1){
                archInx.seekp(j*sizeof(Indice));
                archInx.write((char*) &inx, sizeof(Indice));
                archInx.write((char*) &inxAux, sizeof(Indice));
            }
        }
    }

    archInx.close();
}

//opcion de busqueda para inx A por codigo y rubro
//opcon de busqueda para inx B por codigo

void busquedaMenu(){
    int deciB;
    int deciB2;
    char codigo_busqueda[10];
    string rubro;

    while(deciB != 0){
        cout << "Que desea buscar?" << endl;
        cout << "[1] Buscar en indice A" << endl;
        cout << "[2] Buscar en indice B" << endl;
        cout << "[0] Salir" << endl;
        cin >> deciB;

        if(deciB == 1){
            cout << "Busqueda en indice A por codigo y rubro" << endl;
            cout << "Ingrese el rubro en el que desea buscar" << endl;
            cin >> rubro;

            if(rubro.compare("automotor") == 0){

                cout << "Introduzca el codigo que desea buscar" << endl;
                cin >> codigo_busqueda;
                busquedaBinaria(rubro, codigo_busqueda);

            } else if(rubro.compare("motos") == 0){

                cout << "Introduzca el codigo que desea buscar" << endl;
                cin >> codigo_busqueda;
                busquedaBinaria(rubro, codigo_busqueda);

            } else if(rubro.compare("nautica") == 0){

                cout << "Introduzca el codigo que desea buscar" << endl;
                cin >> codigo_busqueda;
                busquedaBinaria(rubro, codigo_busqueda);

            } else if(rubro.compare("varios") == 0){

                cout << "Introduzca el codigo que desea buscar" << endl;
                cin >> codigo_busqueda;
                busquedaBinaria(rubro, codigo_busqueda);

            } else {
                cout << "No se encontro el rubro especificado" << endl;
            }

        } else if(deciB == 2){
            cout << "Busqueda en indice B por codigo" << endl;
            cout << "Introduzca el codigo que desea buscar" << endl;
            cin >> codigo_busqueda;
        }
    }
}

void busquedaBinaria(string rubro, char codigo_busqueda[10]){

    ifstream archInx;
    archInx.open(rubro + ".inx", ios::binary);
    struct Indice inx;
    struct repuestoR rep;

    int n;
    int medio;
    int inicio = 0;
    int fin = (sizeof(archInx)/sizeof(repuestoR)) - 1;
    int encontrado = 0;

    while(inicio <= fin){

        medio = (fin + inicio) / 2;

        archInx.seekg(medio * sizeof(repuestoR));
        archInx.read((char*) &inx, sizeof(inx));

        if(strcmp(inx.codigo, codigo_busqueda) == 0){
            ifstream archRep;

            archRep.open(rubro + ".dat", ios::binary);
            archRep.seekg(inx.posicion);
            archRep.read((char*) &rep, sizeof(repuestoR));

            cout << "Codigo alpha: " << rep.codigoA << endl;
            cout << "Codigo de marca: " << rep.codigo_marca << endl;
            cout << "Descripcion: " << rep.descripcion << endl;

            archRep.close();

            encontrado = 1;
            fin = -1;
        } else {
            if(strcmp(codigo_busqueda, inx.codigo) == -1){
                fin = medio - 1;
            } else {
                inicio = medio + 1;
            }
        }
    }

    if(encontrado != 1){
        cout << "No se encontro el repuesto" << endl;
    }

    archInx.close();
}