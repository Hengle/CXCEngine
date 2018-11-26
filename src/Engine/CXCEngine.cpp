#include "CXCEngine.h"

namespace cxc
{
	GEngine::GEngine()
	{

	}

	GEngine::~GEngine()
	{

	}

	void GEngine::ConfigureEngineDisplaySettings(const DisplayParameters& DisplayConf)
	{
		auto pWindowMgr = WindowManager::GetInstance();
		if (pWindowMgr)
		{
			pWindowMgr->SetWindowHeight(DisplayConf.WindowHeight);
			pWindowMgr->SetWindowWidth(DisplayConf.WindowWidth);
			pWindowMgr->SetWindowTitle(DisplayConf.ApplicationTitle);
			pWindowMgr->SetWindowPos(DisplayConf.WindowPosX, DisplayConf.WindowPosY);
			pWindowMgr->isDecoraded = DisplayConf.bIsDecorated;

			pWindowMgr->x_pos = DisplayConf.WindowPosX; pWindowMgr->y_pos = DisplayConf.WindowPosY;
		}
	}

	void GEngine::BindMeshRender(std::shared_ptr<MeshRender> pRender, std::shared_ptr<Object3D> pObject, uint32_t MeshIndex)
	{
		auto pMesh = pObject->GetMesh(MeshIndex);
		if (pMesh)
		{
			pMesh->BindMeshRender(pRender);
		}
	}

	void GEngine::InitializeEngine()
	{
		auto World = World::GetInstance();
		if (World)
		{
			// Initialize the engine
			World->Initialize();
		}
	}

	void GEngine::SetCamera(const glm::vec3& CameraPosition, const glm::vec3& CameraOrigin, const glm::vec3& UpVector, const glm::mat4 ProjectionMatrix)
	{
		auto World = World::GetInstance();
		if (World)
		{
			// Set camera
			World->pSceneMgr->SetCameraParams(CameraPosition, CameraOrigin, UpVector, ProjectionMatrix);

			World->pSceneMgr->InitCameraStatus(World->pWindowMgr->GetWindowHandle());
		}
	}

	void GEngine::StartEngine()
	{
		auto World = World::GetInstance();
		if (World)
		{
			// Start to run
			World->run();
		}
	}
}