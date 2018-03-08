cbuffer MatrixBuffr
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

PixelInputType TextureVertexShader(VertexInputType input)
{
	PixelInputType output;

	//Change the postion vector to be 4 units for proper matrix calculations.
	output.position = mul(input.position,worldMatrix);
	output.position = mul(output.position,viewMatrix);
	output.position = mul(output.position,projectionMatrix);
	//Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
	return output;
}