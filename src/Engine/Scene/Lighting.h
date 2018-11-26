#ifdef WIN32

#include "..\General\DefineTypes.h"

#else

#include "../General/DefineTypes.h"

#endif

#ifndef CXC_LIGHTING_H
#define CXC_LIGHTING_H

namespace cxc {
	enum class eLightType : uint16_t {
		Directional,
		Spot,
		OmniDirectional,
		Area,
		Volumetric,
		InvalidType
	};

	class BaseLighting
	{

		friend class FBXSDKUtil;

	public:

		BaseLighting();
		BaseLighting(const std::string& Name, const glm::vec3 &pos, const glm::vec3 &dir, float Intensity, eLightType type);
		virtual ~BaseLighting();

	public:

		void SetLightPos(const glm::vec3 &pos) noexcept;
		void SetLightType(eLightType type) noexcept;
		void SetDirection(const glm::vec3 &dir) noexcept;
		void SetIntensity(float NewIntensity) { LightIntensity = NewIntensity; }

		glm::vec3 GetDirection() const noexcept;
		eLightType GetLightType() const noexcept;
		glm::vec3 GetLightPos() const noexcept;;
		const std::string& GetLightName() const { return LightName; }
		float GetIntensity() const { return LightIntensity; }

	private:

		std::string LightName;

		glm::vec3 LightColor;

		glm::vec3 LightPos;

		glm::vec3 LightDirection;

		float LightIntensity;

		eLightType LightType;

		bool bCastLight;

		bool bCastShadow;

	};

}
#endif // CXC_LIGHTING_H