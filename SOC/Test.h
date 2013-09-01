#pragma once

#include "Object.h"
#include "Mesh.h"
#include "DeviceDirector.h"
#include "ShaderManager.h"

using namespace Rendering;

class Test : public Rendering::Object
{
private:
	Rendering::Mesh::Mesh *mesh;

public:
	Test(void)
	{

	}

	~Test(void)
	{

	}

private:
	Shader::Shader *testShader;

public: 
	void Init(Shader::ShaderManager *shaderMgr)
	{		
		mesh = new Rendering::Mesh::Mesh(Device::DeviceDirector::GetInstance()->GetGraphics());

		Material *mat = new Material("TestDiffuse");

		std::string shaderCode;
		shaderMgr->LoadShaderFromFile("TestDiffuse", &shaderCode, true);

		Shader::Shader *shader = new Shader::Shader("TestDiffuse");

		if(shader->Compile(shaderCode) == false)
			return;

		testShader = shader;
		mat->AddShader(shader);

		mesh->GetRenderer()->AddMaterial(mat, false);
		CreateBox(mesh->GetFilter());

		SetPosition(SOC_Vector3(0, 0, 0));
	}

	void CreateBox(Mesh::MeshFilter *filter)
	{ 
		SOC_Vector3 v[6];

		v[0] = SOC_Vector3(0, 0, 0);
		v[1] = SOC_Vector3(1, 1, 0);
		v[2] = SOC_Vector3(0, 1, 0);

		v[3] = SOC_Vector3(1, 1, 0);
		v[4] = SOC_Vector3(1, 0, 0);
		v[5] = SOC_Vector3(1, 0, 0);

		std::pair<Mesh::MeshFilter::count, WORD*> indices;
		indices.first = 6;
		indices.second = new WORD[6];

		for(int i=0; i<6; ++i)
			indices.second[i] = i;

		filter->Create(v, NULL, NULL, NULL, NULL, NULL, NULL, 6, indices, SOC_TRIANGLE_LIST, false);
	}

public:
	bool Update()
	{
		UpdateChild();

		return true;
	}

	bool Render(std::vector<Rendering::Object*> *lights)
	{
		mesh->Render();

		return true;
	}
};

