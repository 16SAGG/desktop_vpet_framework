#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <glad/glad.h>

/**
 * @brief Lee un archivo completo y lo devuelve como una cadena de texto (std::string).
 * * Utiliza operaciones de flujo de archivos para posicionarse al final, medir el tamaño,
 * y cargar todo el contenido de una sola vez de forma eficiente.
 * * @param filename Ruta del archivo a leer. Tipo char*
 * @return std::string con el contenido del archivo.
 * @throws errno Si el archivo no puede abrirse.
 */
std::string get_file_contents(const char* filename);

/**
 * @brief Compila, vincula y crea un programa de shader desde archivos externos.
 * * Este proceso es el pipeline estándar de creación de shaders en OpenGL:
 * 1. Carga: Lee el código fuente (.vert y .frag) del disco.
 * 2. Compilación: Traduce el código de alto nivel (GLSL) a código máquina de la GPU.
 * 3. Vinculación (Linking): Une ambos shaders en un solo programa ejecutable (ID).
 * 4. Limpieza: Elimina los objetos shader individuales ya que su código ya reside en el programa.
 */
class Shader
{
private:
	// Identificador de shader
	GLuint ID;

	/**
	 * @brief Verifica si hubo errores durante la compilación o vinculación del shader.
	 * * Dado que OpenGL es una API de C de bajo nivel, no lanza excepciones al fallar.
	 * Debemos consultar manualmente el "log" (registro) de errores de la GPU.
	 * * @param shader El ID del objeto (shader o programa) a verificar. Tipo unsigned int
	 * @param type Etiqueta para saber qué estamos verificando ("VERTEX", "FRAGMENT" o "PROGRAM"). Tipo char*
	 */
	void compileErrors(const unsigned int shader, const char* type) const;
public:
	/**
	 * @brief Constructor de shader
	 * * @param vertexFile Ruta del archivo al codigo fuente del Vertex Shader. Tipo char*
	 * @param vertexFile Ruta del archivo al codigo fuente del Fragment Shader. Tipo char*
	 */
	Shader(const char* vertexFile, const char* fragmentFile);

	/**
	 * @brief Activa el shader
	 **/
	void activate() const;
	/**
	 * @brief Elimina el shader
	 **/
	void deleteShader() const;

	//GETTERS

	/**
	 * @brief Obtiene el ID del shader
	 **/
	GLuint getID() const { return ID; };
};
#endif