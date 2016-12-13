/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   readJson.h
 * Author: Hector
 *
 * Created on 30 de noviembre de 2016, 0:21
 */


#ifndef READJSON_H
#define READJSON_H

#include "../rapidjson/document.h"
#include <iostream>
#include <list>
#include "escenario/Pared.h"
#include "escenario/Escenario.h"

using namespace rapidjson;
using namespace std;


class readJson {
public:
    readJson(Escenario *e);
    readJson(const readJson& orig);
    virtual ~readJson();
    void leerArchivo(const char* rutaArchivo);
    void crearPared();
    std::list<Pared*> getParedes();
    
private:
    Document d;
    std::list<Pared*> paredes;
    Escenario *esce;
};

#endif /* READJSON_H */

