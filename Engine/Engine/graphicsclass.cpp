////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	//m_Model = 0;
	//m_ColorShader = 0;
	//m_TextureShader = 0;
	//m_LightShader = 0;
	//m_Light = 0;
	//m_Bitmap = 0;
	//m_Text = 0;
	//m_ModelList = 0;
	//m_Frustum = 0;
	//m_MultiTextureShader = 0;
	//m_BumpMapShader = 0;
	//m_SpecMapShader = 0;
	//m_RenderTexture = 0;
	//m_DebuWindow = 0;
	m_TextureShader = 0;
	m_Model1 = 0;
	m_Model2 = 0;
	//m_FogShader = 0;
	//m_clipShader = 0;
	m_transparentShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
// 	m_Camera->Render();
// 	m_Camera->GetViewMatrix(baseViewMatrix);
	
	// Create the model object.
// 	m_Model = new ModelClass;
// 	if(!m_Model)
// 	{
// 		return false;
// 	}
// 
// 	// Initialize the model object.
// 	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stone02.dds", L"../Engine/data/bump02.dds",L"../Engine/data/spec02.dds");
// 	if(!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}

	m_Model1 = new ModelClass1;
	if (!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/dirt01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Model2 = new ModelClass1;
	if (!m_Model2)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stone01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

// 	m_BumpMapShader = new BumpMapShaderClass;
// 	if (!m_BumpMapShader)
// 	{
// 		return false;
// 	}
// 	result = m_BumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the bump map shader object", L"Error", MB_OK);
// 		return false;
// 	}

	// Create the color shader object.
// 	m_ColorShader = new ColorShaderClass;
// 	if(!m_ColorShader)
// 	{
// 		return false;
// 	}

	// Initialize the color shader object.
//	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);


	//Create the light shader object;
// 	m_LightShader = new LightShaderClass;
// 	if(!m_LightShader)
// 	{
// 		return false;
// 	}
// 	//Initialize the light shader object
// 	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if(!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the light shader object", L"Error", MB_OK);
// 		return false;
// 	}

// Create the specular map shader object.
// 	m_SpecMapShader = new SpecMapShaderClass;
// 	if (!m_SpecMapShader)
// 	{
// 		return false;
// 	}
// 
// 	// Initialize the specular map shader object.
// 	result = m_SpecMapShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
// 		return false;
// 	}

// 	m_FogShader = new FogShaderClass;
// 	if (!m_FogShader)
// 	{
// 		return false;
// 	}

	// Initialize the specular map shader object.
// 	result = m_FogShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 	m_FogShader = new FogShaderClass;
// 	if (!m_FogShader)
// 	{
// 		return false;
// 	}

	// Initialize the specular map shader object.
// 	m_clipShader = new ClipPlaneShaderClass;
// 	if (!m_clipShader)
// 	{
// 		return false;
// 	}
// 	result = m_clipShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
// 		return false;
// 	}

	m_transparentShader = new TransparentShaderClass;
	if (!m_transparentShader)
	{
		return false;
	}
	result = m_transparentShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}
	//Create the light object
// 	m_Light = new LightClass;
// 	if (!m_Light)
// 	{
// 		return false;
// 	}
// 	//Initialize the light objec15
// 	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
// 	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
// 	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	m_Light->SetSpecularPower(32.0f);
	//Create the bitmap object;
// 	m_Bitmap = new BitmapClass;
// 	if (!m_Bitmap)
// 	{
// 		return false;
// 	}
// 	//Initialize the bitmap object;
// 	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Engine/data/seafloor.dds", 256, 256);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the bitmap object", L"Error", MB_OK);
// 		return false;
// 	}

// 	m_Text = new TextClass;
// 	if (!m_Text)
// 	{
// 		return false;
// 	}
// 	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 	m_ModelList = new ModelListClass;
// 	if (!m_ModelList)
// 	{
// 		return false;
// 	}
// 	result = m_ModelList->Initialize(25);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model list object", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 	m_Frustum = new FrustumClass;
// 	if (!m_Frustum)
// 	{
// 		return false;
// 	}

// 	m_MultiTextureShader = new MultiTextureShaderClass;
// 	if (!m_MultiTextureShader)
// 	{
// 		return false;
// 	}
// 	result = m_MultiTextureShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the mulittexture shader object", L"Error", MB_OK);
// 		return false;
// 	}

// 	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
// 	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	m_Light->SetSpecularPower(16.0f);
// 
// 	m_RenderTexture = new RenderTextureClass;
// 	if (!m_RenderTexture)
// 	{
// 		return false;
// 	}
// 	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
// 	if (!result)
// 	{
// 		return false;
// 	}
// 
// 	m_DebuWindow = new DebugWindowClass;
// 	if (!m_DebuWindow)
// 	{
// 		return false;
// 	}
// 	result = m_DebuWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
// 		return false;
// 	}

	//Create the texture shader object
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
	 	return false;
	}
	//Initialzie the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
	 	MessageBox(hwnd, L"Could not initialize the texture  shader object.", L"Error", MB_OK);
	 	return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
// 	if (m_FogShader)
// 	{
// 		m_FogShader->Shutdown();
// 		delete m_FogShader;
// 		m_FogShader = 0;
// 	}
	if (m_transparentShader)
	{
		m_transparentShader->Shutdown();
		delete m_transparentShader;
		m_transparentShader = 0;
	}

// 	if (m_clipShader)
// 	{
// 		m_clipShader->Shutdown();
// 		delete m_clipShader;
// 		m_clipShader = 0;
// 	}

	//Release the texture shader object
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
// 
// 	if (m_RenderTexture)
// 	{
// 		m_RenderTexture->Shutdown();
// 		delete m_RenderTexture;
// 		m_RenderTexture = 0;
// 	}
// 	if (m_Light)
// 	{
// 		delete m_Light;
// 		m_Light = 0;
// 	}

	//Release the light shader object
// 	if (m_LightShader)
// 	{
// 	 	m_LightShader->Shutdown();
// 	 	delete m_LightShader;
// 	 	m_LightShader = 0;
// 	}



// 	if (m_SpecMapShader)
// 	{
// 		m_SpecMapShader->Shutdown();
// 		delete m_SpecMapShader;
// 		m_SpecMapShader = 0;
// 	}

// 	if (m_BumpMapShader)
// 	{
// 		m_BumpMapShader->Shutdown();
// 		delete m_BumpMapShader;
// 		m_BumpMapShader = 0;
// 	}
// 	if (m_MultiTextureShader)
// 	{
// 		m_MultiTextureShader->Shutdown();
// 		delete m_MultiTextureShader;
// 		m_MultiTextureShader = 0;
// 	}
// 	if (m_Frustum)
// 	{
// 		delete m_Frustum;
// 		m_Frustum = 0;
// 	}
// 	if (m_ModelList)
// 	{
// 		m_ModelList->Shutdown();
// 		delete m_ModelList;
// 		m_ModelList = 0;
// 	}
	// Release the color shader object.
// 	if(m_ColorShader)
// 	{
// 		m_ColorShader->Shutdown();
// 		delete m_ColorShader;
// 		m_ColorShader = 0;
// 	}

	//Release the bitmap object.
// 	if (m_Bitmap)
// 	{
// 		m_Bitmap->Shutdown();
// 		delete m_Bitmap;
// 		m_Bitmap = 0;
// 	}


	//Release the light object
// 	if (m_Light)
// 	{
// 		delete m_Light;
// 		m_Light = 0;
// 	}


	// Release the model object.
// 	if(m_Model)
// 	{
// 		m_Model->Shutdown();
// 		delete m_Model;
// 		m_Model = 0;
// 	}

	if(m_Model1)
	{
	 	m_Model1->Shutdown();
	 	delete m_Model1;
	 	m_Model1 = 0;
	}

	if (m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}


	//Release the text object;
// 	if (m_Text)
// 	{
// 		m_Text->Shutdown();
// 		delete m_Text;
// 		m_Text = 0;
// 	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(float rotationY)
{
	bool result;

//	static float rotation = 0.0f;
// 	//Update the rotation variable each frame
// 	rotation += (float)D3DX_PI * 0.005f;
// 		if (rotation > 360.0f)
// 		{
// 			rotation -= 360.0f;
// 		}
// 		// Render the graphics scene.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	//m_Camera->SetRotation(0.0, rotationY, 0.0f);
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	static float rotation = 0.0f;
// 	int modelCount;
// 	int renderCount;
// 	int index;
// 	float positionX;
// 	float positionY;
// 	float positionZ;
// 	float radius;
	D3DXVECTOR4 fogColor = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	D3DXVECTOR4 clipPlane = D3DXVECTOR4(0.5f, 1.0f, 0.0f, 0.0f);
	float alpha = 0.5f;



 	bool result;
// 	bool renderModel;
	//The first pass of our render is to a texture now.
// 	result = RenderToTexture();
// 	if (!result)
// 	{
// 		return false;
// 	}

	// Clear the buffers to begin the scene.
	//The second pass of our render is to the back buffer as normal.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
// 	result = RenderScene();
// 	if (!result)
// 	{
// 		return false;
// 	}
	//Then after the rendering is complete we render the 2D debug window so we can see the render to texture as a 2D image at the 50x50 pixel location.
	//m_D3D->TurnZBufferOff();
	

//	renderCount = 0;
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
// 	result = m_DebuWindow->Render(m_D3D->GetDeviceContext(), 50, 50);
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_DebuWindow->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_RenderTexture->GetShaderResourceView());
// 	if (!result)
// 	{
// 		return false;
// 	}
	rotation += (float)D3DX_PI * 0.0025f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	D3DXMatrixRotationY(&worldMatrix, rotation);

	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model1->GetTexture());
	if (!result)
	{
		return false;
	}
	D3DXMatrixTranslation(&worldMatrix, 1.0f, 0.0f, -1.0f);
	m_D3D->TurnOnAlphaBlending();
	m_Model2->Render(m_D3D->GetDeviceContext());
// 	m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 		m_Model1->GetTexture(),fogColor,0.0f,10.0f);
// 	m_clipShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 		m_Model1->GetTexture(), clipPlane);
	result = m_transparentShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model2->GetTexture(), alpha);
	if (!result)
	{
		return false;
	}
	m_D3D->TurnOffAlphaBlending();
// 	m_Frustum->ConsturctFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);
// 	modelCount = m_ModelList->GetModelCount();
// 	for (index = 0; index< modelCount;index++)
// 	{
// 		m_ModelList->GetData(index, positionX, positionY, positionZ, color);
// 		radius = 1.0f;
// 		renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);
// 		if (renderModel)
// 		{
// 			D3DXMatrixTranslation(&worldMatrix, positionX, positionY, positionZ);
// 			m_Model->Render(m_D3D->GetDeviceContext());
// 			m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), color, m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
// 			//Reset the world matrix;
// 			m_D3D->GetWorldMatrix(worldMatrix);
// 			renderCount++;
// 		}
// 	}
// 	result = m_Text->SetText(renderCount, m_D3D->GetDeviceContext());
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	m_D3D->TurnZBufferOff();
	//Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
//	m_Model->Render(m_D3D->GetDeviceContext());
//	m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
// 		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//m_MultiTextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	// Render the model using the color shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

	//Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());

	//Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(),m_Light->GetDiffuseColor(),m_Camera->GetPosition(),m_Light->GetSpecularColor(),m_Light->GetSpecularPower());
	//Put the bitmap vertex and idex buffer on the graphic pipeline to prepare them for drawing.

// 	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
// 	if(!result)
// 	{
// 		return false;
// 	}
// 	//Render the bitmap with the texture shader.

// 	m_D3D->TurnOnAlphaBlending();
// 	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	m_D3D->TurnOffAlphaBlending();
// 	//Turn the Z buffer back on now that all 2D rendering has completed.
// 	m_D3D->TurnZBufferOn();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderToTexture()
{
	bool result;
	// Set the render target to be the render to texture.
	//m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());
	//Clear the render to texture background to blue so we can differentiate it from the rest of the normal scene.
	//m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = RenderScene();
	if (!result)
	{
		return false;
	}
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	return true;
}

bool GraphicsClass::RenderScene()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	static float rotation = 0.0f;
	// 	int modelCount;
	// 	int renderCount;
	// 	int index;
	// 	float positionX;
	// 	float positionY;
	// 	float positionZ;
	// 	float radius;
	// 	D3DXVECTOR4 color;
	bool result;
	// 	bool renderModel;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);


	//	renderCount = 0;
	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	rotation += (float)D3DX_PI * 0.0025f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	D3DXMatrixRotationY(&worldMatrix, rotation);
	//m_Frustum->ConsturctFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);
	// 	modelCount = m_ModelList->GetModelCount();
	// 	for (index = 0; index< modelCount;index++)
	// 	{
	// 		m_ModelList->GetData(index, positionX, positionY, positionZ, color);
	// 		radius = 1.0f;
	// 		renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);
	// 		if (renderModel)
	// 		{
	// 			D3DXMatrixTranslation(&worldMatrix, positionX, positionY, positionZ);
	// 			m_Model->Render(m_D3D->GetDeviceContext());
	// 			m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), color, m_Light->GetDiffuseColor(), m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	// 			//Reset the world matrix;
	// 			m_D3D->GetWorldMatrix(worldMatrix);
	// 			renderCount++;
	// 		}
	// 	}
	// 	result = m_Text->SetText(renderCount, m_D3D->GetDeviceContext());
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}
	// 	m_D3D->TurnZBufferOff();
	//Rotate the world matrix by the rotation value so that the triangle will spin.
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
// 	m_Model->Render(m_D3D->GetDeviceContext());
// 	m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 	 		m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
// 	 		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
	//m_MultiTextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());
	// Render the model using the color shader.
	//result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);

	//Render the model using the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture());

	//Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(),m_Light->GetDiffuseColor(),m_Camera->GetPosition(),m_Light->GetSpecularColor(),m_Light->GetSpecularPower());
	//Put the bitmap vertex and idex buffer on the graphic pipeline to prepare them for drawing.

	// 	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	// 	if(!result)
	// 	{
	// 		return false;
	// 	}
	// 	//Render the bitmap with the texture shader.
	// 	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}
	// 	m_D3D->TurnOnAlphaBlending();
	// 	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}
	// 	m_D3D->TurnOffAlphaBlending();
	// 	//Turn the Z buffer back on now that all 2D rendering has completed.
	//m_D3D->TurnZBufferOn();
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
