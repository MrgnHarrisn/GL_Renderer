#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // Read shader files
    string vertexCode, fragmentCode;
    ifstream vShaderFile, fShaderFile;

    // Enable exception handling for files
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure& e) {
        cerr << "ERROR::SHADER::FILE_READ_FAILED: " << e.what() << endl;
        throw runtime_error("Shader file error");
    }

    const char* vShaderData = vertexCode.c_str();
    const char* fShaderData = fragmentCode.c_str();

    // Compile shaders
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    if (!vertex) {
        cerr << "ERROR::SHADER::VERTEX_SHADER_CREATION_FAILED" << endl;
        throw runtime_error("Shader creation error");
    }
    glShaderSource(vertex, 1, &vShaderData, nullptr);
    glCompileShader(vertex);
    check_error(vertex, GL_COMPILE_STATUS, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragment) {
        cerr << "ERROR::SHADER::FRAGMENT_SHADER_CREATION_FAILED" << endl;
        glDeleteShader(vertex);
        throw runtime_error("Shader creation error");
    }
    glShaderSource(fragment, 1, &fShaderData, nullptr);
    glCompileShader(fragment);
    check_error(fragment, GL_COMPILE_STATUS, "FRAGMENT");

    // Create shader program
    ID = glCreateProgram();
    if (!ID) {
        cerr << "ERROR::SHADER::PROGRAM_CREATION_FAILED" << endl;
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        throw runtime_error("Shader program error");
    }
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    check_error(ID, GL_LINK_STATUS, "PROGRAM");

    // Cleanup
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const {
    glUseProgram(ID);
}

void Shader::set_bool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(Shader::ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(Shader::ID, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(Shader::ID, name.c_str()), value);
}

void Shader::check_error(unsigned int object, GLenum status_to_check, const char* type) {
    int success;
    char infoLog[512];  // Increased buffer size

    if (status_to_check == GL_COMPILE_STATUS) {
        glGetShaderiv(object, status_to_check, &success);
        if (!success) {
            glGetShaderInfoLog(object, sizeof(infoLog), nullptr, infoLog);
            cerr << "ERROR::SHADER::" << type << "_COMPILATION_FAILED\n" << infoLog << endl;
        }
    }
    else if (status_to_check == GL_LINK_STATUS) {
        glGetProgramiv(object, status_to_check, &success);
        if (!success) {
            glGetProgramInfoLog(object, sizeof(infoLog), nullptr, infoLog);
            cerr << "ERROR::SHADER::PROGRAM_LINKING_FAILED\n" << infoLog << endl;
        }
    }
}