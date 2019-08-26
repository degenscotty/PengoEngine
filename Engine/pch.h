#include "targetver.h"

#include <windows.h>

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm.hpp>

#include <fmod.hpp>

#pragma warning (push)
#pragma warning (disable:4505)
#include <fmod_errors.h>
#pragma warning (pop)

#include "Log.h"

template<class T>
inline void SafeDelete(T &pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
