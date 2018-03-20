cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position:POSITION;
	float2 tex:TEXCOORD0;
};

struct PixelInputType
{
	float4 position:SV_POSITION;
	float2 tex:TEXCOORD0;
};

PixelInputType MultiTextureVertexShader(VertexInputType input)
{
	PixelInputType output;
	output.position = mul(worldMatrix,input.position);
	output.position = mul(viewMatrix,output.position);
	output.position = mul(projectionMatrix,output.position);
	output.tex = input.tex;
	return output;
}