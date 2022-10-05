//
//
//

#ifndef AEYON3D_UTIL_HPP
#define AEYON3D_UTIL_HPP

#include "Graphics/Texture.hpp"
#include <string>
#include <memory>
#include "stb_image.h"
#include <fstream>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include "Graphics/Mesh.hpp"
#include <iostream>
#include "Graphics/Shader.hpp"

namespace aeyon
{
	namespace util
	{
		static std::unique_ptr<Texture> loadTexture2DFromFile(const std::string& path, const PixelFormat& format,
																													bool releaseMemory = false)
		{
			stbi_set_flip_vertically_on_load(1);

			int width, height, channels;
			auto data = stbi_load(path.c_str(), &width, &height, &channels, static_cast<int>(format.getNumChannels()));

			stbi_set_flip_vertically_on_load(0);

			if (!data)
			{
				throw std::runtime_error(path + " could not be loaded!");
			}

			auto tex = std::make_unique<Texture>(Texture::Type::Tex2D, format, width, height);
			tex->setPixelDataRaw(data);

			stbi_image_free(data);

			tex->apply(releaseMemory);

			return tex;
		}

		static std::unique_ptr<Texture> loadCubeMapFromFiles(const std::vector<std::string>& paths,
				                                                 const PixelFormat& format,
				                                                 bool releaseMemory = false)
		{
			std::unique_ptr<Texture> tex = nullptr;

			for (std::size_t face = 0; face < 6; face++)
			{
				int width, height, channels;
				auto data = stbi_load(paths[face].c_str(), &width, &height, &channels, static_cast<int>(format.getNumChannels()));

				if (!tex)
				{
					tex = std::make_unique<Texture>(Texture::Type::Cube, format, width, height);
					tex->setWrapMode(Texture::WrapMode::Clamp);
					tex->setAnisoLevel(1.0f);
					tex->setFilterMode(Texture::FilterMode::Bilinear);
				}

				tex->setPixelDataRaw(data, face);

				stbi_image_free(data);
			}

			tex->apply(releaseMemory);


			return tex;
		}


		static std::unique_ptr<Shader> loadShaderFromFile(const std::string& path)
		{
			std::ifstream file(path);

			if (!file)
			{
				throw std::runtime_error(std::string("Shader file ") + path + " could not be opened");
			}

			std::string code = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

			file.close();

			return std::make_unique<Shader>(code);
		}

		template <typename T>
		static std::vector<T> flatten(const std::vector<std::vector<T>>& v)
		{
			std::size_t totalSize = 0;

			for (const auto& sub : v)
			{
				totalSize += sub.size();
			}

			std::vector<T> result;
			result.reserve(totalSize);

			for (const auto& sub : v)
			{
				result.insert(result.end(), sub.begin(), sub.end());
			}

			return result;
		}

		static void dumpGLSL(const std::string& filename, const std::string& code)
		{
			std::ofstream ofs(std::string("shaders/dump/") + filename);

			if (!ofs)
			{
				std::cout << "Shader Dump: File " << filename << " could not be created" << std::endl;
				return;
			}

			ofs << code;
		}

		static bool endsWith(const std::string& str, const std::string& ending)
		{
			if (str.length() >= ending.length())
			{
				return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
			}
			else
			{
				return false;
			}
		}
	}
}

#endif //AEYON3D_UTIL_HPP
