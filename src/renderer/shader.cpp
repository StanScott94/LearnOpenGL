#include "shader.h"

#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

#include "engine.h"
#include "gl_utils.h"

Shader::Shader(const char *name, const char *vertexPath, const char *fragmentPath)
    : m_Name(name), m_VertexPath(vertexPath), m_FragmentPath(fragmentPath) {
}

Shader::~Shader() {
    if (m_ProgramId != -1) {
        Destroy();
    }
}

bool Shader::Create() {
    std::string vertexSource;
    std::string fragmentSource;
    std::ifstream vertexStream;
    std::ifstream fragmentStream;

    vertexStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexStream.open(m_VertexPath);
        fragmentStream.open(m_FragmentPath);
        std::stringstream vertexStringStream, fragmentStringStream;

        vertexStringStream << vertexStream.rdbuf();
        fragmentStringStream << fragmentStream.rdbuf();
 
        vertexStream.close();
        fragmentStream.close();

        vertexSource = vertexStringStream.str();
        fragmentSource = fragmentStringStream.str();
    }
    catch (std::ifstream::failure e) {
        fprintf(stderr, "Shader Error: Failed to load shader '%s'\n", m_Name.c_str());
        return false;
    }

    GL(m_ProgramId = glCreateProgram());

    unsigned int vertexId = CreateShader(m_Name.c_str(), vertexSource.c_str(), GL_VERTEX_SHADER);
    if (vertexId == -1) {
        return false;
    }

    unsigned int fragmentId = CreateShader(m_Name.c_str(), fragmentSource.c_str(), GL_FRAGMENT_SHADER);
    if (fragmentId == -1) {
        return false;
    }

    GL(glAttachShader(m_ProgramId, vertexId));
    GL(glAttachShader(m_ProgramId, fragmentId));
    GL(glLinkProgram(m_ProgramId));

    m_ProgramId = checkCompileErrors(m_ProgramId, m_Name.c_str(), GL_PROGRAM);
    if (m_ProgramId == -1) {
        return false;
    }

    GL(glDeleteShader(vertexId));
    GL(glDeleteShader(fragmentId));

    int uniformCount;
    GL(glGetProgramiv(m_ProgramId, GL_ACTIVE_UNIFORMS, &uniformCount));

    int length, size;
    GLenum type;
    for (int i = 0; i < uniformCount; i++) {
        char name[64];
        GL(glGetActiveUniform(m_ProgramId, (GLuint)i, 64, &length, &size, &type, name));

        GL(unsigned int uniformLocation = glGetUniformLocation(m_ProgramId, name));

        m_Uniforms.insert(std::pair<const char *, unsigned int>(name, uniformLocation));
    }

    printf("Loaded shader program '%s', uniforms: %d\n", m_Name.c_str(), uniformCount);
    return true;
}

void Shader::Destroy() {
    Unbind();
    GL(glDeleteProgram(m_ProgramId));
    m_ProgramId = -1;
}

void Shader::Bind() {
    GL(glUseProgram(m_ProgramId));
}

void Shader::Unbind() {
    GL(glUseProgram(0));
}

void Shader::Uniform1f(std::string name, float value) {
    GL(glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), value));
    //unsigned int location = m_Uniforms[name];
    //GL(glUniform1f(location, value));
}

void Shader::Uniform2f(std::string name, glm::vec2 &value) {
    unsigned int location = m_Uniforms[name];
    GL(glUniform2f(location, value.x, value.y));
}

void Shader::Uniform3f(std::string name, glm::vec3 &value) {
    GL(glUniform3fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, &value[0]));
    //unsigned int location = m_Uniforms[name];
    //GL(glUniform3f(location, value.x, value.y, value.z));
}

void Shader::Uniform4f(std::string name, glm::vec4 &value) {
    unsigned int location = m_Uniforms[name];
    GL(glUniform4f(location, value.x, value.y, value.z, value.w));
}

void Shader::Uniform1i(std::string name, int value) {
    unsigned int location = m_Uniforms[name];
    GL(glUniform1i(location, value));
}

void Shader::Uniform2i(std::string name, glm::ivec2 &value) {
    unsigned int location = m_Uniforms[name];
    GL(glUniform2i(location, value.x, value.y));
}

void Shader::Uniform3i(std::string name, glm::ivec3 &value) {
    unsigned int location = m_Uniforms[name];
    GL(glUniform3i(location, value.x, value.y, value.z));
}

void Shader::Uniform4i(std::string name, glm::ivec4 &value) {
    unsigned int location = m_Uniforms[name];
    GL(glUniform4i(location, value.x, value.y, value.z, value.w));
}

void Shader::UniformMat4(std::string name, glm::mat4 &value) {
    GL(glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, &value[0][0]));
    //unsigned int location = m_Uniforms[name];
    //GL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}

unsigned int Shader::CreateShader(const char *name, const char *source, unsigned int type) {
    unsigned int id;
    GL(id = glCreateShader(type));
    GL(glShaderSource(id, 1, &source, NULL));
    GL(glCompileShader(id));
    return checkCompileErrors(id, name, type);
}

unsigned int Shader::checkCompileErrors(const unsigned int id, const char *name, unsigned int type) {
    int success;
    char infoLog[1024];
    if (type != GL_PROGRAM) {
        GL(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
        if (!success) {
            GL(glGetShaderInfoLog(id, 1024, NULL, infoLog));
            fprintf(stderr, "Shader Error: Failed to compile shader '%s': \n%s\n", name, infoLog);
            return -1;
        }
    } else {
        GL(glGetProgramiv(id, GL_LINK_STATUS, &success));
        if (!success) {
            GL(glGetProgramInfoLog(id, 1024, NULL, infoLog));
            fprintf(stderr, "Shader Error: Failed to link shader program '%s': \n%s\n", name, infoLog);
            return -1;
        }
    }

    printf("Loaded %s shader '%s'\n", type == 35633 ? "vertex" : "fragment", name);
    return id;
}

