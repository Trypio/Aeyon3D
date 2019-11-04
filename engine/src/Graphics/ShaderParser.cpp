//
//
//

#include "Graphics/ShaderParser.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>


ShaderParser::ShaderParser(const std::string& sourceCode)
{
	std::size_t index = 0;

	parseName(sourceCode, index);
	parseProperties(sourceCode, index);
	parsePasses(sourceCode, index);
}

std::string ShaderParser::getName() const
{
	return m_name;
}

std::vector<ShaderParser::Property> ShaderParser::getProperties() const
{
	return m_properties;
}

std::vector<ShaderParser::Pass> ShaderParser::getPasses() const
{
	return m_passes;
}

void ShaderParser::parseName(const std::string& code, std::size_t& index)
{
	std::size_t idxSearch, idxStart = 0, idxEnd = 0;

	idxSearch = code.find("//$$ SHADER \"");

	if (idxSearch == std::string::npos)
	{
		throw std::runtime_error("No valid SHADER tag found");
	}

	idxStart = idxSearch + 13;

	idxSearch = code.find('\"', idxStart + 1);

	if (idxSearch == std::string::npos)
	{
		throw std::runtime_error("No valid SHADER tag found");
	}

	idxEnd = idxSearch;

	m_name = code.substr(idxStart, idxEnd - idxStart);
	index = idxEnd;
}

void ShaderParser::parseProperties(const std::string& code, std::size_t& index)
{
	std::size_t idxSearch, idxStart = index, idxEnd = index;

	idxSearch = code.find("//$$ PROPERTIES_BEGIN", idxEnd);

	if (idxSearch != std::string::npos)
	{
		idxStart = idxSearch + 22;

		idxSearch = code.find("//$$ PROPERTIES_END", idxStart);

		if (idxSearch == std::string::npos)
		{
			throw std::runtime_error("No PROPERTIES_END tag found");
		}

		idxEnd = idxSearch;

		std::string props = code.substr(idxStart, idxEnd - idxStart);
		std::istringstream iss(props);

		std::string line;

		char type[50], name[50];

		do
		{
			std::getline(iss, line);

			if (std::sscanf(line.c_str(), "%s %[^;];\n", type, name) == 2)
			{
				m_properties.push_back({ type, name });
			}
		}
		while (iss.good());
	}

	index = idxEnd;
}

void ShaderParser::parsePasses(const std::string& code, std::size_t& index)
{
	std::size_t idxSearch, idxStart = index, idxEnd = index;

	idxSearch = code.find("//$$ PASS_BEGIN", idxEnd);

	while (idxSearch != std::string::npos)
	{
		Pass pass;

		idxSearch = code.find("//$$ VERTEX_BEGIN", idxSearch);

		if (idxSearch == std::string::npos)
		{
			throw std::runtime_error("A PASS needs a vertex shader");
		}

		idxStart = idxSearch + 18;

		idxSearch = code.find("//$$ VERTEX_END", idxStart);

		if (idxSearch == std::string::npos)
		{
			throw std::runtime_error("Missing VERTEX_END tag");
		}

		idxEnd = idxSearch;

		pass.vertexCode = code.substr(idxStart, idxEnd - idxStart);


		idxSearch = code.find("//$$ FRAGMENT_BEGIN", idxEnd);

		if (idxSearch == std::string::npos)
		{
			throw std::runtime_error("A PASS needs a fragment shader");
		}

		idxStart = idxSearch + 20;

		idxSearch = code.find("//$$ FRAGMENT_END", idxStart);

		if (idxSearch == std::string::npos)
		{
			throw std::runtime_error("Missing FRAGMENT_END tag");
		}

		idxEnd = idxSearch;

		pass.fragmentCode = code.substr(idxStart, idxEnd - idxStart);


		idxSearch = code.find("//$$ PASS_END", idxSearch);

		if (idxSearch == std::string::npos)
		{
			throw std::runtime_error("Missing PASS_END tag");
		}

		m_passes.push_back(pass);
		index = idxSearch + 14;

		idxSearch = code.find("//$$ PASS_BEGIN", idxSearch + 14);
	}
}



