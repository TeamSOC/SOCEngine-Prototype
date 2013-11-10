float4x4 worldViewProjMat : WorldViewProjection;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float3 Normal : NORMAL;
   float2 UV : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   
};

VS_OUTPUT vs( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position, worldViewProjMat );
   
   return( Output );
   
}

float4 ps() : COLOR0
{   
   return( float4( 1.0f, 0.0f, 0.0f, 1.0f ) );
   
}

technique SOC
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 vs();
      PixelShader = compile ps_2_0 ps();
   }

}

