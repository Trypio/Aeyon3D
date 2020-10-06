//
//
//

#include "Graphics/Light.hpp"

namespace aeyon
{
	Light::Light()
			: m_type(Type::Directional), m_color(Color::White), m_intensity(1.0f),
				m_range(10.0f), m_spotAngle(30.0f)
	{
	}

	void Light::setType(Light::Type type)
	{
		m_type = type;
	}

	void Light::setColor(Color color)
	{
		m_color = color;
	}

	void Light::setIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::setRange(float range)
	{
		m_range = range;
	}

	void Light::setSpotAngle(float spotAngle)
	{
		m_spotAngle = glm::clamp(spotAngle, 1.0f, 179.0f);
	}

	Light::Type Light::getType() const
	{
		return m_type;
	}

	Color Light::getColor() const
	{
		return m_color;
	}

	float Light::getIntensity() const
	{
		return m_intensity;
	}

	float Light::getRange() const
	{
		return m_range;
	}

	float Light::getSpotAngle() const
	{
		return m_spotAngle;
	}
}
