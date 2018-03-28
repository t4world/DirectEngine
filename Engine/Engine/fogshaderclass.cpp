#include "fogshaderclass.h"


FogShaderClass::FogShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_SamplerState = 0;
	m_ConstantBuffer = 0;
	m_FogBuffer = 0;
}

FogShaderClass::FogShaderClass(const FogShaderClass &other)
{

}


FogShaderClass::~FogShaderClass()
{
}

bool FogShaderClass::Initialize(ID3D11Device *device, HWND hwnd)
{
	bool result;
	result = InitializeShader(device, hwnd, L"../Engine/fog.vs", L"../Engine/fog.ps");
	if (!result)
	{
		return false;
	}
	return true;
}

void FogShaderClass::Shutdown()
{
	ShutdownShader();
}

bool FogShaderClass::Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 fogColor, float fogStart, float fogEnd)
{
	bool result;
	result = SetShaderParameter(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, fogColor, fogStart, fogEnd);
	if (!result)
	{
		return false;
	}
	result = RenderShader(deviceContext, indexCount);
	if (!result)
	{
		return false;
	}
	return true;
}

bool FogShaderClass::InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsShaderFile, WCHAR *psShaderFile)
{
	HRESULT result;
	ID3D10Blob *vertexDataBuffer;
	ID3D10Blob *pixelDataBuffer;
	ID3D10Blob *errorMessage;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC constantBufferDesc;
	D3D11_BUFFER_DESC fogBufferDesc;
	D3D11_SAMPLER_DESC samplerStateDesc;

	errorMessage = 0;
	pixelDataBuffer = 0;
	vertexDataBuffer = 0;

	result = D3DX11CompileFromFile(vsShaderFile, NULL, NULL, "FogVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexDataBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsShaderFile);
		}
		else
		{
			MessageBox(hwnd, vsShaderFile, L"Missing Shader File", MB_OK);
		}
		return false;
	}
	result = D3DX11CompileFromFile(psShaderFile, NULL, NULL, "FogPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelDataBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psShaderFile);
		}
		else
		{
			MessageBox(hwnd, vsShaderFile, L"Missing Shader File", MB_OK);
		}
		return false;
	}
	result = device->CreateVertexShader(vertexDataBuffer->GetBufferPointer(), vertexDataBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}
	result = device->CreatePixelShader(pixelDataBuffer->GetBufferPointer(), pixelDataBuffer->GetBufferSize(), NULL,&m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
	result = device->CreateInputLayout(polygonLayout, numElements, vertexDataBuffer->GetBufferPointer(), vertexDataBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	vertexDataBuffer->Release();
	vertexDataBuffer = 0;
	pixelDataBuffer->Release();
	pixelDataBuffer = 0;

	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.ByteWidth = sizeof(ConstantBufferType);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&constantBufferDesc, NULL, &m_ConstantBuffer);
	if (FAILED(result))
	{
		return false;
	}

	fogBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	fogBufferDesc.ByteWidth = sizeof(FogBufferType);
	fogBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	fogBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	fogBufferDesc.MiscFlags = 0;
	fogBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&fogBufferDesc, NULL, &m_FogBuffer);
	if (FAILED(result))
	{
		return false;
	}
	samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerStateDesc.MipLODBias = 1;
	samplerStateDesc.MaxAnisotropy = 1;
	samplerStateDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerStateDesc.BorderColor[0] = 0;
	samplerStateDesc.BorderColor[1] = 0;
	samplerStateDesc.BorderColor[2] = 0;
	samplerStateDesc.BorderColor[3] = 0;
	samplerStateDesc.MinLOD = 0;
	samplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerStateDesc, &m_SamplerState);
	if (FAILED(result))
	{
		return false;
	}

	fogBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	fogBufferDesc.ByteWidth = sizeof(FogBufferType);
	fogBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	fogBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	fogBufferDesc.MiscFlags = 0;
	fogBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&fogBufferDesc, NULL, &m_FogBuffer);

	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void FogShaderClass::ShutdownShader()
{
	if (m_FogBuffer)
	{
		m_FogBuffer->Release();
		m_FogBuffer = 0;
	}
	if (m_SamplerState)
	{
		m_SamplerState->Release();
		m_SamplerState = 0;
	}
	if (m_ConstantBuffer)
	{
		m_ConstantBuffer->Release();
		m_ConstantBuffer = 0;
	}
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}

bool FogShaderClass::RenderShader(ID3D11DeviceContext *deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	deviceContext->PSSetSamplers(0, 1, &m_SamplerState);
	deviceContext->DrawIndexed(indexCount, 0, 0);
	return true;
}

bool FogShaderClass::SetShaderParameter(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 fogColor, float fogStart, float fogEnd)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mapResource;
	ConstantBufferType *dataPtr;
	FogBufferType *dataPtr2;
	unsigned int bufferNum;

	result = deviceContext->Map(m_ConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (FAILED(result))
	{
		return false;
	}
	dataPtr = (ConstantBufferType *)mapResource.pData;
	//Transpose the matrices to prepare them for the shader
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;
	dataPtr->fogColor = fogColor;
	deviceContext->Unmap(m_ConstantBuffer, 0);
	bufferNum = 0;
	deviceContext->VSSetConstantBuffers(bufferNum, 1, &m_ConstantBuffer);
	deviceContext->PSSetShaderResources(0, 1,&texture);
	result = deviceContext->Map(m_FogBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (FAILED(result))
	{
		return false;
	}
	dataPtr2 = (FogBufferType *)mapResource.pData;
	dataPtr2->fogStart = fogStart;
	dataPtr2->fogEnd = fogEnd;

	deviceContext->Unmap(m_FogBuffer, 0);
	bufferNum = 1;
	deviceContext->VSSetConstantBuffers(bufferNum, 1, &m_FogBuffer);
	return true;
}

void FogShaderClass::OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR *shaderFileName)
{
	char *compileError;
	unsigned long bufferSize;
	unsigned long i;
	ofstream fout;
	compileError = (char *)(errorMessage->GetBufferPointer());
	bufferSize = errorMessage->GetBufferSize();
	fout.open("shader-error.txt");
	for (i = 0; i < bufferSize;i++)
	{
		fout << compileError[i];
	}
	fout.close();
	errorMessage->Release();
	errorMessage = 0;
	MessageBox(hwnd, L"Error Compiling shader. Check shader-error.txt for message.", shaderFileName, MB_OK);
}
