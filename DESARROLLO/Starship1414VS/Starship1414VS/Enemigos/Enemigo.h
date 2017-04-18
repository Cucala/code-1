#pragma once
/*
* To change this license header, choose License Headers in Project Properties.
* To change this template file, choose Tools | Templates
* and open the template in the editor.
*/

/*
* File:   Enemigo.h
* Author: Iv�n
*
* Created on 29 de noviembre de 2016, 17:52
*/


#include <iostream>
#include <irrlicht.h>
#include <Box2D\Box2D.h>
#include <list>
#include <vector>

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifndef ENEMIGO_H
#define ENEMIGO_H

class Nodo;
class AStar;
class Waypoints;
class Entity2D;
class Bala;
class LogicaDifusa;
class Flocking;

#define CRIA 10
#define BERSERKER 11
#define SOLDADO 12
#define JEFE 13

#define BUSCARPUNTO 0
#define PATRULLAR 1
#define ALERTA 2
#define ATACAR 3
#define ROTACION 4
#define DESCANSAR 5
#define ESCAPAR 6
#define CUERPOACUERPO 7
#define FLOCKING 8

//el enemigo deberia tener un estado que sea
//siguiendo al lider o algo para aplicar el flocking


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Enemigo {
public:
	Enemigo(ISceneManager* smgr, IVideoDriver* driver, b2World *world, vector3df posicion, Waypoints* puntos);
	// Enemigo(const Enemigo& orig);
	virtual ~Enemigo();

	virtual void Update(f32 dt);
	void Mover(vector3df u);
	void setVelocidad();
	virtual void Patrullar();
	virtual void Atacar(f32 dt);
	virtual void BuscarWaypoint();
	virtual void CQC() = 0;
	void setPos(vector3df pos);
	bool estaVivo();
	vector3df getPos();
	vector3df getVectorVel();
	float getVel();
	virtual void quitarVida(float damage) = 0;
	virtual void recuperarResistencia() = 0;

	float getVida();
	Entity2D*  getEntity();
	float getDamageChoque();
	void setEstado(int num);
	int getEstado();

	void setDisparo(bool x);
	void aumentarTiempoDisparo(float t);
	void resetTiempoDisparo();
	void setTime(f32 t);
	float getTiempoDisparo();
	bool getDisparado();
	void disparar(float dt);
	void actualizarLista();
	void setPosJugador(float x, float y);
	Nodo* getNodoInicio();
	Nodo* getNodoFin();
	void setPesoMaximoLogicaDifusa(float x);
	void iniLogicaDifusa();

	bool getVista();
	void setVista(bool x);
	bool getLider();

	void setGrupoFlocking(Entity2D * e);


protected:
	

	IMeshSceneNode *maya;
	float vel;
	vector3df vecVel;
	vector3df pos, rot, vectorUnitario;
	Entity2D *entity;
	int estadoActual;
	float vida;
	int raza;
	ITextSceneNode *GVida;
	ITextSceneNode *RVida;
	ISceneManager* smgr1;
	IVideoDriver* VD;
	b2World* mundo;
	float blindaje;
	Waypoints *waypoints;
	LogicaDifusa *logica;
	Flocking *floc;

	AStar *path;
	Nodo *puntoIni, *puntoFin, *nodoAnterior;
	int dir, posNodo;
	float damageChoque;
	float moral;
	float resistencia;
	bool vista;


	std::list<Bala*> listaBalas;
	std::vector<Nodo*> recorrido; //maximo 4 nodos
	bool disparado;
	float tiempoDisparo;
	vector2df posJugador;
	float damageBala;
	f32 time;


};

#endif /* ENEMIGO_H */

