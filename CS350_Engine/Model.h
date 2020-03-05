/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
File Name: Model.h
Purpose: constructs models
Language: C++ and Visual Studio 2017
Platform:
compiler version:
  14.1 - 14.16
hardware requirements:
  1.8 GHz or faster processor. Dual-core or better recommended
  2 GB of RAM; 4 GB of RAM recommended (2.5 GB minimum if running on a virtual machine)
  Hard disk space: up to 130 GB of available space, depending on features installed; typical installations require 20-50 GB of free space.
  Hard disk speed: to improve performance, install Windows and Visual Studio on a solid state drive (SSD).
  Video card that supports a minimum display resolution of 720p (1280 by 720); Visual Studio will work best at a resolution of WXGA (1366 by 768) or higher.
operating systems:
  Windows 10 64bit
Project: michael.ngo_CS350_1
Author: Michael Ngo, michael.ngo, 90003217
Creation date: 2/2/2020
End Header --------------------------------------------------------*/
#ifndef MODEL_H
#define MODEL_H

#include <glew-2.1.0/GL/glew.h>
#include <glm/glm.hpp>

#include <memory>
#include <vector>

#include "AABB.h"
#include "BoundingSphere.h"

//! Model indices 
enum ModelIndex
{
  FourSphere,
  Bunny,
  BunnyHighPoly,
  Cube,
  CubeTwo,
  Cup,
  LucyPrinceton,
  Quad,
  Rhino,
  Sphere,
  SphereModified,
  StarWarsOne,
  Triangle,
};

//! Model string name
static const char* const ModelNames[] =
{
  "4Sphere",
  "bunny",
  "bunny_high_poly",
  "cube",
  "cube2",
  "cup",
  "lucy_princeton",
  "quad",
  "rhino",
  "sphere",
  "sphere_modified",
  "starwars1",
  "triangle",
};

/**
 * @brief 
 *  Model class
 */
class Model
{
public:
  // Default constructor for a new Model object
  Model(ModelIndex index = ModelIndex::Bunny);

  Model(const Model& rhs) = delete;
  Model(Model&& rhs) = delete;

  // Destructure for the Model object
  ~Model();

  // Move constructor for a Model object
  Model& operator=(Model&& rhs) noexcept;

  // Debug Draw AABB 
  void DrawAABBBounds(const glm::mat4& modelToWorld);

  // Debug Draw Bounding Sphere
  void DrawBoundingSphere(const glm::mat4 & modelToWorld);
  
  ModelIndex m_ModelIndex;                //!< index of the current model
  std::vector<glm::vec3> m_Vertices;      //!< vector of vertices
  std::vector<glm::vec3> m_VertexNormals; //!< vector of vertex normals
  std::vector<glm::uint> m_Indices;       //!< vector of indices
  std::vector<glm::vec3> m_FaceNormals;   //!< vector of face normals
  std::vector<glm::vec3> m_FacesPosition; //!< vector of face positions
  GLuint m_VAO;                           //!< vertex buffer object number
  GLuint m_VBO;                           //!< (vertex) buffer number
  GLuint m_VNBO;                          //!< (vertex normal) buffer number
  GLuint m_EBO;                           //!< (indices) buffer number
  GLuint m_DrawMode;                      //!< draw mode

private:
  AABB m_AABBBounds;               //!< axis aligned bounding box for the model
  BoundingSphere m_BoundingSphere; //!< bounding sphere for the model

  // Model Parsing for ".obj"
  void ParseModel(const char * filename);

  // Generate Buffers for the models for shader to use 
  void GenerateBuffers();

  // Cleanup the model, destructing
  void CleanUp();

  // Set member variables to zero
  void SetZero();

};

using ModelPtr = std::shared_ptr<Model>;

#endif
