#define MAX_LIGHTS 2

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
   float4 position   : POSITION;
   float3 normal     : NORMAL;
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
   o.normal   = mul(i.normal, (float3x3)worldMat);

   o.worldPos = mul(i.position, worldMat);
   o.viewDir  = normalize(cameraPos.xyz - o.worldPos.xyz);  

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
   float3 vtx2LightDir = float3(0,0,0);
   float3 lightDir = float3(0,0,0);
   float3 halfVector = float3(0, 0, 0);

   float dotLight = 0;
   float dotHV = 0;
   float specPower = 0;

   float3 color = float3(0, 0, 0);

   for(int idx=0; idx<lightCount; ++idx)
   {
      vtx2LightDir	= normalize(lights[idx].pos.xyz - i.worldPos.xyz);
      lightDir		= normalize(vtx2LightDir - lights[idx].dir);

	  lightDir = vtx2LightDir;

      halfVector	= normalize(i.viewDir + lightDir);

      dotLight = saturate( dot(i.normal, lightDir) );
      dotHV = saturate( dot(i.normal, halfVector) );
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

      VertexShader = compile vs_2_0 vs_main();
      PixelShader = compile ps_2_0 ps_main();
   }

}

