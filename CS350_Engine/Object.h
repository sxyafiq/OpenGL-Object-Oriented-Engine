/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
File Name: Object.h
Purpose: holds object data
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
#ifndef OBJECT_H
#define OBJECT_H

#include <glew-2.1.0/GL/glew.h>
#include <glm/glm.hpp>

#include <string>

#include "Model.h"
#include "Shader.h"

//! string version of the light types
static const char* const LightTypeNames[] =
{
  "Point",
  "Directional",
  "Spotlight",
};

/**
 * @brief 
 *   Light struct
 */
struct Light
{
  glm::vec3 position; //!< position
  float InnerAngle;   //!< inner angle for spotlights

  glm::vec3 direction; //!< direction
  float OuterAngle;    //!< outer angle for spotlights

  glm::vec3 diffuse; //!< diffuse color
  float falloff;     //!< distance falloff

  glm::vec3 specular; //!< specular color
  int type;           //!< 0 point, 1 directional, 2 spot

  glm::vec3 ambiant; //!< ambiant color
  int pad;           //!< extra padding
};

/**
 * @brief 
 *   Material struct
 */
struct Material
{
public:
  GLfloat   specular_exponent; //!< specular exponent 
  glm::vec3 ambiant_color;     //!< ambiant color
};

/**
 * @brief 
 *   Object class
 */
class Object
{
public:
  /**
   * @brief 
   *   Constructor of a new Object 
   * 
   * @param name 
   *   Name of the Object
   */
  Object(const char* name = "");

  /**
   * @brief 
   *   Destructure of the Object 
   */
  ~Object();

  /**
   * @brief 
   *   
   * 
   * @param deltaTime 
   *   delta time of the engine
   */
  void Update(float deltaTime);
  void SetShader(const ShaderPtr& shader);
  glm::mat4 matrix4() const;
  glm::mat4 normalMatrix() const;

  std::string m_Name;
  ModelPtr m_Model;
  ShaderPtr m_Shader;

  glm::vec3 m_ScaleVector;
  glm::vec3 m_Centroid;
  glm::vec3 m_RotationVector;

  GLfloat m_RotationAngle;
  GLfloat m_RotationAmount;

  Material m_Material;
  Light* m_Light;

  GLint m_PerspectiveMatrixUniform;
  GLint m_ViewMatrixUniform;
  GLint m_ModelMatrixUniform;
  GLint m_NormalMatrixUniform;
  GLint m_EyePositionUniform;
  GLint m_AmbiantColorUniform;

  bool m_DrawAABB;
  bool m_DrawBoundingSphere;
private:
};

#endif
