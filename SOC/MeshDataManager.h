#pragma once

#include "Map.h"
#include "VBElements.h"
#include "MaterialElements.h"

#include "AABB.h"

namespace Rendering
{
	struct MeshDatas
	{
		Mesh::VBElements	vb;
		Material::MaterialElements	material;
		MeshTextureNames	textureNames;

		float radius;
		Intersection::AABB aabb;

		MeshDatas(){}
		~MeshDatas(){}
	};

class MeshDataManager : public Map<MeshDatas>
{
};

}