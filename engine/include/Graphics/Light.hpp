//
//
//

#ifndef AEYON3D_DIRECTIONALLIGHT_HPP
#define AEYON3D_DIRECTIONALLIGHT_HPP

#include "Color.hpp"
#include "ECS/ComponentTypeIndex.hpp"

namespace aeyon
{
	class Light : public ComponentTypeIndex<Light>
	{
	public:
		enum class Type
		{
			Directional,
			Point,
			Spot
		};

		enum class RenderMode
		{
			Auto,
			ForceVertex,
			ForcePixel
		};

	private:
		Type m_type;
		RenderMode m_renderMode;
		Color m_color;
		float m_intensity;
		float m_range;
		float m_spotAngle;

	public:
		Light();

		void setType(Type type);
		void setRenderMode(RenderMode renderMode);
		void setColor(Color color);
		void setIntensity(float intensity);
		void setRange(float range);
		void setSpotAngle(float spotAngle);

		Type getType() const;
		RenderMode getRenderMode() const;
		Color getColor() const;
		float getIntensity() const;
		float getRange() const;
		float getSpotAngle() const;
	};
}


#endif //AEYON3D_DIRECTIONALLIGHT_HPP
