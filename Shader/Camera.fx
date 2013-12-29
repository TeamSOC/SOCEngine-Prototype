struct VS_INPUT 
{
   float4 position	: POSITION;
   float2 uv 		: TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 position	: POSITION;
   float2 uv 		: TEXCOORD0;
};


VS_OUTPUT vs_main( VS_INPUT i )
{
   VS_OUTPUT o;
   
   o.position = i.position;
   o.uv = i.uv;
   
   return o;
}

struct PS_INPUT
{
   float2 uv : TEXCOORD0;
};

texture sceneTexture;
sampler2D SceneSampler = sampler_state
{
   Texture = <sceneTexture>;
};

float4 ps_main( PS_INPUT i ) : COLOR
{
   float4 tex = tex2D(SceneSampler, i.uv);   
   if(i.uv.x > 0.5f)
     tex.rgb = dot(tex.rgb, float3(0.3, 0.59, 0.11));
   return tex;
}

technique SOC
{
   pass
   {
      CULLMODE = NONE;

      VertexShader = compile vs_3_0 vs_main();
      PixelShader = compile ps_3_0 ps_main();
   }

}

