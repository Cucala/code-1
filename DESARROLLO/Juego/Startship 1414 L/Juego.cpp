/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: Hector
 * 
 * Created on 19 de diciembre de 2016, 22:22
 */



#include "Juego.h"

#define ANCHO 1920
#define LARGO 1080

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


Juego::Juego() {
  
}

Juego::Juego(std::string name) : EstadoGeneral(name){
}

Juego::~Juego() {
}

void Juego::StarUP(IrrlichtDevice* iDevice)
{
    iDevice->setEventReceiver(&teclado);
    driver = iDevice->getVideoDriver();
    smgr = iDevice->getSceneManager();
    guienv = iDevice->getGUIEnvironment();
    world = new b2World(gravity);
    contactListenerInstance =  new MiContactListener();
    filtroContact = new MyContactFilter();
    gravity.Set(0.0f, 0.0f);
    
    world->SetContactListener(contactListenerInstance);
    world->SetContactFilter(filtroContact);
    
    iDevice->setWindowCaption(L"Movimiento del personaje");

    guienv->addStaticText(L"Movimiento del personaje",
            rect<s32>(10, 10, 260, 22), true); //metodo para poner algo por pantalla
    //cambiar la camara activa smgr->setActiveCamera(camera);
    lastFPS = 0;
    pers = new Personaje(smgr, driver, world); //el cubo que se crea es de 10x10x10 10px = 1m
    esce = new Escenario(smgr, driver, world);
   // ene = new Enemigo(smgr, driver, world, vector3df(0,10,40));
    esce->fabricaDeEnemigos(smgr, driver, world);
    esce->crearLLave(smgr, driver, world);
    json = new readJson(esce);
    cam = new Camara(smgr, pers->getPos());
    
    then = iDevice->getTimer()->getTime();
    estado = 0;
    i=0;
    up=300;
}


void Juego::Dentro(void)
 {
 	//set up gui
 }
 
 void Juego::Fuera(void)
 {
 	//restore playerdata
 }
 
 bool Juego::OnEvent(const SEvent &event)
 {
 	//handle user input
 	return(false);
 }
 
 void Juego::render(IrrlichtDevice* iDevice)
 {
     
     if(control==false)
     {  
         
         
         this->StarUP(iDevice);
         control=true;
     }
     
     if (iDevice->isWindowActive()) {

        
            const u32 now = iDevice->getTimer()->getTime();
             
            const f32 dt = (f32) (now - then) / 1000.f;
            //float distancia;
            world->Step(dt, 6, 2); //1.0f/60.0f
            world->ClearForces();
           
            if(teclado.isKeyDown(irr::KEY_KEY_J)){
                estado = 0;
            }
            else if(teclado.isKeyDown(irr::KEY_KEY_K)){
                               estado = 1;

            }
            else if(teclado.isKeyDown(irr::KEY_KEY_L)){
                                estado = 2;

            }
//            else if(teclado.isKeyDown(irr::KEY_KEY_P)){
//                ene->Cambiar(4);
//            }
//            else if(teclado.isKeyDown(irr::KEY_KEY_O)){
//                ene->Cambiar(5);
//            }
            
            
           // ene->Update(pers);
             esce->actualizarListaEnemigos(estado);

             i++;
            guienv->clear();
           
            if(pers->p!=NULL){
              //  guienv->addStaticText(L"Pulsa la tecla I para abrir/cerrar la puerta",
            //rect<s32>(pers->getPos().X, pers->getPos().Z, pers->getPos().X+10, pers->getPos().Z+10), false);
                 IGUIStaticText* tex=guienv->addStaticText(L"Pulsa la tecla E para abrir/cerrar la puerta",
            rect<s32>(320, 240, 420, 260), true,true);
                tex->setOverrideColor(video::SColor(255,255,255,255));
                tex->setBackgroundColor(video::SColor(120,0,0,0));
                pers->p->Update();
                
            }
            
            if(pers->ultp!=NULL){
                if(pers->ultp->getEstado()!=0){
                    pers->ultp->Update();
                }
            }
            
            
            if(teclado.isKeyDown(irr::KEY_KEY_Q)&&i>up){
                
                pers->ModPuerta();
                i=0;
                
            }
            esce->actualizarListaLLaves();
            

            if (teclado.isKeyUp(irr::KEY_KEY_D) || teclado.isKeyUp(irr::KEY_KEY_A) || teclado.isKeyUp(irr::KEY_KEY_W) || teclado.isKeyUp(irr::KEY_KEY_S)) {
                pers->setVelocidad();
                cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);
            }

            if (teclado.isKeyDown(irr::KEY_KEY_W) && teclado.isKeyDown(irr::KEY_KEY_D)) {

                pers->moverPersonaje(4, dt);
                cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

                //cam->actualizarCamara(0, dt);
                //cam->actualizarCamara(2, dt);
            } else if (teclado.isKeyDown(irr::KEY_KEY_S) && teclado.isKeyDown(irr::KEY_KEY_D)) {

                pers->moverPersonaje(5, dt);
                            cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

               // cam->actualizarCamara(0, dt);
                //cam->actualizarCamara(3, dt);

            } else if (teclado.isKeyDown(irr::KEY_KEY_S) && teclado.isKeyDown(irr::KEY_KEY_A)) {

                pers->moverPersonaje(6, dt);
                            cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

               // cam->actualizarCamara(1, dt);
               // cam->actualizarCamara(3, dt);


            } else if (teclado.isKeyDown(irr::KEY_KEY_A) && teclado.isKeyDown(irr::KEY_KEY_W)) {

                pers->moverPersonaje(7, dt);
                            cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

               // cam->actualizarCamara(1, dt);
               // cam->actualizarCamara(2, dt);


            }// X + and -
            else if (teclado.isKeyDown(irr::KEY_KEY_D)) {

                    pers->moverPersonaje(0, dt);
                                cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

                 //   cam->actualizarCamara(0, dt);
              
            } 
               
            else if (teclado.isKeyDown(irr::KEY_KEY_A)) {

                pers->moverPersonaje(1, dt);
                            cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

                //cam->actualizarCamara(1, dt);

            }//Z + and -
            else if (teclado.isKeyDown(irr::KEY_KEY_W)) {

                pers->moverPersonaje(2, dt);
                            cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

                //cam->actualizarCamara(2, dt);
            } else if (teclado.isKeyDown(irr::KEY_KEY_S)) {

                pers->moverPersonaje(3, dt);
                            cam->actualizarCamara(pers->getPos(), pers->getRot(), dt);

                //cam->actualizarCamara(3, dt);

            }
            //recarga
            if(teclado.isKeyDown(irr::KEY_KEY_R)){
                pers->recargar();
            }
            
            if(teclado.isKeyDown(irr::KEY_ESCAPE)){
                 iDevice->closeDevice();
            }
            //cambio de arma
             
             if(teclado.isKeyDown(irr::KEY_KEY_1)){
                 if(pers->getArmaActual() != 0)
                 pers->setArmaActual(0);
             }
             
             else if(teclado.isKeyDown(irr::KEY_KEY_2)){
                 if(pers->getArmaActual() != 1)
                 pers->setArmaActual(1);
             }
             
             else if(teclado.isKeyDown(irr::KEY_KEY_3)){
                 if(pers->getArmaActual() != 2)
                    pers->setArmaActual(2);
             }
            /*
            if(teclado.isKeyDown(irr::KEY_KEY_Q) && now >= 5.0f){
                esce->spawnearEnemigo(smgr, driver, world);
                
            }*/
             
             //debug para la subida de las armas
             
             if(teclado.isKeyDown(irr::KEY_KEY_I)){
                 pers->subirCapacidadDeMun();
             }
             else if(teclado.isKeyDown(irr::KEY_KEY_O)){
                 pers->subirCargador();
             }
             
             else if(teclado.isKeyDown(irr::KEY_KEY_P)){
                 pers->subirNivelDamage();
             }
             
             
            //RATON
            vector3df mousePosition;
            // Create a ray through the mouse cursor.
            line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(teclado.GetMouseState().Position, smgr->getActiveCamera());
            // And intersect the ray with a plane around the node facing towards the camera.
            plane3df plane(mousePosition, vector3df(0, 0, -1));
            bool ok = plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition);
            mousePosition.X = teclado.GetMouseState().Position.X;
            mousePosition.Y = teclado.GetMouseState().Position.Y;
            pers->rotar(mousePosition);
            if (teclado.GetMouseState().LeftButtonDown && pers->getDisparo() == false) {
                //tiempoDisparo += dt;
                
                //pers -> disparar(dt,ok);
                //disparo = true;
                //Bala *bullet = new Bala(smgr, driver, world, pers, vector2df(teclado.GetMouseState().Position.X, teclado.GetMouseState().Position.Y));
                //listaBalas.push_back(bullet);
                //  }
                // }
                
                if(pers->getCargador() >= 0){
                    pers->disparar(smgr, driver, world, dt, vector2df(mousePosition.X, mousePosition.Y));

                }
            }
            

            if(pers->getDisparo() == true){
                pers->setTiempoDisparo(pers->getTiempoDisparo()+dt);
                if(pers->getTiempoDisparo() >= pers->getTiempoArma()){
                    pers->setDisparo(false);
                    pers->setTiempoDisparo(0);
                }
            }
            
            
            
             if (ok) {
    
                 pers->actualizarLista(dt);
               
            }
            

            
            then = now;

            driver->beginScene(true, true, SColor(255, 100, 101, 140)); //se usa para hacer el render

            smgr->drawAll(); //dibuja todo el grafo

            guienv->drawAll(); //dibujar el GUI

            driver->endScene(); //intercambia buffer
            
            int fps = driver->getFPS();
            if (lastFPS != fps)
            {
              core::stringw str = L"FPS: ";     
              str += fps;     

              iDevice->setWindowCaption(str.c_str());

              lastFPS = fps;
            }

        } else {
            iDevice->yield();
        }
 }
  