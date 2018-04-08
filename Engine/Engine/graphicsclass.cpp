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
	//m_ReflectionTexture = 0;
	//m_DebuWindow = 0;
	//m_TextureShader = 0;
	//m_Model1 = 0;
	//m_Model2 = 0;
	//m_FogShader = 0;
	//m_clipShader = 0;
	//m_transparentShader = 0;
	//m_FloorModel = 0;
	//m_ReflectionShader = 0;
// 	m_GroundModel = 0;
// 	m_WallModel = 0;
// 	m_BathModel = 0;
// 	m_WallModel = 0;
// 	m_ReflectionTexture = 0;
// 	m_RefractionShader = 0;
// 	m_RefractionShader = 0;
// 	m_WaterShader = 0;
// 	m_Model1 = 0;
// 	m_mulLightShader = 0;
// 	m_light1 = 0;
// 	m_light2 = 0;
// 	m_light3 = 0;
// 	m_light4 = 0;

	m_TextureShader = 0;
	m_FloorModel = 0;
	m_BillboardModel = 0;
	m_depthShaderClass = 0;
	m_InstanceModel = 0;
	m_instanceTextureShader = 0;

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

// 	m_Model1 = new ModelClass1;
// 	if (!m_Model1)
// 	{
// 		return false;
// 	}
// 
// 	// Initialize the model object.
// 	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/seafloor.dds");
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}

// 	m_GroundModel = new ModelClass1;
// 	if (!m_GroundModel)
// 	{
// 	 	return false;
// 	}
	 
	// Initialize the model object.
// 	result = m_GroundModel->Initialize(m_D3D->GetDevice(), "../Engine/data/ground.txt", L"../Engine/data/ground01.dds");
// 	if (!result)
// 	{
// 	 	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 	 	return false;
// 	}
// 
// 	m_WallModel = new ModelClass1;
// 	if (!m_WallModel)
// 	{
// 		return false;
// 	}

	// Initialize the model object.
// 	result = m_WallModel->Initialize(m_D3D->GetDevice(), "../Engine/data/wall.txt", L"../Engine/data/wall01.dds");
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 	m_BathModel = new ModelClass1;
// 	if (!m_BathModel)
// 	{
// 		return false;
// 	}

	// Initialize the model object.
// 	result = m_BathModel->Initialize(m_D3D->GetDevice(), "../Engine/data/bath.txt", L"../Engine/data/marble01.dds");
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 	m_WaterModel = new ModelClass1;
// 	if (!m_WaterModel)
// 	{
// 		return false;
// 	}

	// Initialize the model object.
// 	result = m_WaterModel->Initialize(m_D3D->GetDevice(), "../Engine/data/water.txt", L"../Engine/data/water01.dds");
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}

	


// 	m_Model2 = new ModelClass1;
// 	if (!m_Model2)
// 	{
// 		return false;
// 	}
// 
// 	// Initialize the model object.
// 	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stone01.dds");
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}

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

// 	m_transparentShader = new TransparentShaderClass;
// 	if (!m_transparentShader)
// 	{
// 		return false;
// 	}
// 	result = m_transparentShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
// 		return false;
// 	}
	//Create the light object
// 	m_Light = new LightClass;
// 	if (!m_Light)
// 	{
// 		return false;
// 	}
// 	//Initialize the light objec15
// 	m_Light->SetDirection(1.0f, -1.0f, 0.5f);
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
//  	m_ReflectionTexture = new RenderTextureClass;
// 	if (!m_ReflectionTexture)
// 	{
// 		return false;
// 	}
// 	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
// 	if (!result)
// 	{
// 		return false;
// 	}
// 
// 	m_RefractionTexture = new RenderTextureClass;
// 	if (!m_RefractionTexture)
// 	{
// 		return false;
// 	}
// 	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
// 	if (!result)
// 	{
// 		return false;
// 	}

// 	m_FloorModel = new ModelClass1;
// 	if (!m_FloorModel)
// 	{
// 	 	return false;
// 	}
// 	 
// 	// Initialize the model object.
// 	result = m_FloorModel->Initialize(m_D3D->GetDevice(), "../Engine/data/floor.txt", L"../Engine/data/blue01.dds");
// 	if (!result)
// 	{
// 	 	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 	 	return false;
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

// 	m_ReflectionShader = new ReflectionShaderClass;
// 	if (!m_ReflectionShader)
// 	{
// 		return false;
// 	}
// 	//Initialzie the texture shader object.
// 	result = m_ReflectionShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the texture  shader object.", L"Error", MB_OK);
// 		return false;
// 	}

// 	m_RefractionShader = new Refractionshaderclass;
// 	if (!m_RefractionShader)
// 	{
// 		return false;
// 	}
// 	//Initialzie the texture shader object.
// 	result = m_RefractionShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the texture  shader object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 
// 	m_WaterShader = new Watershaderclass;
// 	if (!m_WaterShader)
// 	{
// 		return false;
// 	}
// 	//Initialzie the texture shader object.
// 	result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the texture  shader object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
//  	m_waterHeight = 2.75f;
//  	m_waterTranslation = 0.0f;

//  	m_Model1 = new ModelClass1;
//  	if (!m_Model1)
//  	{
//  		return false;
//  	}
//  
//  	// Initialize the model object.
//  	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/plane01.txt", L"../Engine/data/stone01.dds");
//  	if (!result)
//  	{
//  		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
//  		return false;
//  	}
// 
// 	m_mulLightShader = new MultPointLightsShader;
// 	if (!m_mulLightShader)
// 	{
// 		return false;
// 	}
// 	result = m_mulLightShader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if (!result)
// 	{
// 		return false;
// 	}
// 
// 	m_light1 = new PointLight;
// 	if (!m_light1)
// 	{
// 		return false;
// 	}
// 	m_light1->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
// 	m_light1->SetPosition(-3.0f, 1.0f, 3.0f);
// 	m_light2 = new PointLight;
// 	if (!m_light2)
// 	{
// 		return false;
// 	}
// 	m_light2->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
// 	m_light2->SetPosition(3.0f, 1.0f, 3.0f);
// 	m_light3 = new PointLight;
// 	if (!m_light3)
// 	{
// 		return false;
// 	}
// 	m_light3->SetDiffuseColor(0.0f, 0.0f, 1.0f, 1.0f);
// 	m_light3->SetPosition(-3.0f, 1.0f, -3.0f);
// 	m_light4 = new PointLight;
// 	if (!m_light4)
// 	{
// 		return false;
// 	}
// 	m_light4->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	m_light4->SetPosition(3.0f, 1.0f, -3.0f);

	m_FloorModel = new ModelClass1;
	if (!m_FloorModel)
	{
		return false;
	}
	result = m_FloorModel->Initialize(m_D3D->GetDevice(), "../Engine/data/floor.txt", L"../Engine/data/grid01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_BillboardModel = new ModelClass1;
	if (!m_BillboardModel)
	{
		return false;
	}
	result = m_BillboardModel->Initialize(m_D3D->GetDevice(), "../Engine/data/square.txt", L"../Engine/data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_depthShaderClass = new DepthShaderClass;
	if (!m_depthShaderClass)
	{
		return false;
	}
	//Initialzie the texture shader object.
	result = m_depthShaderClass->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture  shader object.", L"Error", MB_OK);
		return false;
	}

	m_InstanceModel = new ModelClassInstance;
	if (!m_InstanceModel)
	{
		return false;
	}
	result = m_InstanceModel->Initialize(m_D3D->GetDevice(), L"../Engine/data/seafloor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_instanceTextureShader = new InstanceTextureShaderClass;
	if (!m_instanceTextureShader)
	{
		return false;
	}
	//Initialzie the texture shader object.
	result = m_instanceTextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
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
	// 	if (m_transparentShader)
	// 	{
	// 		m_transparentShader->Shutdown();
	// 		delete m_transparentShader;
	// 		m_transparentShader = 0;
	// 	}

	// 	if (m_ReflectionShader)
	// 	{
	// 		m_ReflectionShader->Shutdown();
	// 		delete m_ReflectionShader;
	// 		m_ReflectionShader = 0;
	// 	}

	// 	if (m_clipShader)
	// 	{
	// 		m_clipShader->Shutdown();
	// 		delete m_clipShader;
	// 		m_clipShader = 0;
	// 	}

	//Release the texture shader object
	// 	if (m_TextureShader)
	// 	{
	// 		m_TextureShader->Shutdown();
	// 		delete m_TextureShader;
	// 		m_TextureShader = 0;
	// 	}
	// 	if (m_FloorModel)
	// 	{
	// 		m_FloorModel->Shutdown();
	// 		delete m_FloorModel;
	// 		m_FloorModel = 0;
	// 	}
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

	// 	if(m_Model1)
	// 	{
	// 	 	m_Model1->Shutdown();
	// 	 	delete m_Model1;
	// 	 	m_Model1 = 0;
	// 	}

	// 	if (m_Model2)
	// 	{
	// 		m_Model2->Shutdown();
	// 		delete m_Model2;
	// 		m_Model2 = 0;
	// 	}


	//Release the text object;
	// 	if (m_Text)
	// 	{
	// 		m_Text->Shutdown();
	// 		delete m_Text;
	// 		m_Text = 0;
	// 	}



	// 	if (m_WaterShader)
	// 	{
	// 		m_WaterShader->Shutdown();
	// 		delete m_WaterShader;
	// 		m_WaterShader = 0;
	// 	}
	// 
	// 	if (m_RefractionShader)
	// 	{
	// 		m_RefractionShader->Shutdown();
	// 		delete m_RefractionShader;
	// 		m_RefractionShader = 0;
	// 	}
	// 
	// 	if (m_LightShader)
	// 	{
	// 		m_LightShader->Shutdown();
	// 		delete m_LightShader;
	// 		m_LightShader = 0;
	// 	}
	// 
	// 	if (m_ReflectionTexture)
	// 	{
	// 		m_ReflectionTexture->Shutdown();
	// 		delete m_ReflectionTexture;
	// 		m_ReflectionTexture = 0;
	// 	}
	// 
	// 	if (m_RefractionTexture)
	// 	{
	// 		m_RefractionTexture->Shutdown();
	// 		delete m_RefractionTexture;
	// 		m_RefractionTexture = 0;
	// 	}
	// 
	// 	if (m_Light)
	// 	{
	// 		delete m_Light;
	// 		m_Light = 0;
	// 	}


	// 	if (m_light1)
	// 	{
	// 		delete m_light1;
	// 		m_light1 = 0;
	// 	}
	// 
	// 	if (m_light2)
	// 	{
	// 		delete m_light2;
	// 		m_light2 = 0;
	// 	}
	// 
	// 	if (m_light3)
	// 	{
	// 		delete m_light3;
	// 		m_light3 = 0;
	// 	}
	// 
	// 	if (m_light4)
	// 	{
	// 		delete m_light4;
	// 		m_light4 = 0;
	// 	}
	// 
	// 	if (m_mulLightShader)
	// 	{
	// 		m_mulLightShader->Shutdown();
	// 		delete m_mulLightShader;
	// 		m_mulLightShader = 0;
	// 	}
	// 
	// 	if (m_Model1)
	// 	{
	// 		m_Model1->Shutdown();
	// 		delete m_Model1;
	// 		m_Model1 = 0;
	// 	}

	if (m_instanceTextureShader)
	{
		m_instanceTextureShader->Shutdown();
		delete m_instanceTextureShader;
		m_instanceTextureShader = 0;
	}

	if (m_InstanceModel)
	{
		m_InstanceModel->Shutdown();
		delete m_InstanceModel;
		m_InstanceModel = 0;
	}

	if (m_depthShaderClass)
	{
		m_depthShaderClass->Shutdown();
		delete m_depthShaderClass;
		m_depthShaderClass = 0;
	}

	if (m_BillboardModel)
	{
		m_BillboardModel->Shutdown();
		delete m_BillboardModel;
		m_BillboardModel = 0;
	}

	if (m_FloorModel)
	{
		m_FloorModel->Shutdown();
		delete m_FloorModel;
		m_FloorModel = 0;
	}

	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
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
// 	m_waterTranslation += 0.001f;
// 	if (m_waterTranslation > 1.0f)
// 	{
// 		m_waterTranslation -= 1.0f;
// 	}
	//m_Camera->SetPosition(0.0f, 2.0f, -12.0f);
	//m_Camera->SetRotation(0.0, 45.0f, 0.0f);
	//m_Camera->SetPosition(1.0f, 1.0f, -10.0f);
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
//	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
//	static float rotation = 0.0f;
// 	int modelCount;
// 	int renderCount;
// 	int index;
// 	float positionX;
// 	float positionY;
// 	float positionZ;
// 	float radius;
//	D3DXVECTOR4 fogColor = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
//	D3DXVECTOR4 clipPlane = D3DXVECTOR4(0.5f, 1.0f, 0.0f, 0.0f);
//	float alpha = 0.5f;



 	bool result;
// 	bool renderModel;
	//The first pass of our render is to a texture now.
	// Render the refraction of the scene to a texture.
// 	result = RenderRefractionToTexture();
// 	if (!result)
// 	{
// 		return false;
// 	}
//  	result = RenderReflectionToTexture();
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	result = RenderScene();
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	return true;

// 	result = RenderBillBorad();
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	return true;

// 	result = RenderDepth();
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	return true;

	result = RenderInstanceModel();
	if (!result)
	{
		return false;
	}
	return true;
	
	

	// Clear the buffers to begin the scene.
	//The second pass of our render is to the back buffer as normal.
	//m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	//result = RenderScene();
// 	if (!result)
// 	{
// 		return false;
// 	}
	//Then after the rendering is complete we render the 2D debug window so we can see the render to texture as a 2D image at the 50x50 pixel location.
	//m_D3D->TurnZBufferOff();
	

//	renderCount = 0;
	// Generate the view matrix based on the camera's position.
	//m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
// 	m_Camera->GetViewMatrix(viewMatrix);
// 	m_D3D->GetWorldMatrix(worldMatrix);
// 	m_D3D->GetProjectionMatrix(projectionMatrix);
// 	m_D3D->GetOrthoMatrix(orthoMatrix);
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
// 	rotation += (float)D3DX_PI * 0.0025f;
// 	if (rotation > 360.0f)
// 	{
// 		rotation -= 360.0f;
// 	}
// 	D3DXMatrixRotationY(&worldMatrix, rotation);
// 
// 	m_Model1->Render(m_D3D->GetDeviceContext());
// 	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model1->GetTexture());
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	D3DXMatrixTranslation(&worldMatrix, 1.0f, 0.0f, -1.0f);
// 	m_D3D->TurnOnAlphaBlending();
// 	m_Model2->Render(m_D3D->GetDeviceContext());
// 	m_FogShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 		m_Model1->GetTexture(),fogColor,0.0f,10.0f);
// 	m_clipShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 		m_Model1->GetTexture(), clipPlane);
// 	result = m_transparentShader->Render(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
// 		m_Model2->GetTexture(), alpha);
// 	if (!result)
// 	{
// 		return false;
// 	}
// 	m_D3D->TurnOffAlphaBlending();
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
	//m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderRefractionToTexture()
{
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	D3DXVECTOR4 clipPlane;
	static float rotation = 0.0f;
	bool result;
	//clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);
	// Set the render target to be the render to texture.
	//m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());
	//Clear the render to texture background to blue so we can differentiate it from the rest of the normal scene.
	//m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->Render();
	//Use the camera to calculate the reflecitonMatrix;
	//m_Camera->RenderReflection(-1.5f);
	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	//result = RenderScene();
	//reflectionMatrix = m_Camera->GetReflectionViewMatrix();
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	
// 	D3DXMatrixTranslation(&worldMatrix, 0.0f,2.0f, 0.0f);
// 	m_BathModel->Render(m_D3D->GetDeviceContext());
// 
// 	result = m_RefractionShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
// 		projectionMatrix, m_BathModel->GetTexture(), m_Light->GetDirection(),
// 		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), clipPlane);
// 	if (!result)
// 	{
// 		return false;
// 	}

// 	rotation += (float)D3DX_PI * 0.005f;
// 	if (rotation > 360.0f)
// 	{
// 		rotation -= 360.0f;
// 	}
// 	D3DXMatrixRotationY(&worldMatrix, rotation);

// 	m_Model1->Render(m_D3D->GetDeviceContext());
// 	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, reflectionMatrix, projectionMatrix, m_Model1->GetTexture());
// 	if (!result)
// 	{
// 		return false;
// 	}
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();
	return true;
}

bool GraphicsClass::RenderReflectionToTexture()
{
	D3DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	bool result;


	// Set the render target to be the reflection render to texture.
	//m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the reflection render to texture.
	//m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);
	//The reflection matrix is setup using the water height.

		// Use the camera to render the reflection and create a reflection view matrix.
		//m_Camera->RenderReflection(m_waterHeight);

	// Get the camera reflection view matrix instead of the normal view matrix.
	reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Translate to where the wall model will be rendered.
	D3DXMatrixTranslation(&worldMatrix, 0.0f, 6.0f, 8.0f);

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_WallModel->Render(m_D3D->GetDeviceContext());

	// Render the wall model using the light shader and the reflection view matrix.
// 	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, reflectionViewMatrix,
// 		projectionMatrix, m_WallModel->GetTexture(), m_Light->GetDirection(),
// 		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);
// 	if (!result)
// 	{
// 		return false;
// 	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::RenderScene()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX reflectionMatrix;
	D3DXVECTOR4 diffuseColor[4];
	D3DXVECTOR4 lightPosition[4];

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

// 	diffuseColor[0] = m_light1->GetDiffuseColor();
// 	diffuseColor[1] = m_light2->GetDiffuseColor();
// 	diffuseColor[2] = m_light3->GetDiffuseColor();
// 	diffuseColor[3] = m_light4->GetDiffuseColor();
// 
// 	lightPosition[0] = m_light1->GetPosition();
// 	lightPosition[1] = m_light2->GetPosition();
// 
// 	lightPosition[2] = m_light3->GetPosition();
// 
// 	lightPosition[3] = m_light4->GetPosition();



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
	// 	rotation += (float)D3DX_PI * 0.005f;
	// 	if (rotation > 360.0f)
	// 	{
	// 		rotation -= 360.0f;
	// 	}
	// 	D3DXMatrixRotationY(&worldMatrix, rotation);
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
	// 	m_Model1->Render(m_D3D->GetDeviceContext());
	// 	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model1->GetTexture());
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}
	// 
	// 	m_D3D->GetWorldMatrix(worldMatrix);
	// 	D3DXMatrixTranslation(&worldMatrix, 0.0f, -1.5f, 0.0f);
	// 	reflectionMatrix = m_Camera->GetReflectionViewMatrix();
	// 	m_FloorModel->Render(m_D3D->GetDeviceContext());
	// 	result = m_ReflectionShader->Render(m_D3D->GetDeviceContext(), m_FloorModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_FloorModel->GetTexture(), m_ReflectionTexture->GetShaderResourceView(), reflectionMatrix);

	//D3DXMatrixTranslation(&worldMatrix, 0.0f, 1.0f, 0.0f);

	// Put the ground model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// 	m_GroundModel->Render(m_D3D->GetDeviceContext());
	// 
	// 	// Render the ground model using the light shader.
	// 	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix,
	// 		projectionMatrix, m_GroundModel->GetTexture(), m_Light->GetDirection(),
	// 		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}

	// Reset the world matrix.
	// 	m_D3D->GetWorldMatrix(worldMatrix);
	// 
	// 	// Translate to where the wall model will be rendered.
	// 	D3DXMatrixTranslation(&worldMatrix, 0.0f, 6.0f, 8.0f);
	// 
	// 	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// 	m_WallModel->Render(m_D3D->GetDeviceContext());
	// 
	// 	// Render the wall model using the light shader.
	// 	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_WallModel->GetIndexCount(), worldMatrix, viewMatrix,
	// 		projectionMatrix, m_WallModel->GetTexture(), m_Light->GetDirection(),
	// 		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}
	// 
	// 	// Reset the world matrix.
	// 	m_D3D->GetWorldMatrix(worldMatrix);
	// 
	// 
	// 	// Translate to where the bath model will be rendered.
	// 	D3DXMatrixTranslation(&worldMatrix, 0.0f, 2.0f, 0.0f);
	// 
	// 	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// 	m_BathModel->Render(m_D3D->GetDeviceContext());
	// 
	// 	// Render the bath model using the light shader.
	// 	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
	// 		projectionMatrix, m_BathModel->GetTexture(), m_Light->GetDirection(),
	// 		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f);
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}
	// 
	// 	// Reset the world matrix.
	// 	m_D3D->GetWorldMatrix(worldMatrix);
	// 
	// 	// Get the camera reflection view matrix.
	// 	reflectionMatrix = m_Camera->GetReflectionViewMatrix();
	// 
	// 	// Translate to where the water model will be rendered.
	// 	D3DXMatrixTranslation(&worldMatrix, 0.0f, m_waterHeight, 0.0f);
	// 
	// 	// Put the water model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	// 	m_WaterModel->Render(m_D3D->GetDeviceContext());
	// 
	// 	// Render the water model using the water shader.
	// 	result = m_WaterShader->Render(m_D3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix,
	// 		projectionMatrix, reflectionMatrix, m_ReflectionTexture->GetShaderResourceView(),
	// 		m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(),
	// 		m_waterTranslation, 0.01f);
	// 	if (!result)
	// 	{
	// 		return false;
	// 	}

// 	m_Model1->Render(m_D3D->GetDeviceContext());
// 	result = m_mulLightShader->Render(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model1->GetTexture(), diffuseColor, lightPosition);
// 	if (!result)
// 	{
// 		return false;
// 	}


	m_D3D->EndScene();
	return true;
}

bool GraphicsClass::RenderBillBorad()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	D3DXMATRIX translateMatrix;
	bool result;
	D3DXVECTOR3 cameraPosition;
	D3DXVECTOR3 modelPosition;
	double angle;
	float rotation;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_FloorModel->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_FloorModel->GetIndexCount(),worldMatrix,viewMatrix,projectionMatrix,m_FloorModel->GetTexture());
	if (!result)
	{
		return false;
	}


	cameraPosition = m_Camera->GetPosition();

	modelPosition.x = 0.0f;
	modelPosition.y = 1.5f;
	modelPosition.z = 0.0f;

	rotation = atan2(modelPosition.x - cameraPosition.x,modelPosition.z - cameraPosition.z);
	D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixTranslation(&translateMatrix, modelPosition.x, modelPosition.y, modelPosition.z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);
	m_BillboardModel->Render(m_D3D->GetDeviceContext());
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(),m_BillboardModel->GetIndexCount(),worldMatrix,viewMatrix,projectionMatrix,m_BillboardModel->GetTexture());
	m_D3D->EndScene();
	return true;
}

bool GraphicsClass::RenderDepth()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_FloorModel->Render(m_D3D->GetDeviceContext());
	result = m_depthShaderClass->Render(m_D3D->GetDeviceContext(), m_FloorModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}
	m_D3D->EndScene();
	return true;
}

bool GraphicsClass::RenderInstanceModel()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_InstanceModel->Render(m_D3D->GetDeviceContext());
	result = m_instanceTextureShader->Render(m_D3D->GetDeviceContext(), m_InstanceModel->GetVertexCount(), m_InstanceModel->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix, m_InstanceModel->GetTexture());
	if (!result)
	{
		return false;
	}
	m_D3D->EndScene();
	return true;
}


