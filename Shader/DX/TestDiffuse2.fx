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

VS_OUTPUT TestDiffuse_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position, worldViewProjMat );
   
   return( Output );
   
}

float4 TestDiffuse_Pass_0_Pixel_Shader_ps_main() : COLOR0
{   
   return( float4( 1.0f, 0.0f, 0.0f, 1.0f ) );
   
}

technique SOC
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 TestDiffuse_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 TestDiffuse_Pass_0_Pixel_Shader_ps_main();
   }

}

