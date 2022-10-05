//
//
//

#ifndef AEYON3D_SHADER_HPP
#define AEYON3D_SHADER_HPP

#include "ShaderProgram.hpp"
#include <unordered_map>
#include "ShaderProperty.hpp"

namespace aeyon
{
    class Shader
    {
    private:
        std::string m_name;
        std::unordered_map<std::uint32_t, ShaderProgram> m_programs;
        std::unordered_map<std::string, ShaderProperty> m_properties;

        void createPrograms(const std::string& sourceCode);

    public:
        explicit Shader(const std::string& sourceCode);

        const std::string& getName() const;
        ShaderProgram& getShaderProgram(std::size_t passIndex);
        const std::unordered_map<std::string, ShaderProperty>& getPropertyMap() const;
    };
}


#endif //AEYON3D_SHADER_HPP
