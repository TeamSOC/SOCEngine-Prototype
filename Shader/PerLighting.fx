string Lighting_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\torus.3ds";

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjectionMatrix;

float4 gWorldLightPosition;
float4 gWorldCameraPosition;

struct VS_INPUT 
{
   float4 mPosition : POSITION;
   float3 mNormal: NORMAL;
};

struct VS_OUTPUT 
{
   float4 mPosition		: POSITION;
   float4 worldPos		: TEXCOORD0;
   float3 viewDir		: TEXCOORD1;
   float3 worldNormal	: TEXCOORD2;
   float3 lightDir		: TEXCOORD3;
};

VS_OUTPUT Lighting_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.mPosition = mul( Input.mPosition, gWorldMatrix );
   Output.worldPos = Output.mPosition;

   float3 lightDir = gWorldLightPosition.xyz - Output.mPosition.xyz;
   Output.lightDir = normalize(lightDir);
   
   float3 viewDir = normalize(gWorldCameraPosition.xyz - Output.mPosition.xyz);
   Output.viewDir = viewDir;
   
   Output.mPosition = mul( Output.mPosition, gViewMatrix );
   Output.mPosition = mul( Output.mPosition, gProjectionMatrix );
   
   float3 worldNormal = mul( Input.mNormal, (float3x3)gWorldMatrix );
   Output.worldNormal = normalize(worldNormal);
   
   return Output;
}

struct PS_INPUT
{
   float4 mPosition		: POSITION;
   float4 worldPos		: TEXCOORD0;
   float3 viewDir		: TEXCOORD1;
   float3 worldNormal	: TEXCOORD2;
   float3 lightDir		: TEXCOORD3;
};

float3 lightDiffuseColor = float3(1, 1, 1);
float3 lightSpecularColor = float3(1, 1, 1);

float3 diffuseColor = float3(1, 1, 0);
float3 ambientColor = float3(0.1, 0.1, 0.1);
float3 specularColor = float3(1, 1, 1);

float specularPower = 20.0f;

float4 Lighting_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR
{   
   float3 normal = normalize(Input.worldNormal);
   float3 worldPos = Input.worldPos;
   float3 viewDir = normalize(Input.viewDir);
   

   float3 halfVector;

   float dotLight;
   float dotHV;
   float specPower;

   float3 color = float3(0, 0, 0);


      halfVector	= normalize(viewDir + Input.lightDir);
      dotLight = saturate( dot(normal, Input.lightDir) );
      dotHV = saturate( dot(normal, halfVector) );
      specPower = (dotLight == 0.0f) ? 0.0f : pow(dotHV, specularPower);
      
      color += (diffuseColor * lightDiffuseColor * dotLight) +
	       (specularColor * lightSpecularColor * specPower) +
	       (ambientColor * lightDiffuseColor);

   return float4(color, 1.0f);
}

//--------------------------------------------------------------//
// Technique Section for Lighting
//--------------------------------------------------------------//
technique Lighting
{
   pass Pass_0
   {
//      CULLMODE = CW;
      SRGBWRITEENABLE = FALSE;

      VertexShader = compile vs_2_0 Lighting_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Lighting_Pass_0_Pixel_Shader_ps_main();
   }

}

