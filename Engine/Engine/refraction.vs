cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer ClipPanelBuffer
{
	float4 clipPlane;
};

struct VertexInputType
{
	float4 position:POSITION;
	float2 tex:TEXCOORD0;
	float3 normal:NORMAL;
};

struct PixelInputType
{
	float4 position:SV_POSITION;
	float2 tex:TEXCOORD0;
	float3 normal:NORMAL;
	float clip:SV_ClipDistance0;
};

PixelInputType RefractionVertexShader()