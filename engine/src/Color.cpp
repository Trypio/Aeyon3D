//
//
//

#include "Color.hpp"

namespace aeyon
{
	Color::Color()
	: Color(0.0f)
	{
	}

	Color::Color(float value)
			: Color(value, value, value)
	{
	}

	Color::Color(float red, float green, float blue, float alpha)
			: r(red), g(green), b(blue), a(alpha)
	{
	}

	Color::Color(const glm::vec3& v)
			: Color(v.r, v.g, v.b, 1.0f)
	{
	}

	Color::Color(const glm::vec4& v)
			: Color(v.r, v.g, v.b, v.a)
	{
	}

	Color::operator glm::vec3() const
	{
		return glm::vec3(r, g, b);
	}

	Color::operator glm::vec4() const
	{
		return glm::vec4(r, g, b, a);
	}


	bool Color::operator==(const Color& other) const
	{
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	bool Color::operator!=(const Color& other) const
	{
		return !(*this == other);
	}

	Color Color::fromRGBA32(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
	{
		return {red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f};
	}

	const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::Cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::Magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
	const Color Color::Yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
	const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
	const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
	const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
	const Color Color::Transparent = Color(0.0f, 0.0f, 0.0f, 0.0f);
}