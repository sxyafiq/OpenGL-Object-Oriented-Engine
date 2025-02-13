/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
File Name: Shader.cpp
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
#include <string>
#include <vector>
#include <fstream>

#include "Shader.h"

Shader::Shader(ShaderIndex index)
{
  std::string vertex(ShaderNames[index]);
  std::string fragment(vertex);
  vertex.append(".vert");
  fragment.append(".frag");
  m_Index = index;
  m_ProgramID = LoadShaders(vertex.c_str(), fragment.c_str());
}

GLuint Shader::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }

  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }
  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;
  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open()) {
    std::string Line;
    while (getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }
  else {
    printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open()) {
    std::string Line;
    while (getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }

  GLint Result = GL_FALSE;
  int InfoLogLength;

  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }
  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const* VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }

  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const* FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }

  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }
  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);
  {
    GLenum error_out;
    while ((error_out = glGetError()) != GL_NO_ERROR)
    {
      __debugbreak();
      printf("oof %i", error_out);
    }
  }
  return ProgramID;
}

GLuint Shader::LoadMultiShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geom_file_path)
{
  // Create the shaders
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  GLuint GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

  // Read the Vertex Shader code from the file
  std::string VertexShaderCode;

  std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
  if (VertexShaderStream.is_open())
  {
    std::string Line;
    while (getline(VertexShaderStream, Line))
      VertexShaderCode += "\n" + Line;
    VertexShaderStream.close();
  }
  else
  {
    printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n",
      vertex_file_path);
    getchar();
    return 0;
  }

  // Read the Fragment Shader code from the file
  std::string FragmentShaderCode;
  std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
  if (FragmentShaderStream.is_open())
  {
    std::string Line;
    while (getline(FragmentShaderStream, Line))
      FragmentShaderCode += "\n" + Line;
    FragmentShaderStream.close();
  }


  // array of char * to hold the strings
  std::vector<const char*> shaderStrings;
  shaderStrings.clear();

  // Read the Geometry Shader from the file
  std::string GeometryShaderCode;
  std::ifstream GeometryShaderStream(geom_file_path, std::ios::in);
  if (GeometryShaderStream.is_open())
  {
    std::string Line;
    while (getline(GeometryShaderStream, Line))
      GeometryShaderCode += "\n" + Line;
    GeometryShaderStream.close();
  }

  shaderStrings.push_back(GeometryShaderCode.c_str());
  //////////////////////////////////////////////////////////


  GLint Result = GL_FALSE;
  int InfoLogLength;


  // Compile Vertex Shader
  printf("Compiling shader : %s\n", vertex_file_path);
  char const* VertexSourcePointer = VertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
  glCompileShader(VertexShaderID);

  // Check Vertex Shader
  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> VertexShaderErrorMessage(static_cast<unsigned long>(InfoLogLength + 1));
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }


  // Compile Geometry Shader
  printf("Compiling shader : %s\n", geom_file_path);
  char const* GeometrySourcePointer = GeometryShaderCode.c_str();
  glShaderSource(GeometryShaderID, 1, &GeometrySourcePointer, nullptr);
  glCompileShader(GeometryShaderID);
  // Check Fragment Shader
  glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> GeometryShaderErrorMessage((unsigned long)(InfoLogLength + 1));
    glGetShaderInfoLog(GeometryShaderID, InfoLogLength, nullptr, &GeometryShaderErrorMessage[0]);
    printf("%s\n", &GeometryShaderErrorMessage[0]);
  }


  // Compile Fragment Shader
  printf("Compiling shader : %s\n", fragment_file_path);
  char const* FragmentSourcePointer = FragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> FragmentShaderErrorMessage(static_cast<unsigned long>(InfoLogLength + 1));
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }
  // Link the program
  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, GeometryShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  // Check the program
  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0)
  {
    std::vector<char> ProgramErrorMessage(static_cast<unsigned long>(InfoLogLength + 1));
    glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }


  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, GeometryShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(GeometryShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}