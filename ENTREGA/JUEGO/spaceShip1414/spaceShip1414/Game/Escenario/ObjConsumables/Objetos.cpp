
#include "Objetos.h"
#include "../Fisicas/Entity2D.h"
#include "../Fisicas/Mundo.h"
#include "../graphicEngine/TGraphicEngine.h"


Objetos::Objetos(const glm::vec3 & posicion, const glm::vec3 & rotacion, const glm::vec3 & escala, const int & identificacion, TGraphicEngine *motor)
{
	pos = posicion;
	rot = rotacion;
	esca = escala;
	ID = identificacion;
	engine = motor;
	motor->escalar(nodo, esca.x, esca.y, esca.z);
	motor->trasladar(nodo, pos.x, pos.y, pos.z);
	motor->rotarYPR(nodo, rot.y, rot.x, rot.z);


}

Objetos::~Objetos() {

	//destroyEntidades();

}

void Objetos::destroyEntidades()
{
	//if (maya != nullptr && entity != nullptr) {
	//	maya->getParent()->removeChild(maya);
	//	delete(entity);
	//}
	//maya = nullptr;
	entity = nullptr;
}

glm::vec3 Objetos::getPos()
{
	return pos;
}

glm::vec3 Objetos::getRot()
{
	return rot;
}

glm::vec3 Objetos::getEscala()
{
	return esca;
}

int Objetos::getID()
{
	return ID;
}

void Objetos::setFisica(Mundo * world)
{

}

bool Objetos::getVivo() {
	return entity->getLive();
}

void Objetos::rotation(TGraphicEngine * motorApp, float a, float x, float y, float z)
{
	motorApp->rotar(nodo, a, x, y, z);
}

void Objetos::rotationYPR(TGraphicEngine * motorApp, float y, float p, float r)
{
	motorApp->rotarYPR(nodo, y, p, r);
}

void Objetos::scale(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->escalar(nodo, x, y, z);
}

void Objetos::translation(TGraphicEngine * motorApp, float x, float y, float z)
{
	motorApp->trasladar(nodo, x, y, z);
}

TNodo * Objetos::getNodo()
{
	return nodo;
}
