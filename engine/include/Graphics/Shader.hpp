#ifndef AEYON3D_SHADER_HPP
#define AEYON3D_SHADER_HPP

#include "ShaderProgram.hpp"
#include <unordered_map>
#include "ShaderProperty.hpp"
#include <cstdint>

namespace aeyon
{
    /**
     * Shader class that can be assigned to a Material.
     */
    class Shader
    {
    private:
        std::string m_name;
        std::unordered_map<std::uint32_t, ShaderProgram> m_programs;
        std::unordered_map<std::string, ShaderProperty> m_properties;

        void createPrograms(const std::string& sourceCode);

    public:
        /**
         * Creates and compiles a shader from the given source code.
         * Retrieve the compiled shader program by calling Shader::getShaderProgram.
         * The location of the parsed shader properties can be accessed by Shader::getPropertyMap.
         *
         * TODO: Implement support for shader options
         *
         * @param sourceCode The shader source code
         */
        explicit Shader(const std::string& sourceCode);

        Shader(const Shader& other) = delete;
        Shader& operator=(const Shader& other) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        ~Shader() = default;

        const std::string& getName() const;
        ShaderProgram& getShaderProgram(std::size_t passIndex);
        const std::unordered_map<std::string, ShaderProperty>& getPropertyMap() const;
    };
}


#endif //AEYON3D_SHADER_HPP
