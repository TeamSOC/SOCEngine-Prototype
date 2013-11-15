#define MAX_LIGHTS 8

struct Light
{
	float3 ambient;
	float3 diffuse;
	float3 specular;

	float3 pos;
	float3 dir;
	int type;

	float range;
	float spotAngle;
};

struct Material
{
	float3 ambient;
	float3 diffuse;
	float3 emissive;
	float3 specular;
	float transparent;
	float shininess;
};

float4x4 worldMat;
float4x4 worldViewProjMat;

float4 cameraPos;
int lightCount;

Material material;
Light lights[MAX_LIGHTS];

struct VS_INPUT 
{
	float4 position   : POSITION;
	float3 normal     : NORMAL;
};

struct VS_OUTPUT 
{
	float4 position   : POSITION;
	float3 normal     : TEXCOORD0;

	float3 worldPos   : TEXCOORD1;
	float3 viewDir    : TEXCOORD2;
};

VS_OUTPUT vs_main( VS_INPUT i )
{
	VS_OUTPUT o;

	o.position = mul(i.position, worldViewProjMat);
	o.normal   = mul(i.normal, (float3x3)worldMat);

	o.worldPos = mul(i.position, worldMat).xyz;
	o.viewDir  = cameraPos.xyz - o.worldPos;

	return o;
}

struct PS_INPUT 
{
	float3 normal     : TEXCOORD0;
	float3 worldPos   : TEXCOORD1;
	float3 viewDir    : TEXCOORD2;
};

float4 ps_main(PS_INPUT i) : COLOR
{  
	float3 normal = normalize(i.normal);
		float3 worldPos = normalize(i.worldPos);
		float3 viewDir = normalize(i.viewDir);

		float3 vtx2LightDir;
	float3 lightDir;
	float3 halfVector;

	float dotLight;
	float dotHV;
	float specPower;

	float3 color = float3(0, 0, 0);

		for(int idx=0; idx<lightCount; ++idx)
		{
			vtx2LightDir = normalize(lights[idx].pos.xyz - worldPos.xyz);
			lightDir = normalize(vtx2LightDir - lights[idx].dir);
			halfVector = normalize(viewDir + lightDir);

			//      dotLight = saturate( dot(normal, lightDir) );
			dotLight = saturate( dot(normal, lights[idx].dir) );
			dotHV = saturate( dot(normal, halfVector) );
			specPower = (dotLight == 0.0f) ? 0.0f : pow(dotHV, material.shininess * 10);

			color += (material.diffuse * lights[idx].diffuse * dotLight) +
				(material.specular * lights[idx].specular * specPower) * 0.0 +
				(material.ambient * lights[idx].ambient);
		}

		return float4(color, 1.0f);
}

technique SOC
{
	pass
	{
		CULLMODE = CW;
		SRGBWRITEENABLE = FALSE;

		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}

}

