//
//
//

#ifndef AEYON3D_COLOR_HPP
#define AEYON3D_COLOR_HPP

#include <glm/glm.hpp>

namespace aeyon
{
	class Color
	{
	public:
//        union
//        {
//            struct
//            {
//                float r, g, b, a;
//            };
//            glm::vec4 vec;
//        };

		float r, g, b, a;
		Color();
		explicit Color(float value);
		Color(float red, float green, float blue, float alpha = 1.0f);
		Color(const glm::vec3& v);
		Color(const glm::vec4& v);

		operator glm::vec3() const;
		operator glm::vec4() const;

		bool operator==(const Color& other) const;
		bool operator!=(const Color& other) const;

		static Color fromRGBA32(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha);

		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Cyan;
		static const Color Magenta;
		static const Color Yellow;
		static const Color Black;
		static const Color White;
		static const Color Gray;
		static const Color Transparent;
	};
}


#endif //AEYON3D_COLOR_HPP
