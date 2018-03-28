cbuffer PerFrameBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	float4 fogColor;
};

cbuffer FogBuffer
{
	float fogStart;
	float fogEnd;
};

struct VertexInputType
{
	float4 position:POSITION;
	float2 tex:TEXCOORD0;
};

struct PixelInputType
{
	float4 position:SV_POSITION;
	float4 fogColor:COLOR;
	float2 tex:TEXCOORD0;
	float fogFactor:FOG;
};

PixelInputType FogVertexShader(VertexInputType input)
{
	PixelInputType output;
	float4 cameraPosition;
	input.position.w = 1.0f;
	output.position = mul(input.position,worldMatrix);
	output.position = mul(output.position,viewMatrix);
	cameraPosition = output.position;
	output.position = mul(output.position,projectionMatrix);
	output.tex = input.tex;
	output.fogColor = fogColor;
	//Linear fog
	output.fogFactor = saturate((fogEnd - cameraPosition.z)/(fogEnd - fogStart));
	return output;
}