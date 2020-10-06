//
//
//

#ifndef AEYON3D_DIRECTIONALLIGHT_HPP
#define AEYON3D_DIRECTIONALLIGHT_HPP

#include "Color.hpp"
#include "Component.hpp"

namespace aeyon
{
	/**
	 * Represents a 3D light
	 */
	class Light : public Component
	{
	public:
		enum class Type
		{
			Directional,
			Point,
			Spot
		};

	private:
		Type m_type;
		Color m_color;
		float m_intensity;
		float m_range;
		float m_spotAngle;

	public:
		Light();

		void setType(Type type);
		void setColor(Color color);
		void setIntensity(float intensity);
		void setRange(float range);
		void setSpotAngle(float spotAngle);

		Type getType() const;
		Color getColor() const;
		float getIntensity() const;
		float getRange() const;
		float getSpotAngle() const;
	};
}


#endif //AEYON3D_DIRECTIONALLIGHT_HPP
