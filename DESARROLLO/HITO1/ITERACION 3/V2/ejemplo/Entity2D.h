/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity2D.h
 * Author: User
 *
 * Created on 9 de diciembre de 2016, 15:52
 */

#ifndef ENTITY2D_H
#define ENTITY2D_H
#include <Box2D.h>
#include <irrlicht.h>
#include "RayCastCallback.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Entity2D {
public:
    Entity2D(b2World *world, vector3df pos);
    Entity2D(b2World* world, vector3df pos, vector3df rot, vector3df escala);
    Entity2D(b2World* world, vector3df pos, vector3df rot, vector3df escala, bool sensor);
    Entity2D(b2World* world, vector3df pos, vector3df rot,  bool vivo);
    Entity2D(const Entity2D& orig);
    virtual ~Entity2D();
    float rayCast(int modo);
    b2Body* getCuerpo2D();
    float rayCasting(b2Vec2 inicio, b2Vec2 fin);
    float llamarCallBack(RayCastCallback* callback, b2Vec2 inicio, b2Vec2 fin);
    int getIDEN();
    bool getLive();
    void setLive(bool x);
    
private:
    
    b2World *mundo;
    b2Body *body;
    b2BodyDef bodyDef;
    b2PolygonShape bodyShape;
    b2MassData md;
    b2Filter filtro;
    int iden;
    bool live;
};

#endif /* ENTITY2D_H */
