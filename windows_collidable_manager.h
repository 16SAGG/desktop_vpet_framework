#pragma once
#ifndef WINDOWS_COLLIDABLE_MANAGER_CLASS_H
#define WINDOWS_COLLIDABLE_MANAGER_CLASS_H

#include <Windows.h>
#include <memory>
#include <vector>

class Window;
class Wall;
class WindowCollidable;

/**
* @brief Crea y gestiona las ventanas con colision
*/
class WindowsCollidableManager
{
private:
    // Referencia a la ventana que encapsula este objeto.
    Window& window;

    // Lista de todas las ventanas colisionables activas. Tipo std::vector<std::shared_ptr<WindowCollidable>>
    std::vector<std::shared_ptr<WindowCollidable>> activeWindows;
public:
    /*
    * @brief Constructor de WindowsCollidableManager
    */
    WindowsCollidableManager(Window& _window): window(_window) {}
    
    /*
    * @brief Sincroniza todas las ventanas activas del SO al motor fisicas del juego
    */
    void syncWindows();

    /*
	* @brief Comprueba si una ventana es valida para colisionar
    * Contiene IsWindow(hwnd) para verificar si la ventana existe
	* IsWindowVisible(hwnd) es una marca del SO para ventanas que son visibles
    * IsIconic(hwnd) comprueba si esta minimizada
    * DWMWA_CLOAKED es un atributo de una ventana oculta por el sistema (por eso cloaked != 0)
	* Comprueba con GetWindowRect si el tamaño de la ventana es mayor a 0
	* GetWindowLong(hwnd, GWL_STYLE) Obtiene las flags de estilo de la ventana, si no tiene WS_VISIBLE no es visible
    * if (wp.showCmd == SW_SHOWMINIMIZED) comprueba de nuevo si esta minimizado
    * if (wp.showCmd == SW_SHOWMAXIMIZED) comprueba de nuevo si esta maximizado
	* WS_EX_TOOLWINDOW y WS_EX_NOACTIVATE son estilos de ventana que no se deben colisionar
	* if (GetWindowTextA(hwnd, title, sizeof(title)) == 0) Es para verificar si la ventana tiene titulo, si no tiene titulo no se colisiona
	* Si cumple alguno de estos criterios, no es una ventana valida para colisionar
    */
    bool isValidWindow(HWND hwnd);

    /*
	* @brief Elimina todas las ventanas que no son validas para colisionar del motor de fisicas y de la lista de ventanas activas
    */
    void cleanupInactiveWindows();

    /*
    * @brief Actualiza las propiedades de las ventanas colisionables activas
    */
    void updateAllVisibleWindows();

    /*
    * @brief Incluye o actualiza las propiedades de una ventana colisionable.
    * @param hwnd Es la referencia a la ventana. Tipo HWND
    */
    void addOrUpdateWindow(HWND hwnd);

    //GETTER

    /*
    * @brief Obtiene las ventanas activas. Tipo std::vector<std::shared_ptr<WindowCollidable>>
    */
    std::vector<std::shared_ptr<WindowCollidable>>& getActiveWindows() { return activeWindows; };

};
#endif