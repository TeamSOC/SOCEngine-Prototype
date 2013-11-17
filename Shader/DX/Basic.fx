#define MAX_LIGHTS 8

struct Light
{
	float3 ambient;
	float3 diffuse;
	float3 specular;

	float4 pos;
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
float4x4 worldViewInvTns;

float4 cameraPos;
int lightCount;

Material material;
Light lights[MAX_LIGHTS];

struct VS_INPUT 
{
	float4 position		: POSITION;
	float3 normal		: NORMAL;
	float3 tangent		: TANGENT;
	float3 binormal		: BINORMAL;
	float3 uv			: TEXCOORD0;
};

struct VS_OUTPUT 
{
	float4 position   : POSITION;
	float3 normal     : TEXCOORD0;

	float4 worldPos   : TEXCOORD1;
	float3 viewDir    : TEXCOORD2;
};

VS_OUTPUT vs_main( VS_INPUT i )
{
	VS_OUTPUT o;

	o.position = mul(i.position, worldViewProjMat);
	o.worldPos = mul(i.position, worldMat);
	o.viewDir  = normalize(cameraPos.xyz - o.worldPos.xyz);  

	o.normal = mul(i.normal, worldMat);

	//float3 worldNormal = normalize( mul( i.normal, (float3x3)worldMat));
	//float3 worldTangent = normalize( mul( i.tangent, (float3x3)worldMat));
	//float3 worldBinormal = normalize( mul( i.binormal, (float3x3)worldMat));

	//float3x3 TBN = float3x3( worldNormal, worldBinormal, worldTangent );
	return o;
}

struct PS_INPUT 
{
	float3 normal     : TEXCOORD0;
	float4 worldPos   : TEXCOORD1;
	float3 viewDir    : TEXCOORD2;
};

float4 ps_main(PS_INPUT i) : COLOR
{  
	float3 normal = normalize(i.normal);
	float3 worldPos = i.worldPos.xyz;
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
		vtx2LightDir	= normalize(lights[idx].pos.xyz - worldPos);
		lightDir		= normalize(vtx2LightDir - lights[idx].dir);  
		halfVector		= normalize(viewDir + lightDir);

		dotLight = saturate( dot(normal, lightDir) );
		dotHV = saturate( dot(normal, halfVector) );
		specPower = (dotLight == 0.0f) ? 0.0f : pow(dotHV, material.shininess * 10);

		color += (material.diffuse * lights[idx].diffuse * dotLight) +
			(material.specular * lights[idx].specular * specPower) * 0 +
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

