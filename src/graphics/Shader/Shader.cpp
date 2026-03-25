#include "Shader.h"

Shader::Shader(const std::string& vertexPath,
               const std::string& fragmentPath)
{
    std::string vsrc = loadFile(vertexPath);
    std::string fsrc = loadFile(fragmentPath);

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vsrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fsrc);

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vs);
    glAttachShader(m_ID, fs);
    glLinkProgram(m_ID);

    int success;
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(m_ID, 512, nullptr, info);
        std::cout << "Shader link error:\n" << info << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::bind() const
{
    glUseProgram(m_ID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

std::string Shader::loadFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type,
                                   const std::string& src)
{
    unsigned int id = glCreateShader(type);
    const char* cstr = src.c_str();
    glShaderSource(id, 1, &cstr, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(id, 512, nullptr, info);
        std::cout << "Shader compile error:\n" << info << std::endl;
    }

    return id;
}

// ---------------- uniforms ----------------

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

// void Shader::setVec3(const std::string& name,
//                      const glm::vec3& v) const
// {
//     glUniform3f(
//         glGetUniformLocation(m_ID, name.c_str()),
//         v.x, v.y, v.z
//     );
// }

// void Shader::setMat4(const std::string& name,
//                      const glm::mat4& m) const
// {
//     glUniformMatrix4fv(
//         glGetUniformLocation(m_ID, name.c_str()),
//         1,
//         GL_FALSE,
//         &m[0][0]
//     );
// }
