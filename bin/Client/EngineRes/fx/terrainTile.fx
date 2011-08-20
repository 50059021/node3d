#include "shared.fx"
#include "terrainShared.fx"

VS_TERRAIN_OUTPUT VS(VS_TERRAIN_INPUT i)
{
	VS_TERRAIN_OUTPUT o;
	o.UV0 = i.UV0;
	o.UV1 = i.UV1;
	o.Pos = mul(i.Pos,g_mViewProj);
	o.Pos.z+=0.001f;
	o.Color = i.Color;
	return o;
}

sampler s0: register(s0);
float4 PS(VS_TERRAIN_OUTPUT i) : COLOR0
{
	float4 cDiffuse	= tex2D(s0, i.UV0);
	float4 color;
	color = i.Color;
	color *= cDiffuse;
	return color;
}

technique Render
{
    pass P0
    {
		Lighting			= False;
		CullMode			= None;
		
		AlphaTestEnable		= False;
		AlphaBlendEnable	= False;

		ZEnable				= True;
		ZFunc				= LessEqual;
		ZWriteEnable		= True;

		ColorOp[0]			= Modulate;
		ColorArg1[0]		= Texture;
		ColorArg2[0]		= Diffuse;

		AlphaOp[0]			= Disable;

		ColorOp[1]			= Disable;
		AlphaOP[1]			= Disable;
		
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS();
    }
}