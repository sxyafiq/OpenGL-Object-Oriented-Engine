/* Start Header -------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
File Name: DebugNormal.vert
Purpose: 
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
Creation date: 1/30/2021
End Header --------------------------------------------------------*/

#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

out Vertex
{
  vec4 normal;
} vertex;

void main()
{
  gl_Position = vec4( vPosition, 1.0f );
  vertex.normal = vec4(vNormal.xyz, 1.0);
}