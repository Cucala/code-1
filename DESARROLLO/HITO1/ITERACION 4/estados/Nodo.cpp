/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.cpp
 * Author: Iván
 * 
 * Created on 16 de diciembre de 2016, 16:28
 */

#include "Nodo.h"


Nodo::Nodo() {
    
        
    
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::~Nodo() {
}

bool Nodo::Ejecutar(){
     //std::cout<<"El nodo funciona."<<std::endl;
    bool result=false;
    std::cout<<hijos.size()<<std::endl;
    if(hijos.empty()){
        //std::cout<<"No hay hijos"<<std::endl;
    }
    else{
    for(std::list<Nodo>::iterator it=hijos.begin();it!=hijos.end();it++) {
        result=(*it).Ejecutar();
    }
    }
    return result;
}

void Nodo::Extra(Nodo* n){
    hijos.push_front(*n);
}