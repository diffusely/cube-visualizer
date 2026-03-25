#pragma once
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath,
           const std::string& fragmentPath);
    ~Shader();

    void use(); 
    void bind() const;
    void unbind() const;

    // uniforms
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    // void setVec3(const std::string& name, const glm::vec3& v) const;
    // void setMat4(const std::string& name, const glm::mat4& m) const;

private:
    unsigned int m_ID;

    std::string loadFile(const std::string& path);
    unsigned int compileShader(unsigned int type, const std::string& src);
};
