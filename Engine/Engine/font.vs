cbuffer PerFrameBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position:POSITION;
	float2 texture:TEXCOORD0;
};

struct PixelInputType
{
	float4 position:SV_POSITION;
	float2 texture:TEXCOORD0;
};

PixelInputType FontVertexShader(VertexInput input)
{
	PixelInputType output;
	output.position = mul(input.position,worldMatrix);
	output.position = mul(output.position,viewMatrix);
	output.position = mul(output.position,projectionMatrix);
	//store the texture coordinate for the pixel shader.
	output.texture = input.texture;
	return output;
}