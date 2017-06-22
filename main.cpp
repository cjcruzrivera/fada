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


struct division{
    int inicio;
    int final;
};

int numLibros;
int numEscritores;
vector<string> libros;
vector<int> paginas;
vector<vector<division> > posiblesSol;
/*
 * 
 */
int main(int argc, char** argv) {
    
    string direccion;
    cout << "Ingrese la direccion del archivo a cargar: "<<endl;
    cin >> direccion;
    
    cargaArchivo(direccion);
    
    
    bool opc =true;
    
    while(opc){
        
        int selec;
        cout << endl << "Ingrese 1 para la solución INGENUA "<< endl << "Ingrese 3 para la solución DINAMICA "<< endl << "Ingrese 2 para la solución VORAZ "<< endl ; 
        cin >> selec;

        switch(selec){
            case 1:
                cout << "La solución optima calculada de forma exhaustiva es la siguiente:"<<endl;
                solIngenua();
                opc = false;
                break;
            case 2:
                cout << "Aqui ira la solucion dinamica";
                opc = false;
                break;
            case 3:
                cout << "Aqui ira la solucion voraz";
                opc = false;
                break;
            default:
                cout << "Ingrese una opcion válida" ;
                break;
        }
    
    }
    //
    
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



void extraerPosiblesSol(int escritor,int libros,vector<division> librosSel){

	if (!(escritor==0 and libros!=0) and !(escritor!=0 and libros ==0)){

		if(escritor==0 and libros==0){
			posiblesSol.push_back(librosSel);

		}else{

			for(int i=1;i<=libros;i++){
				vector<division>  auxSol = librosSel;
				division selec;
                                selec.inicio = i;
                                selec.final = libros;
				auxSol.push_back(selec);
				extraerPosiblesSol(escritor-1,i-1,auxSol);

			}
		}
	}
}    
    


int calcTiempo(division div){
    
    int tiempo =0;
    for(int i = div.inicio; i<=div.final ;i++){
        tiempo = tiempo + paginas[i-1];
    }
    
    return tiempo;
}
    
int calcularTiempo(vector<division> sol){
    int tiempo = 0;
    
    for(int i = 0; i < sol.size();i++){
        if(calcTiempo(sol[i]) > tiempo){
            tiempo = calcTiempo(sol[i]);
        }
    }
    
    return tiempo;
}
    


void solIngenua(){
    
    extraerPosiblesSol(numEscritores,numLibros,vector<division>());
    
    vector<division> solucion;
    int tiempoMin =0;
    
    for(int i = 0; i<posiblesSol.size();i++){
        
        if(i==0){
           tiempoMin = calcularTiempo(posiblesSol[i]);
           solucion = posiblesSol[i];
        }else if(tiempoMin > calcularTiempo(posiblesSol[i])){
            tiempoMin = calcularTiempo(posiblesSol[i]);
            solucion = posiblesSol[i];
        }
    }
    cout<<"El tiempo total sera de "<<tiempoMin<<" dias."<<endl<<"Y se distribuira el trabajo de la siguiente forma:"<<endl;
    
    for(int j = 0;j<solucion.size();j++){
        if(solucion[j].inicio == solucion[j].final){
            cout << "Al escritor número "<< j+1 << " se le asignara el siguiente libro:"<<endl<<"Título: " << libros[solucion[j].inicio - 1]<<endl;
        }else{
            cout << "Al escritor número "<< j+1 << " se le asignaran los siguientes libros:"<<endl;
            for(int k = solucion[j].inicio;k<=solucion[j].final ;k++){
                cout << "Título: " << libros[k-1]<<endl;
            }       
        }
    }  
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