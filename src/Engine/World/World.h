#ifdef WIN32

#include "..\General\EngineCompoents.h"
#include "..\General\DefineTypes.h"
#include "..\Utilities\Singleton.inl"
#include "..\World\LogicFramework.h"
#include "..\Physics\PhysicalWorld.h"

#else

#include "../General/EngineCompoents.h"
#include "../General/DefineTypes.h"
#include "../Utilities/Singleton.inl"
#include "../World/LogicFramework.h"
#include "../Physics/PhysicalWorld.h"

#endif // WIN32

#define _CRT_SECURE_NO_WARINGS

#ifndef CXC_WORLD_H
#define CXC_WORLD_H

#define MAX_DISTANCE 5000.0f
#define MIN_DISTANCE 50.0f
#define ZOOMING_SPEED 100.0f
#define MOUSE_ROTATE_ANGLE_SPEED 1.0f

namespace cxc {

	const float FixedDeltaSeconds_30FPS = 0.3333f;
	const float FixedDeltaSeconds_60FPS = 0.1667f;

	using SystemClock = std::chrono::time_point<std::chrono::system_clock>;

	// Input handler
	void KeyBoradCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);
	void MouseCallBack(GLFWwindow *window, int button, int action, int mods);
	void CursorPosCallBack(GLFWwindow *window,double x,double y);
	void ScrollBarCallBack(GLFWwindow *window,double x,double y);

	// Window description
	typedef struct WindowDescriptor {
		GLint SamplingLevel;
		GLboolean isEnableDepth;
		GLboolean isForwardComptible;
		Color BackGroundColor;

		bool operator ==(const WindowDescriptor &windes) {
			return SamplingLevel == windes.SamplingLevel
				&& isEnableDepth == windes.isEnableDepth
				&& isForwardComptible == windes.isForwardComptible
				&& BackGroundColor == windes.BackGroundColor;
		}
	} WindowDescriptor;

	class World final : public Singleton<World>, public std::enable_shared_from_this<World>
	{
	public:

		friend Singleton<World>;

		explicit World();
		~World();

		World(const World &) = delete;
		World(const World &&) = delete;

		World& operator=(const World &) = delete;
		World& operator=(const World &&) = delete;

	public:

		void AddObject(const std::shared_ptr<Object3D > &pObject, bool isKinematics = false) noexcept;

	public:

		GLboolean CreateAndDisplayWindow(GLint Height,GLint Width,const std::string Title);

	// Configuration
	public:

		void SetRenderingFrameRates(uint32_t NewFrameRates) { RenderingFrameRates = NewFrameRates; }
		uint32_t GetRenderingFrameRates() const { return RenderingFrameRates; }
		void SetBackGroundColor(float red, float green, float blue, float alpha) noexcept;
		void SetWindowParams(const WindowDescriptor &windes) noexcept;
		void SetGraphicsLibVersion(GLint HighByte,GLint LowByte) noexcept;
		void SetWindowPosition(GLint x, GLint y) noexcept { pWindowMgr->x_pos = x; pWindowMgr->y_pos = y; };

	public:

		void Initialize() noexcept;
		void InitInputMode() noexcept;

	public:

		void CleanFrameBuffer() const noexcept;
		void CleanGL() noexcept {glfwTerminate();};
		void StoreAndSetMousePos() noexcept;

		void WorldLooping() noexcept;

		void run() noexcept;
		
		// Tick manager
	public:

		void Tick();

	private:

		void RenderingTick();

		void LogicFrameworkTick();

		void PhysicsTick() noexcept;

		// Time
	public:

		float GetWorldSeconds() const;

	public:

		// Pointer to the manager
		std::shared_ptr<InputManager> pInputMgr;
		std::shared_ptr<WindowManager> pWindowMgr;
		std::shared_ptr<SceneManager> pSceneMgr;

		// Shader path
		void SetSceneSize(const glm::vec3 &center, float size) noexcept { pSceneMgr->SetCenter(center); pSceneMgr->SetSize(size); }

	// Physics
	public:

		void SetGravity(GLfloat x,GLfloat y,GLfloat z) noexcept;

	public:

		// flag representing the status
		GLboolean GameOver;

		static std::function<void(int key, int scancode, int action, int mods)> KeyInputCallBack;

	private:

		uint32_t RenderingFrameRates;

		SystemClock WorldStartSeconds;

		float LastRenderingTickSeconds, LastLogicWorldTickSeconds, LastPhysicalWorldTickSeconds;

		std::shared_ptr<LogicFramework> m_LogicFramework;

		std::shared_ptr<PhysicalWorld> m_PhysicalWorld;
	};
}

#endif // CXC_WORLD_H