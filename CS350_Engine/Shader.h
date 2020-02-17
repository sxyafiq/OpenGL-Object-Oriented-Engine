/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Shader.h
Purpose: holds shader data
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
#ifndef SHADER_H
#define SHADER_H

#include <glew-2.1.0/GL/glew.h>

#include <memory>

enum ShaderIndex
{
  DefaultShader,
  LightShader,
  PhongShading,
  GeometryShader,
  LightingPass,
  TextureShader,
};

static const char* const ShaderNames[] =
{
  "DefaultShader",
  "LightShader",
  "PhongShading",
  "GeometryShader",
  "LightingPass",
  "TextureShader",
};

class Shader
{
public:
  Shader(ShaderIndex index = ShaderIndex::DefaultShader);

  ShaderIndex m_Index;
  GLuint m_ProgramID;

private:
  GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
};

using ShaderPtr = std::shared_ptr<Shader>;

#endif
