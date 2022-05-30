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

static bool once = true;

#define OCTHALFWIDTH 15

Scene::Scene(SceneIndex number)
{
  m_Camera.m_Position = glm::vec3(0.0f,0.0f,1.0f);
  m_BoundingHierarchy.m_Construction = BoundingHierarchy::Construction::BottomUp;
  m_BoundingHierarchy.m_Method = BoundingHierarchy::Method::AABB;
  m_IsDrawingBoundingHierarchy = false;
  m_OctTreeHead = BuildOctree({ 0,0,0 }, OCTHALFWIDTH, OctTreeNode::maxDepth);

	switch (number)
	{
  case ZERO:
    break;
  case ONE:
  {
    Object& object1 = AddObject();
    object1.m_Name = "Sphere";
    object1.m_Model = Engine::get().m_AssetManager.GetModel(Model::Cube);
    object1.SetShader(Engine::get().m_AssetManager.GetShader(ShaderIndex::DeferredFirstPassShader));
    object1.SetCentroid(glm::vec3(-1.0f, 0.0f, -1.0f));
    object1.m_Material.ambiant_color = glm::vec3(1.0f, 0.3f, 1.0f);

    Object& object2 = AddObject();
    //object2.SetScaleVector({ 0,0,0 });
    object2.m_Name = "Sphere";
    object2.m_Model = Engine::get().m_AssetManager.GetModel(Model::Cube);
    object2.SetShader(Engine::get().m_AssetManager.GetShader(ShaderIndex::DeferredFirstPassShader));
    object2.SetCentroid(glm::vec3(1.0f, 0.0f, -1.0f));
    object2.m_Material.ambiant_color = glm::vec3(0.4f, 1.0f, 1.0f);

    
    break;
  }
  default:
    break;
	}
  UpdateBSP();

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

  for (int i = 0; i < m_Lights.size(); ++i)
  {
    m_Lights[i].Update(deltaTime);
    float x = 2 * cos((i * 360.0f / m_Lights.size() * 3.1415f / 180.0f) + m_Lights[i].RotationAngle());
    float y = 2 * sin((i * 360.0f / m_Lights.size() * 3.1415f / 180.0f) + m_Lights[i].RotationAngle());

    m_Lights[i].SetCentroid(glm::vec3(x, 0.0f, y));
    m_Lights[i].m_Light->position = m_Lights[i].Centroid();
    m_Lights[i].m_Light->direction = glm::rotate(m_Lights[i].RotationAngle(), m_Lights[i].RotationVector()) * glm::vec4(1.0f);
    m_Lights[i].m_Light->ambiant = m_Lights[i].m_Material.ambiant_color;
  }

  if(m_IsDrawingBoundingHierarchy)
  {
    m_BoundingHierarchy.Draw(m_Objects);
  }

  if (m_OctTreeHead && m_OctTreeHead->showBoxes)
  {
    m_OctTreeHead->Draw();
  }

  if (m_BSPHead && m_BSPHead->showLines)
  {
    m_BSPHead->Draw();
  }
}

Object& Scene::AddObject()
{
  m_Objects.emplace_back("Object");

  return m_Objects.back();
}

Object& Scene::AddLight()
{
  m_Lights.emplace_back("Light");

  return m_Lights.back();
}

void Scene::UpdateOctTree()
{
  m_OctTreeHead = BuildOctree({ 0,0,0 }, OCTHALFWIDTH, OctTreeNode::maxDepth);

  for (int i = 0; i < m_Objects.size(); ++i)
  {
    if (!m_Objects[i].m_Light)
    {
      OctTreeInsertObject(m_OctTreeHead, &m_Objects[i]);
    }
  }
}

void Scene::UpdateBSP()
{
  wholeMeshVert.clear();
  wholeMeshIndex.clear();

  for (Object& object : m_Objects)
  {
    if (!object.m_Light)
    {
      glm::mat4 modelToWorldMatrix = object.matrix4();
      std::vector<glm::vec3> verts = object.m_Model->m_Vertices;
      for (glm::vec3& vert : verts)
      {
        vert = glm::vec3(modelToWorldMatrix * glm::vec4(vert, 1.0f));
      }

      UniqueAddVerties(verts, object.m_Model->m_Indices, wholeMeshVert, wholeMeshIndex);
    }
  }

  m_BSPHead = BuildBSPTree(wholeMeshVert, wholeMeshIndex, 0);
}
