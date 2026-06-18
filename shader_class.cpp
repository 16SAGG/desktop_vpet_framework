#include "shader_class.h"

/**
 * @brief Lee un archivo completo y lo devuelve como una cadena de texto (std::string).
 * * Utiliza operaciones de flujo de archivos para posicionarse al final, medir el tamaño,
 * y cargar todo el contenido de una sola vez de forma eficiente.
 * * @param filename Ruta del archivo a leer. Tipo char*
 * @return std::string con el contenido del archivo.
 * @throws errno Si el archivo no puede abrirse.
 */
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

/**
 * @brief Compila, vincula y crea un programa de shader desde archivos externos.
 * * Este proceso es el pipeline estándar de creación de shaders en OpenGL:
 * 1. Carga: Lee el código fuente (.vert y .frag) del disco.
 * 2. Compilación: Traduce el código de alto nivel (GLSL) a código máquina de la GPU.
 * 3. Vinculación (Linking): Une ambos shaders en un solo programa ejecutable (ID).
 * 4. Limpieza: Elimina los objetos shader individuales ya que su código ya reside en el programa.
 * * @param vertexFile Ruta del archivo al codigo fuente del Vertex Shader. Tipo char*
 * @param vertexFile Ruta del archivo al codigo fuente del Fragment Shader. Tipo char*
 */
Shader :: Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	compileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	compileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

/**
 * @brief Activa el shader
 **/
void Shader::activate() const
{
	glUseProgram(ID);
}

/**
 * @brief Elimina el shader
 **/
void Shader::deleteShader() const
{
	glDeleteProgram(ID);
}

/**
 * @brief Verifica si hubo errores durante la compilación o vinculación del shader.
 * * Dado que OpenGL es una API de C de bajo nivel, no lanza excepciones al fallar.
 * Debemos consultar manualmente el "log" (registro) de errores de la GPU.
 * * @param shader El ID del objeto (shader o programa) a verificar. Tipo unsigned int
 * @param type Etiqueta para saber qué estamos verificando ("VERTEX", "FRAGMENT" o "PROGRAM"). Tipo char*
 */
void Shader::compileErrors(unsigned int shader, const char* type) const
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}