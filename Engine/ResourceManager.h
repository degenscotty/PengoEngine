#pragma once
#include "Singleton.h"
#include "Texture2D.h"
#include "Font.h"

class ResourceManager : public Singleton<ResourceManager>
{
public:
	ResourceManager();
	~ResourceManager();

	Texture2D* LoadTexture(const std::string& file);
	Font* LoadFont(const std::pair<std::string, unsigned int>& fontData);
private:
	struct pair_hash
	{
		template <class T1, class T2>
		size_t operator()(const std::pair<T1, T2>& pair) const
		{
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};

	std::string m_FolderPath;

	std::unordered_map<std::string, Texture2D*> m_Textures;
	std::unordered_map<std::pair<std::string, unsigned int>, Font*, pair_hash> m_Fonts;
};

