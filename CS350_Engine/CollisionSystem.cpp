#include "CollisionSystem.h"
#include <iostream>




void CollisionSystem::DoCollision(Object& firstObj, Object& secondObj)
{
	switch (hash(firstObj.m_Name)) {
	case "Sphere"_sh: {
		Sphere a(firstObj.Centroid(), firstObj.ScaleVector().x / 2.f);
		if (secondObj.m_Name == "Sphere")
		{
			Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x / 2.f);
			if (Collision::SphereSphere(a, b))
			{
				std::cout << "Sphere Sphere COLLIDE" << std::endl;
			}
		}
		else if (secondObj.m_Name == "AABB")
		{
			AABB b(secondObj.m_AABB.m_Min, secondObj.m_AABB.m_Max);
			if (Collision::SphereAABB(a, b))
			{
				std::cout << "Sphere AABB COLLIDE" << std::endl;
			}
		}
		break;
	}
	case "AABB"_sh: {
		AABB a(firstObj.m_AABB.m_Min, firstObj.m_AABB.m_Max);
		if (secondObj.m_Name == "Sphere")
		{
			Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x / 2.f);
			if (Collision::AABBSphere(a, b))
			{
				std::cout << "Sphere AABB COLLIDE" << std::endl;
			}
		}

		else if (secondObj.m_Name == "AABB")
		{
			AABB b(secondObj.m_AABB.m_Min, secondObj.m_AABB.m_Max);
			if (Collision::AABBAABB(a, b))
			{
				std::cout << "AABB AABB COLLIDE" << std::endl;
			}

		}
		break;
	}
	case "Point"_sh: {
		if (secondObj.m_Name == "Sphere")
		{

		}

		else if (secondObj.m_Name == "AABB")
		{

		}

		else if (secondObj.m_Name == "Triangle")
		{

		}

		else if (secondObj.m_Name == "Plane")
		{

		}
		break;
	}
	case "Ray"_sh: {
		if (secondObj.m_Name == "Plane")
		{

		}

		else if (secondObj.m_Name == "AABB")
		{

		}

		else if (secondObj.m_Name == "Sphere")
		{

		}

		else if (secondObj.m_Name == "Triangle")
		{

		}
		break;
	}
	case "Plane"_sh: {
		if (secondObj.m_Name == "AABB")
		{

		}

		else if (secondObj.m_Name == "Sphere")
		{

		}
		break;
	}
	default:
		break;
	}


	//if (firstObj.m_Name == "Sphere")
	//{
	//	Sphere a(firstObj.Centroid(), firstObj.ScaleVector().x/2.f);
	//	if (secondObj.m_Name == "Sphere")
	//	{
	//		Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x/2.f);
	//		if (Collision::SphereSphere(a, b))
	//		{
	//			std::cout << "Sphere Sphere COLLIDE" << std::endl;
	//		}
	//	}

	//	if (secondObj.m_Name == "AABB")
	//	{
	//		AABB b(secondObj.m_AABB.m_Min, secondObj.m_AABB.m_Max);
	//		if (Collision::SphereAABB(a, b))
	//		{
	//			std::cout << "Sphere AABB COLLIDE" << std::endl;
	//		}
	//	}
	//}

	//else if (firstObj.m_Name == "AABB")
	//{
	//	AABB a(firstObj.m_AABB.m_Min, firstObj.m_AABB.m_Max);
	//	if (secondObj.m_Name == "Sphere")
	//	{
	//		Sphere b(secondObj.Centroid(), secondObj.ScaleVector().x / 2.f);
	//		if (Collision::AABBSphere(a, b))
	//		{
	//			std::cout << "Sphere AABB COLLIDE" << std::endl;
	//		}
	//	}

	//	if (secondObj.m_Name == "AABB")
	//	{
	//		AABB b(secondObj.m_AABB.m_Min, secondObj.m_AABB.m_Max);

	//	}
	//}


	//else if (firstObj.m_Name == "Point")
	//{
	//	if (secondObj.m_Name == "Sphere")
	//	{

	//	}

	//	if (secondObj.m_Name == "AABB")
	//	{

	//	}

	//	if (secondObj.m_Name == "Triangle")
	//	{

	//	}

	//	if (secondObj.m_Name == "Plane")
	//	{

	//	}

	//}
}
