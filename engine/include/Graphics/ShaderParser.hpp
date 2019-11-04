//
//
//

#ifndef AEYON3D_SHADERPARSER_HPP
#define AEYON3D_SHADERPARSER_HPP

#include <string>
#include <vector>

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

	std::string getName() const;
	std::vector<Property> getProperties() const;
	std::vector<Pass> getPasses() const;;
};

#endif //AEYON3D_SHADERPARSER_HPP
