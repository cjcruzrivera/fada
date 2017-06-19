/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: camilojcr
 *
 * Created on 15 de junio de 2017, 11:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void cargaArchivo(string dir);
void solIngenua();

int numLibros;
int numEscritores;
vector<string> libros;
vector<int> paginas;
vector<vector> posiblesSol;
/*
 * 
 */
int main(int argc, char** argv) {
    
    string direccion;
    cout << "Ingrese la direccion del archivo a cargar: "<<endl;
    cin >> direccion;
    
    cargaArchivo(direccion);
    
    
//    bool opc =true;
//    
//    while(opc){
//        
//        int selec;
//        cout << endl << "Ingrese 1 para la solución INGENUA "<< endl << "Ingrese 3 para la solución DINAMICA "<< endl << "Ingrese 2 para la solución VORAZ "<< endl ; 
//        cin >> selec;
//
//        switch(selec){
//            case 1:
//                cout << "Aqui ira la solucion ingenua";
//                solIngenua();
//                opc = false;
//                break;
//            case 2:
//                cout << "Aqui ira la solucion dinamica";
//                opc = false;
//                break;
//            case 3:
//                cout << "Aqui ira la solucion voraz";
//                opc = false;
//                break;
//            default:
//                cout << "Ingrese una opcion válida" ;
//                break;
//        }
//    
//    }
//    //
    
    return 0;
}


void split(const string& s, char delim,vector<string>& v) {
    int i = 0;
    int pos = s.find(delim);
    while (pos != string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);

      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
}

void solIngenua(){
    
    
    

}

void cargaArchivo(string dir){
    
    ifstream archivo;
    string direccion = dir+".txt";
    archivo.open(direccion.c_str(),ios::in);
    
    if (archivo.fail()) {
        cout << "ERROR AL LEER EL ARCHIVO";
        exit(1);
    } 
    
    bool boolean = true;
    int cont = 0;
    
    while(!archivo.eof()){
        if(boolean){
            string aux;
            getline(archivo,aux);
            vector<string> tokens;
            split(aux,' ',tokens);
            numEscritores = atoi(tokens[0].c_str());
            numLibros = atoi(tokens[1].c_str());
            cout << "El número de escritores es: " << numEscritores << endl << "El número de libros es: " << numLibros << endl;
            boolean = false;
        }
        string auxiliar;
        getline(archivo,auxiliar);
        vector <string> tok;
        split(auxiliar,' ',tok);
        libros.push_back(tok[0]);
        paginas.push_back(atoi(tok[1].c_str()));
        cout <<"Titulo: " <<libros[cont]<<" Numero de paginas: " << paginas[cont] <<endl;
        cont++;
    }

    archivo.close();
    
}