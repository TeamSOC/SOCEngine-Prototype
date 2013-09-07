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
	Test(void) : Object()
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

		Device::Graphics::GraphicsForm *graphics = Device::DeviceDirector::GetInstance()->GetGraphics();
		Shader::Shader *shader = new Shader::Shader(graphics, "TestDiffuse");

		if(shader->Compile(shaderCode) == false)
			return;

		testShader = shader;
		mat->AddShader(shader);

		mesh->GetRenderer()->AddMaterial(mat, false);
		CreateBox(mesh->GetFilter());
		shader->SetTechnique("TestDiffuse");

		SetPosition(SOC_Vector3(0, 0.0f, 0.0f));
	}

	void CreateBox(Mesh::MeshFilter *filter)
	{ 
		SOC_Vector3 v[3];

		v[0] = SOC_Vector3(   0.0f, 0,   0.5f);
		v[1] = SOC_Vector3(   0.5f,   0.5,   0.5f);
		v[2] = SOC_Vector3(  -0.5f,   0.5,  0.5f);

		std::pair<Mesh::MeshFilter::count, SOC_word*> indices;
		indices.first = 3;
		indices.second = new SOC_word[3];

		indices.second[0]  = 0;
		indices.second[1]  = 1;
		indices.second[2]  = 2;

//		filter->Create(v, NULL, NULL, NULL, NULL, NULL, NULL, 8, indices, SOC_TRIANGLE_LIST, false);
		filter->Create(v, nullptr ,nullptr, nullptr, nullptr, nullptr,
			3, indices, SOC_TRIANGLE_LIST, false);
	}

public:
	void SetMat(SOC_Matrix *viewMat, SOC_Matrix *projectionMat)
	{
		SOC_Matrix worldMat;
		GetWorldMatrix(&worldMat);

		static float angle = 0.0f;

		angle += 0.2f * SOCM_PI / 180.0f;
		if( angle > 2 * SOCM_PI )
			angle -= 2 * SOCM_PI;

		D3DXMatrixRotationY(&worldMat, angle);

		SOC_Matrix wvp;
		SOCMatrixMultiply(&wvp, &worldMat, viewMat);
		SOCMatrixMultiply(&wvp, &wvp, projectionMat);

		bool b;

		b = testShader->SetVariable("worldViewProjection", &wvp);
	}

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

