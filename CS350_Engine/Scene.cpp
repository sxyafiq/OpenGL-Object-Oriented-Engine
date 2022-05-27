/* Start Header -------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
File Name: Scene.cpp
Purpose: holds scene data
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
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/color_space.hpp>

#include "Scene.h"
#include "Engine.h"
#include <iostream>


static bool once = true;

#define OCTHALFWIDTH 15

Scene::Scene(SceneIndex number)
{
  m_Camera.m_Position = glm::vec3(0.0f,0.0f,1.0f);
  m_BoundingHierarchy.m_Construction = BoundingHierarchy::Construction::BottomUp;
  m_BoundingHierarchy.m_Method = BoundingHierarchy::Method::AABB;
  m_IsDrawingBoundingHierarchy = false;

	switch (number)
	{
  case ZERO:
    break;
  case ONE:
  {
    Object& object1 = AddObject();
    object1.m_Name = "Sphere";
    object1.m_Model = Engine::get().m_AssetManager.GetModel(Model::Sphere);
    object1.SetShader(Engine::get().m_AssetManager.GetShader(ShaderIndex::DeferredFirstPassShader));
    object1.SetCentroid(glm::vec3(0.0f, 0.0f, 0.0f));
    object1.m_Material.ambiant_color = glm::vec3(0.0f, 0.0f, 0.0f);


    Object& object2 = AddObject();
    object2.m_Name = "Sphere";
    //object2.SetScaleVector({ 0,0,0 });
    object2.m_Model = Engine::get().m_AssetManager.GetModel(Model::Sphere);
    object2.SetShader(Engine::get().m_AssetManager.GetShader(ShaderIndex::DeferredFirstPassShader));
    object2.SetCentroid(glm::vec3(2.0f, 0.0f, 0.0f));
    object2.m_Material.ambiant_color = glm::vec3(0.0f, 0.0f, 0.0f);

    
    break;
  }
  default:
    break;
	}

}

Scene::~Scene()
{
  m_Lights.clear();
  m_Objects.clear();
}

void Scene::Update(float deltaTime)
{
  for(Object& object : m_Objects)
  {
    object.Update(deltaTime);
  }
}

Object& Scene::AddObject()
{
  m_Objects.emplace_back("Object");

  return m_Objects.back();
}

