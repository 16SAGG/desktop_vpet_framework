#pragma once
#ifndef WINDOW_COLLIDABLE_CLASS_H
#define WINDOW_COLLIDABLE_CLASS_H

#include <memory>
#include <windows.h>

#include "wall.h"

class CollisionBox;

/**
* @brief Entidad asociada a una ventana activa para darle colision
*/
class WindowCollidable : public Wall {
private:
    //Referencia a la ventana utilizada de base para esta entidad. Tipo HWND
    HWND hwnd;
public:
    /*
    * @brief Constructor por defecto de la clase WindowCollidable
    * @param _hwnd Referencia a la ventana utilizada de base para esta entidad. Tipo HWND
    * @param _collider Referencia al CollisionBox de la entidad. Tipo CollisionBox
    */
    WindowCollidable(HWND _hwnd, std::shared_ptr<CollisionBox> _collider) : Wall(_collider), hwnd(_hwnd) {
        setOneWayCollisionDirection({ 0, -1 });
    };

    /*
    * @brief Actualiza las caracteristicas (tamano y posicion) de la entidad en funcion de la ventana usada como referencia
    */
    void updateBounds();

    //GETTER

    /*
    * @brief Obtiene le HWND de la entidad
    */
    HWND getHwnd() const { return hwnd; };
};
#endif
