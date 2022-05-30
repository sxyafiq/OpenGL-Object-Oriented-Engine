#include <iostream>
#include "CollisionSystem.h"


void CollisionSystem::DoCollision(Object& firstObj, Object& secondObj)
{
	switch (hash(firstObj.m_Name)) {
	case "Sphere"_sh: {
		Sphere a(firstObj.m_BoundingSphere.m_Center, firstObj.m_BoundingSphere.m_Radius / 2.f);
		if (secondObj.m_Name == "Sphere")
		{
			Sphere b(secondObj.m_BoundingSphere.m_Center, secondObj.m_BoundingSphere.m_Radius / 2.f);
			if (Collision::SphereSphere(a, b))
			{
				std::cout << "Sphere Sphere COLLIDE" << std::endl;
				m_IsIntersecting = true;
			}
			else m_IsIntersecting = false;

		}
		else if (secondObj.m_Name == "AABB")
		{
			AABB b;
			b.m_Center = secondObj.Centroid();
			b.m_HalfExtents = secondObj.ScaleVector() / 2.f;
			b.m_Max = b.m_Center + b.m_HalfExtents;
			b.m_Min = b.m_Center - b.m_HalfExtents;
			if (Collision::SphereAABB(a, b))
			{
				m_IsIntersecting = true;
				std::cout << "Sphere AABB COLLIDE" << std::endl;
			}
			else m_IsIntersecting = false;
		}
		break;
	}
	case "AABB"_sh: {
		AABB a;
		a.m_Center = firstObj.Centroid();
		a.m_HalfExtents = firstObj.ScaleVector() / 2.f;
		a.m_Max = a.m_Center + a.m_HalfExtents;
		a.m_Min = a.m_Center - a.m_HalfExtents;
		if (secondObj.m_Name == "Sphere")
		{
			Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x / 2.f);
			if (Collision::AABBSphere(a, b))
			{
				m_IsIntersecting = true;
				std::cout << "Sphere AABB COLLIDE" << std::endl;
			}
			else m_IsIntersecting = false;
		}

		else if (secondObj.m_Name == "AABB")
		{
			AABB b;
			b.m_Center = secondObj.Centroid();
			b.m_HalfExtents = secondObj.ScaleVector() / 2.f;
			b.m_Max = b.m_Center + b.m_HalfExtents;
			b.m_Min = b.m_Center - b.m_HalfExtents;
			if (Collision::AABBAABB(a, b))
			{
				m_IsIntersecting = true;
				std::cout << "AABB AABB COLLIDE" << std::endl;
			}
			else m_IsIntersecting = false;
		}
		break;
	}
	case "Point"_sh: {
		Point3D a(firstObj.Centroid());
		if (secondObj.m_Name == "Sphere")
		{
			Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x / 2.f);
			if (Collision::PointSphere(a, b))
			{
				m_IsIntersecting = true;
				std::cout << "Point Sphere COLLIDE" << std::endl;
			}
			else m_IsIntersecting = false;
		}

		else if (secondObj.m_Name == "AABB")
		{
			AABB b;
			b.m_Center = secondObj.Centroid();
			b.m_HalfExtents = secondObj.ScaleVector() / 2.f;
			b.m_Min = b.m_Center - b.m_HalfExtents;
			b.m_Max = b.m_Center + b.m_HalfExtents;
			if (Collision::PointAABB(a, b)) {
				std::cout << "COLLIDING" << std::endl;
				this->m_IsIntersecting = true;
			}
			else {
				this->m_IsIntersecting = false;
			}
		}

		else if (secondObj.m_Name == "Triangle")
		{
			Triangle b(secondObj.matrix4() * glm::vec4(secondObj.m_Model->m_Vertices[0], 1.f),
				secondObj.matrix4() * glm::vec4(secondObj.m_Model->m_Vertices[1], 1.f),
				secondObj.matrix4() * glm::vec4(secondObj.m_Model->m_Vertices[2], 1.f));
			if (Collision::PointTriangle(a, b))
			{
				this->m_IsIntersecting = true;
				std::cout << "Point Triangle COLLIDE" << std::endl;
			}
			else m_IsIntersecting = false;
		}

		else if (secondObj.m_Name == "Plane")
		{
			Triangle tri(secondObj.matrix4() * glm::vec4(secondObj.m_Model->m_Vertices[0], 1.f),
				secondObj.matrix4() * glm::vec4(secondObj.m_Model->m_Vertices[1], 1.f),
				secondObj.matrix4() * glm::vec4(secondObj.m_Model->m_Vertices[2], 1.f));

			Plane b(tri);

			if (Collision::PointPlane(a, b))
			{
				m_IsIntersecting = true;
			}
			else m_IsIntersecting = false;

			//b.m_RandomPointOnPlane = secondObj.Centroid();
			//{
			//	m_IsIntersecting = true;
			//}
			//else m_IsIntersecting = false;
		}
		break;
	}
	case "Ray"_sh: {
		glm::vec3 vertexPos1 = firstObj.matrix4() * glm::vec4(firstObj.m_Model->m_Vertices[0], 1.f);
		glm::vec3 vertexPos2 = firstObj.matrix4() * glm::vec4(firstObj.m_Model->m_Vertices[1], 1.f);
		Ray a;
		a.m_Position = firstObj.Centroid();
		a.m_Direction = vertexPos2 - vertexPos1;


		if (secondObj.m_Name == "Plane")
		{
			Plane b;
			if (Collision::RayPlane(a, b))
			{
				std::cout << "Ray Plane COLLIDE" << std::endl;
			}
			else m_IsIntersecting = false;
		}

		else if (secondObj.m_Name == "AABB")
		{
			AABB b;
			b.m_Center = secondObj.Centroid();
			b.m_HalfExtents = secondObj.ScaleVector() / 2.f;
			b.m_Max = b.m_Center + b.m_HalfExtents;
			b.m_Min = b.m_Center - b.m_HalfExtents;
			if (Collision::RayAAABB(a, b))
			{
				m_IsIntersecting = true;
			}
			else m_IsIntersecting = false;
		}

		else if (secondObj.m_Name == "Sphere")
		{
			Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x / 2.f);
			//float t;
			//Point3D c;
			//if (Collision::RaySphere(a, b))
			//{
			//	m_IsIntersecting = true;
			//}
			//else m_IsIntersecting = false;
		}

		else if (secondObj.m_Name == "Triangle")
		{
			Triangle b;
			//if (Collision::RayTriangle(a, b))
			//{
			//	std::cout << "Point Triangle COLLIDE" << std::endl;
			//}
		}
		break;
	}
	case "Plane"_sh: {
		Plane a;

		if (secondObj.m_Name == "AABB")
		{
			AABB b;
			b.m_Center = secondObj.Centroid();
			b.m_HalfExtents = secondObj.ScaleVector() / 2.f;
			b.m_Max = b.m_Center + b.m_HalfExtents;
			b.m_Min = b.m_Center - b.m_HalfExtents;
			//if (Collision::PlaneAABB(a, b))
			//{
			//	std::cout << "Plane AABB COLLIDE" << std::endl;
			//}
		}

		else if (secondObj.m_Name == "Triangle")
		{
			Triangle b;
		}
		break;
	}
	default:
		break;
	}
}
