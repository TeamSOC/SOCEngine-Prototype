float4x4 worldViewProjMat : WorldViewProjection;
float4x4 worldMat : World;

struct VS_INPUT 
{
   float4 position : POSITION0;
   float3 normal : NORMAL;
   float2 uv : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 position : POSITION0;
   float4 normal : TEXCOORD0;
   float2 uv : TEXCOORD1; 
};

VS_OUTPUT vs( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.position 	= mul( Input.position, worldViewProjMat );
   Output.normal 	= mul( Input.position, worldMat );
   Output.uv 		= Input.uv;
   
   return Output;   
}

texture diffuseTex;
sampler2D diffuseMap = sampler_state
{
    Texture = (diffuseTex);
};

struct PS_INPUT 
{
   float4 normal : TEXCOORD0;
   float2 uv : TEXCOORD1; 
};


float4 ps(PS_INPUT input) : COLOR
{   
   float4 albedo = tex2D(diffuseMap, input.uv);
   return albedo;
}

technique SOC
{
   pass Pass_0
   {
      CULLMODE = CW;
      ZWRITEENABLE = TRUE;

      VertexShader = compile vs_2_0 vs();
      PixelShader = compile ps_2_0 ps();
   }

}

