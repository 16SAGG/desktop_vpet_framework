#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include <glad/glad.h>


std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;

	Shader(const char* vertexFile, const char* fragmentFile);

	void activate() const;
	void deleteShader() const;

private:
	void compileErrors(const unsigned int shader, const char* type) const;
};
#endif