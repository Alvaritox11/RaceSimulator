#pragma once

//STD Libs
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

//GLEW
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

//OpenGL Math libs
#include<glm/glm.hpp>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//Own libs
#include"Vertex.h"

#include "Vertex.h" // Asegúrate de que esta inclusión apunta a tu definición de Vertex

static std::vector<Vertex> loadOBJ(const char* file_name) {
    // Listas para almacenar las posiciones, texcoords y normales de los vértices
    std::vector<glm::fvec3> vertex_positions;
    std::vector<glm::fvec2> vertex_texcoords;
    std::vector<glm::fvec3> vertex_normals;

    // Listas para almacenar los índices de las caras
    std::vector<GLint> vertex_position_indicies;
    std::vector<GLint> vertex_texcoord_indicies;
    std::vector<GLint> vertex_normal_indicies;

    std::vector<Vertex> vertices; // Lista final de vértices
    std::stringstream ss;
    std::ifstream in_file(file_name);
    std::string line;
    glm::vec3 temp_vec3;
    glm::vec2 temp_vec2;

    // Verificación de la apertura del archivo
    if (!in_file.is_open()) {
        throw "ERROR::OBJLOADER::Could not open file.";
    }

    // Lectura de líneas
    while (std::getline(in_file, line)) {
        ss.clear();
        ss.str(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_positions.push_back(temp_vec3);
        }
        else if (prefix == "vt") {
            ss >> temp_vec2.x >> temp_vec2.y;
            vertex_texcoords.push_back(temp_vec2);
        }
        else if (prefix == "vn") {
            ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
            vertex_normals.push_back(temp_vec3);
        }
        else if (prefix == "f") {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            char slash;

            ss >> vertexIndex[0] >> slash >> uvIndex[0] >> slash >> normalIndex[0]
                >> vertexIndex[1] >> slash >> uvIndex[1] >> slash >> normalIndex[1]
                >> vertexIndex[2] >> slash >> uvIndex[2] >> slash >> normalIndex[2];

            vertex_position_indicies.push_back(vertexIndex[0]);
            vertex_position_indicies.push_back(vertexIndex[1]);
            vertex_position_indicies.push_back(vertexIndex[2]);
            vertex_texcoord_indicies.push_back(uvIndex[0]);
            vertex_texcoord_indicies.push_back(uvIndex[1]);
            vertex_texcoord_indicies.push_back(uvIndex[2]);
            vertex_normal_indicies.push_back(normalIndex[0]);
            vertex_normal_indicies.push_back(normalIndex[1]);
            vertex_normal_indicies.push_back(normalIndex[2]);
        }
        // Ignorar otras líneas
    }

    // Construir el arreglo final de vértices
    for (size_t i = 0; i < vertex_position_indicies.size(); i++) {
        glm::vec3 position = vertex_positions[vertex_position_indicies[i] - 1];
        glm::vec2 texcoord;
        glm::vec3 normal;

        if (i < vertex_texcoord_indicies.size())
            texcoord = vertex_texcoords[vertex_texcoord_indicies[i] - 1];
        if (i < vertex_normal_indicies.size())
            normal = vertex_normals[vertex_normal_indicies[i] - 1];

        Vertex v;
        v.position = position;
        v.texcoord = texcoord;
        v.normal = normal;
        vertices.push_back(v);
    }

    in_file.close();
    return vertices;
}