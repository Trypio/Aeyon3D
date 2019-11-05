//
// Created by thors on 05.11.2019.
//

#ifndef AEYON3D_TEXTURECACHE_HPP
#define AEYON3D_TEXTURECACHE_HPP

#include "ResourceCache.hpp"
#include "Util.hpp"

namespace aeyon
{
	struct TextureMetaData
	{
		Texture::Type type;
		std::string paths[6];
		PixelFormat format;
		bool releaseMemory;
	};

	class TextureCache : public ResourceCache<Texture, TextureMetaData>
	{
	public:
		std::unique_ptr<Texture> create(const TextureMetaData& meta) override
		{
			switch (meta.type)
			{
				case Texture::Type::Tex2D:
					return util::loadTexture2DFromFile(meta.paths[0], meta.format, meta.releaseMemory);
				case Texture::Type::Cube:
					return util::loadCubeMapFromFiles(
							std::vector<std::string>(meta.paths, meta.paths + 6),
							meta.format,
							meta.releaseMemory
					);
				default:
					throw std::runtime_error("Not implemented!");
			}
		}
	};
}

#endif //AEYON3D_TEXTURECACHE_HPP
