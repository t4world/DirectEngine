#include "watershaderclass.h"


Watershaderclass::Watershaderclass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
	m_reflectionBuffer = 0;
	m_waterBuffer = 0;
}

Watershaderclass::Watershaderclass(const Watershaderclass &other)
{

}


Watershaderclass::~Watershaderclass()
{
}

bool Watershaderclass::Initialize(ID3D11Device *device, HWND hWnd)
{
	bool result;
	//Initialize the vertex and pixel shader
	result = InitializeShader(device, hWnd, L"../Engine/texture.vs", L"../Engine/texture.ps");
	if (!result)
	{
		return false;
	}
	return true;
}

void Watershaderclass::Shutdown()
{
	ShutdownShader();
	return;
}

bool Watershaderclass::Render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, D3DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* refractionTexture, ID3D11ShaderResourceView* normalTexture, float waterTranslation, float reflectRefractScale)
{
	bool result;
	result = SetShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix, texture, refractionTexture, normalTexture, waterTranslation, reflectRefractScale);
	if (!result)
	{
		return false;
	}
	//Now Render the prepared buffers with the shader
	RenderShader(deviceContext, indexCount);
	return true;
}

bool Watershaderclass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	ID3D10Blob *vertexShaderBuffer;
	ID3D10Blob *pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC reflectinBufferDesc;
	D3D11_BUFFER_DESC refractionBufferDesc;


	//Initialize the pointers this function will use to null;
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DX11CompileFromFile(vsFilename, NULL, NULL, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}
		return false;
	}
	result = D3DX11CompileFromFile(psFilename, NULL, NULL, "TexturePixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File.", MB_OK);
		}
		return false;
	}
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}
	//Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	//Create the vertex input layout description.
	//This setup needs to match the VertexType structure in the ModelClass and in  the shader.
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

	//Get a count of the elements in the layout.
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//Create the vertex input layout.
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

	//Setup the description of the dynamic matrix buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	//Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Create a texture sampler state description.
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
	//Create the texture sampler state.
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	reflectinBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	reflectinBufferDesc.ByteWidth = sizeof(ReflectionBufferType);
	reflectinBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	reflectinBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	reflectinBufferDesc.MiscFlags = 0;
	reflectinBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&reflectinBufferDesc, NULL, &m_reflectionBuffer);
	if (FAILED(result))
	{
		return false;
	}

	refractionBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	refractionBufferDesc.ByteWidth = sizeof(WaterBufferType);
	refractionBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	refractionBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	refractionBufferDesc.MiscFlags = 0;
	refractionBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&refractionBufferDesc, NULL, &m_waterBuffer);
	if (FAILED(result))
	{
		return false;
	}
	
	return true;
}

void Watershaderclass::ShutdownShader()
{
	if (m_waterBuffer)
	{
		m_waterBuffer->Release();
		m_waterBuffer = 0;
	}

	if (m_reflectionBuffer)
	{
		m_reflectionBuffer->Release();
		m_reflectionBuffer = 0;
	}
	//Release the sampler state.
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}
	//Release the matrix constant buffer
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	//Release the layout
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}
	//Release the pixel shader.
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
	//Release the vertex shader
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
	return;
}

void Watershaderclass::OutputShaderErrorMessage(ID3D10Blob *errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char *compileError;
	unsigned long bufferSize;
	unsigned long i;
	ofstream fout;
	//Get the pointer to the error message text buffer.
	compileError = (char *)(errorMessage->GetBufferPointer());
	//Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();
	//Open a file to write the error message to
	fout.open("shader-error.txt");
	//Write out the error message.
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileError[i];
	}
	//Close the file
	fout.close();
	//Release the error message.
	errorMessage->Release();
	errorMessage = 0;
	//Pop a message up on the screen ot notify the user to check the text file for compile errors;
	MessageBox(hwnd, L"Error compiling shader. Check Shader-error.txt for message.", shaderFilename, MB_OK);
}

bool Watershaderclass::SetShaderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, D3DXMATRIX reflectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* refractionTexture, ID3D11ShaderResourceView* normalTexture, float waterTranslation, float reflectRefractScale)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType *dataPtr;
	ReflectionBufferType *dataPtr2;
	WaterBufferType *dataPtr3;
	unsigned int bufferNumber;
	//Transpose the matrics to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	//Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	//Get a pointer to the data in the constant buffer
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	//Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);
	//Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;
	//Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	deviceContext->PSSetShaderResources(0, 1, &texture);

	result = deviceContext->Map(m_reflectionBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	dataPtr2 = (ReflectionBufferType *)mappedResource.pData;
	dataPtr2->reflectMatrix = reflectionMatrix;
	deviceContext->Unmap(m_reflectionBuffer, 0);
	bufferNumber = 1;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_reflectionBuffer);

	result = deviceContext->Map(m_waterBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}
	dataPtr3 = (WaterBufferType *)mappedResource.pData;
	dataPtr3->reflectRefractScale = reflectRefractScale;
	dataPtr3->waterTranslation = waterTranslation;
	dataPtr3->padding = D3DXVECTOR2(0.0f, 0.0f);
	bufferNumber = 0;
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &m_waterBuffer);
	deviceContext->PSSetShaderResources(1, 1, &refractionTexture);
	deviceContext->PSSetShaderResources(2, 1, &refractionTexture);
	return true;
}

void Watershaderclass::RenderShader(ID3D11DeviceContext* deviceContext, int indexCount)
{
	//Set the vertex input layout.
	deviceContext->IASetInputLayout(m_layout);
	//Set the vertex and pixel shaders that will be used to render this triangle.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	//Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	//Render the triangle
	deviceContext->DrawIndexed(indexCount, 0, 0);
	return;
}
