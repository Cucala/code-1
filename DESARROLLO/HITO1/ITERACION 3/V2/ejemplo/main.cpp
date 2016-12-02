#include <irrlicht.h>
#include <Box2D.h>
#include <iostream>
#include "CAppReceiver.h"
#include "Personaje.h"
#include "Escenario/Escenario.h"
#include "Camara.h"
#include "readJson.h"

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

int main() {

    CAppReceiver teclado;

    //creas una ventana, primer false es si quieres fullscreen
    IrrlichtDevice *device =
            createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
            false, false, false, &teclado);

    
    
    if (!device)
        return 1;


    b2Vec2 gravity(0.0f, 0.0f);
    b2World *world = new b2World(gravity);

    device->setWindowCaption(L"Movimiento del personaje");

    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager(); //grafo de la escena(controlador)
    IGUIEnvironment* guienv = device->getGUIEnvironment(); //hacer intrerfaces de usuario

    guienv->addStaticText(L"Movimiento del personaje",
            rect<s32>(10, 10, 260, 22), true); //metodo para poner algo por pantalla
    //cambiar la camara activa smgr->setActiveCamera(camera);

    Personaje *pers = new Personaje(smgr, driver, world); //el cubo que se crea es de 10x10x10 10px = 1m
    Escenario *esce = new Escenario(smgr, driver);
    Camara *cam = new Camara(smgr);
    //smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0)); //se añade una camara al grafo
    //esce->crearPared(vector3df(40,0,0), vector3df(90,-90,0));
   // esce->crearPared(vector3df(-40,0,0), vector3df(90,90,0));


    //primer parametro nodo padre, 0 el nodo raiz
    //primer vector posicion, segundo direccion

    u32 then = device->getTimer()->getTime();
    //const f32 MOVEMENT_SPEED = 100.f;

    while (device->run()) {

        if (device->isWindowActive()) {


            const u32 now = device->getTimer()->getTime();
            const f32 dt = (f32) (now - then) / 1000.f;
            world->Step(dt, 6, 2); //1.0f/60.0f
            world->ClearForces();

            if (teclado.isKeyUp(irr::KEY_KEY_D) || teclado.isKeyUp(irr::KEY_KEY_A) || teclado.isKeyUp(irr::KEY_KEY_W) || teclado.isKeyUp(irr::KEY_KEY_S)) {
                pers->setVelocidad();
            }

            if (teclado.isKeyDown(irr::KEY_KEY_W) && teclado.isKeyDown(irr::KEY_KEY_D)) {

                pers->moverPersonaje(4, dt);
                cam->actualizarCamara(0, dt);
                cam->actualizarCamara(2, dt);
            } else if (teclado.isKeyDown(irr::KEY_KEY_S) && teclado.isKeyDown(irr::KEY_KEY_D)) {

                pers->moverPersonaje(5, dt);
                cam->actualizarCamara(0, dt);
                cam->actualizarCamara(3, dt);

            } else if (teclado.isKeyDown(irr::KEY_KEY_S) && teclado.isKeyDown(irr::KEY_KEY_A)) {

                pers->moverPersonaje(6, dt);
                cam->actualizarCamara(1, dt);
                cam->actualizarCamara(3, dt);


            } else if (teclado.isKeyDown(irr::KEY_KEY_A) && teclado.isKeyDown(irr::KEY_KEY_W)) {

                pers->moverPersonaje(7, dt);
                cam->actualizarCamara(1, dt);
                cam->actualizarCamara(2, dt);


            }// X + and -
            else if (teclado.isKeyDown(irr::KEY_KEY_D)) {

                pers->moverPersonaje(0, dt);
                cam->actualizarCamara(0, dt);
            } else if (teclado.isKeyDown(irr::KEY_KEY_A)) {

                pers->moverPersonaje(1, dt);
                cam->actualizarCamara(1, dt);

            }//Z + and -
            else if (teclado.isKeyDown(irr::KEY_KEY_W)) {

                pers->moverPersonaje(2, dt);
                cam->actualizarCamara(2, dt);
            } else if (teclado.isKeyDown(irr::KEY_KEY_S)) {

                pers->moverPersonaje(3, dt);
                cam->actualizarCamara(3, dt);

            }

            //RATON
            vector3df mousePosition;
            // Create a ray through the mouse cursor.
            line3df ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(teclado.GetMouseState().Position, smgr->getActiveCamera());
            // And intersect the ray with a plane around the node facing towards the camera.
            plane3df plane(mousePosition, vector3df(0, 0, -1));
            plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition);

            pers->rotar(mousePosition);


            then = now;

            driver->beginScene(true, true, SColor(255, 100, 101, 140)); //se usa para hacer el render

            smgr->drawAll(); //dibuja todo el grafo

            guienv->drawAll(); //dibujar el GUI

            driver->endScene(); //intercambia buffer

        } else {
            device->yield();
        }
    }

    device->drop();

    return 0;
}
