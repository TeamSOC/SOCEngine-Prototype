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

		Shader::Shader *shader = new Shader::Shader("TestDiffuse");

		if(shader->Compile(shaderCode) == false)
			return;

		testShader = shader;
		mat->AddShader(shader);

		mesh->GetRenderer()->AddMaterial(mat, false);
		CreateBox(mesh->GetFilter());
		shader->SetTechnique("TestDiffuse");

		SetPosition(SOC_Vector3(0, 0.0f, -5.0f));
	}

	void CreateBox(Mesh::MeshFilter *filter)
	{ 
		SOC_Vector3 v[8];

		v[0] = SOC_Vector3( -1,  1,   1);
		v[1] = SOC_Vector3(  1,  1,   1);
		v[2] = SOC_Vector3(  1,  1,  -1);
		v[3] = SOC_Vector3( -1,  1,  -1);

		v[4] = SOC_Vector3( -1,  -1,  1);
		v[5] = SOC_Vector3(  1,  -1,  1);
		v[6] = SOC_Vector3(  1,  -1, -1);
		v[7] = SOC_Vector3( -1,  -1, -1);

		//v[3] = SOC_Vector3(1, 1, 0);
		//v[4] = SOC_Vector3(1, 0, 0);
		//v[5] = SOC_Vector3(1, 0, 0);

		std::pair<Mesh::MeshFilter::count, SOC_dword*> indices;
		indices.first = 36;
		indices.second = new SOC_dword[36];

		indices.second[0] = 0; 		indices.second[1]  = 1;		indices.second[2]  = 2;
		indices.second[3] = 0; 		indices.second[4]  = 2;		indices.second[5]  = 3;

		indices.second[6] = 4; 		indices.second[7]  = 6;		indices.second[8]  = 5;
		indices.second[9] = 4; 		indices.second[10] = 7;		indices.second[11] = 6;

		indices.second[12] = 0; 	indices.second[13] = 3;		indices.second[14] = 7;
		indices.second[15] = 0; 	indices.second[16] = 7;		indices.second[17] = 4;

		indices.second[18] = 1; 	indices.second[19] = 5;		indices.second[20] = 6;
		indices.second[21] = 1; 	indices.second[22] = 6;		indices.second[23] = 2;

		indices.second[24] = 3; 	indices.second[25] = 2;		indices.second[26] = 6;
		indices.second[27] = 3; 	indices.second[28] = 6;		indices.second[29] = 7;

		indices.second[30] = 0; 	indices.second[31] = 4;		indices.second[32] = 5;
		indices.second[33] = 0; 	indices.second[34] = 5;		indices.second[35] = 1;

		filter->Create(v, NULL, NULL, NULL, NULL, NULL, NULL, 8, indices, SOC_TRIANGLE_LIST, false);
	}

public:
	void SetMat(SOC_Matrix *viewMat, SOC_Matrix *projectionMat)
	{
		SOC_Matrix worldMat;
		GetWorldMatrix(&worldMat);

		SOC_Matrix viewProjection;
		SOCMatrixMultiply(&viewProjection, viewMat, projectionMat);

		bool b;

		b = testShader->SetVariable("worldMatrix", &worldMat);
		b = testShader->SetVariable("viewProjection", &viewProjection);
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

