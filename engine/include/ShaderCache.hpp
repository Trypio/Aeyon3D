//
// Created by thors on 05.11.2019.
//

#ifndef AEYON3D_SHADERCACHE_HPP
#define AEYON3D_SHADERCACHE_HPP

#include "ResourceCache.hpp"
#include "Util.hpp"

namespace aeyon
{
	struct ShaderMetaData
	{
		std::string path;
	};

	class ShaderCache : public ResourceCache<Shader, ShaderMetaData>
	{
		std::unique_ptr<Shader> create(const ShaderMetaData& meta) override
		{
			return util::loadShaderFromFile(meta.path);
		}
	};
}

#endif //AEYON3D_SHADERCACHE_HPP
