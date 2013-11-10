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

   float3 lightDir   : TEXCOORD2;
   float3 viewDir    : TEXCOORD3;
};

VS_OUTPUT vs_main( VS_INPUT i )
{
   VS_OUTPUT o;

   o.position = mul(i.position, worldViewProjMat);
   o.normal   = mul(i.normal, (float3x3)worldMat);

   o.worldPos = mul(i.position, worldMat);
   o.lightDir = normalize(lights[0].pos.xyz - o.worldPos.xyz);
   o.viewDir  = normalize(cameraPos.xyz - o.worldPos.xyz);  
      
   return o;
}

texture diffuseTex;
sampler2D diffuseMap = sampler_state
{
    Texture = <diffuseTex>;
};

struct PS_INPUT 
{
   float3 normal     : TEXCOORD0;

   float4 worldPos   : TEXCOORD1;

   float3 lightDir   : TEXCOORD2;
   float3 viewDir    : TEXCOORD3;
};


float4 ps_main(PS_INPUT i) : COLOR
{  
   float3 normal = normalize(i.normal);
   float3 lightDir = normalize(i.lightDir);
 
//   float3 albedo = tex2D(diffuseMap, i.uv);
   float3 halfVector = normalize(i.viewDir) + normalize(i.lightDir);
   float dotLight = saturate( dot(normal, lightDir) );

   float3 ambient = lights[0].ambient * material.ambient;
   
   float3 diffuse = float3(0, 0, 0);
   float3 specular = float3(0, 0, 0);

   if(dotLight > 0.0f)
   {
      diffuse = lights[0].diffuse * material.diffuse;
      specular = lights[0].specular * material.specular * pow( saturate( dot(normal, halfVector) ), material.shininess);
   }

   return float4(diffuse + ambient, 1.0f);
}

technique SOC
{
   pass
   {
      CULLMODE = CW;

      VertexShader = compile vs_3_0 vs_main();
      PixelShader = compile ps_3_0 ps_main();
   }

}

