#include "multpoinlLightshader.h"

MultPointLightsShader::MultPointLightsShader()
{
	m_matrixBuffer = 0;
	m_layout = 0;
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_sampleState = 0;
	m_lightColorBuffer = 0;
	m_lightPositionBuffer = 0;
}

MultPointLightsShader::MultPointLightsShader(const MultPointLightsShader &other)
{
}


MultPointLightsShader::~MultPointLightsShader()
{
}

bool MultPointLightsShader::Initialize(ID3D11Device *device, HWND hwnd)
{
	bool result;
	result = InitializeShader(device, hwnd, L"../Engine/mullight.vs", L"../Engine/mullight.ps");
	if (!result)
	{
		return false;
	}
	return true;
}

void MultPointLightsShader::Shutdown()
{
	ShutdownShader();
	return;
}

bool MultPointLightsShader::Render(ID3D11DeviceContext *deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 diffuseColor[], D3DXVECTOR4 lightPostions[])
{
	bool result;
	result = SetShaderParamters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, texture, diffuseColor, lightPostions);
	if (!result)
	{
		return false;
	}
	RenderShader(deviceContext, indexCount);
	return true;
}

bool MultPointLightsShader::InitializeShader(ID3D11Device *device, HWND hwnd, WCHAR *vsFilename, WCHAR *psFilename)
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	ID3D10Blob *vertexShaderBuffer;
	ID3D10Blob *pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_BUFFER_DESC lightColorDesc;
	D3D11_BUFFER_DESC lightPositionDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;
	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "LightVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing shader file!", MB_OK);
		}
		return false;
	}
	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "LigthPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}
		return false;
	}
	//Create the vertex shader from the buffer
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}
	//Create the pixel shader from the buffer
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}
	//Create the vertex input description.
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

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	//Get a count of the elements in the layout;
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
	//Create the vertex input layout
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}
	//Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;
	//Create a texture sampler state description
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create the texture sampler state
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}
	//Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;
	//Create the constants buffer pointer so we can access the vertex shader constant buffer from within this class
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}
	//Setup the description of the camera dynamic constant buffer that is in the vertex shader.
	lightPositionDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightPositionDesc.ByteWidth = sizeof(LightPositionBufferType);
	lightPositionDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightPositionDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightPositionDesc.MiscFlags = 0;
	lightPositionDesc.StructureByteStride = 0;
	//Create the camera constant buffer pointer so we can access the vertex shader constant buffer from withiin this class
	result = device->CreateBuffer(&lightPositionDesc, NULL, &m_lightPositionBuffer);
	if (FAILED(result))
	{
		return false;
	}
	//Setup the desciption of the dynamic matrix constant buffer that is in the pixel shader.
	lightColorDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightColorDesc.ByteWidth = sizeof(LightColorBufferType);
	lightColorDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightColorDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightColorDesc.MiscFlags = 0;
	lightColorDesc.StructureByteStride = 0;
	//Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class
	result = device->CreateBuffer(&lightColorDesc, NULL, &m_lightColorBuffer);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void MultPointLightsShader::ShutdownShader()
{
	//Release the light constant buffer
	if (m_lightColorBuffer)
	{
		m_lightColorBuffer->Release();
		m_lightColorBuffer = 0;
	}
	//Release the camera constant buffer
	if (m_lightPositionBuffer)
	{
		m_lightPositionBuffer->Release();
		m_lightPositionBuffer = 0;
	}
	//Release the matrix constant buffer
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}
	//Release the sampler state
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}
	//Release the layout
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}
	//Release the pixel shader
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
	//Release the vertex shader.
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
	return;
}

void MultPointLightsShader::OutputShaderErrorMessage(ID3D10Blob *errorMesage, HWND hwnd, WCHAR *shaderFileName)
{
	char* compileError;
	unsigned long bufferSize;
	unsigned long i;
	ofstream fout;
	//Get a pointer to the error message text buffer;
	compileError = (char*)(errorMesage->GetBufferPointer());
	bufferSize = errorMesage->GetBufferSize();
	//Open a file to write the error message to.
	fout.open("shader-error.txt");
	//Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileError[i];
	}
	//Close the file
	fout.close();
	//Release the error message.
	errorMesage->Release();
	errorMesage = 0;
	//Pop a message up on the screen to notify the user to check the text file for compile error.
	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFileName, MB_OK);
}

bool MultPointLightsShader::SetShaderParamters(ID3D11DeviceContext *deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, ID3D11ShaderResourceView *texture, D3DXVECTOR4 diffuseColor[], D3DXVECTOR4 lightPostions[])
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType *dataPtr;
	LightColorBufferType *dataPtr2;
	LightPositionBufferType *dataPtr3;
	//Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);
	//Lock the constant buffer so it can be writen to;
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	//Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType *)mappedResource.pData;
	//Copy the matrices into the constant buffer
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;
	//Unlock the constant buffer
	deviceContext->Unmap(m_matrixBuffer, 0);
	//Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;
	//Now set the constant buffer in the vertex shader with the updated values;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	//Set shader texture resource in the pixel shader.

	result = deviceContext->Map(m_lightPositionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	dataPtr3 = (LightPositionBufferType*)mappedResource.pData;
	//Copy the camera position into ht constant buffer.
	dataPtr3->lightPosition[0] = lightPostions[0];
	dataPtr3->lightPosition[1] = lightPostions[1];
	dataPtr3->lightPosition[2] = lightPostions[2];
	dataPtr3->lightPosition[3] = lightPostions[3];

	//Unlock the camera constant buffer.
	deviceContext->Unmap(m_lightPositionBuffer, 0);
	//Note that we set the bufferNumber to 1 instead of 0 before setting the constant buffer. This is because it is the second buffer in the vertex shader (the first being the matrix buffer).
	//Set the position of the camera constant buffer int the vertex shader.
	bufferNumber = 1;
	//Now set the camera constant buffer in the vertex shade with the update values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_lightPositionBuffer);
	deviceContext->PSSetShaderResources(0, 1, &texture);
	result = deviceContext->Map(m_lightColorBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	//Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightColorBufferType*)mappedResource.pData;
	//Copy the lighting variables into the constant buffer.
	dataPtr2->diffuseColor[0] = diffuseColor[0];
	dataPtr2->diffuseColor[1] = diffuseColor[1];
	dataPtr2->diffuseColor[2] = diffuseColor[2];
	dataPtr2->diffuseColor[3] = diffuseColor[3];
	deviceContext->Unmap(m_lightColorBuffer, 0);
	//Unlock the constant buffer.
	//Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;
	//Finally set the light constant buffer in the pixel shader with the updated values.
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_lightColorBuffer);
	return true;
}

void MultPointLightsShader::RenderShader(ID3D11DeviceContext *deviceContext, int indexCount)
{
	//Set the vertex input layout
	deviceContext->IASetInputLayout(m_layout);
	//Set the vertex and pixel shaders that will be used to render this triangle
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	//Set the sample state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	//Render the triangle
	deviceContext->DrawIndexed(indexCount, 0, 0);
	return;
}
