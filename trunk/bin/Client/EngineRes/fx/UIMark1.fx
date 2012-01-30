#include "shared.fx"

technique Render
{
    pass P0
    {
		Lighting			= False;
		CullMode			= None;
		
		AlphaTestEnable		= True;
		AlphaFunc			= GreaterEqual;
		AlphaRef			= 64;
		
		AlphaBlendEnable	= TRUE;
		BlendOp				= Add;
		SrcBlend			= ZERO;
		DestBlend			= ONE;

		ZEnable				= True;
		ZFunc				= LessEqual;
		ZWriteEnable		= True;

		ColorOp[0]			= Modulate;
		ColorArg1[0]		= Texture;
		ColorArg2[0]		= Diffuse;

		AlphaOp[0]			= Modulate;
		AlphaArg1[0]		= Texture;
		AlphaArg2[0]		= Diffuse;

		ColorOp[1]			= Disable;
		AlphaOP[1]			= Disable;
		
		VertexShader		= NULL;
        PixelShader			= NULL;
    }
}