#ifndef AEYON3D_SHADERPARSER_HPP
#define AEYON3D_SHADERPARSER_HPP

#include <string>
#include <vector>

namespace aeyon
{
    /**
     * A very simple parser for the experimental Aeyon Shader Language (ASL). It basically converts high level
     * ASL code into structured data (shader properties, code of shader passes) that can be used by the Shader class
     * to compile more specific shader programs.
     *
     * TODO: Separate code parsing and parse result. ex.: ShaderParseResult = ShaderParser::parse(sourceCode)
     */
    class ShaderParser
    {
    public:
        struct Property
        {
            std::string type;
            std::string name;
        };

        struct Pass
        {
            std::string vertexCode;
            std::string fragmentCode;
        };

    private:
        std::string m_name;
        std::vector<Property> m_properties;
        std::vector<Pass> m_passes;

        void parseName(const std::string& code, std::size_t& index);
        void parseProperties(const std::string& code, std::size_t& index);
        void parsePasses(const std::string& code, std::size_t& index);

    public:
        explicit ShaderParser(const std::string& sourceCode);

        const std::string& getName() const;
        const std::vector<Property>& getProperties() const;
        const std::vector<Pass>& getPasses() const;
    };
}

#endif //AEYON3D_SHADERPARSER_HPP
