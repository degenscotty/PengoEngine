#pragma once

namespace utils
{
	bool IsPointInRect(const glm::vec2& mousePos, const glm::vec4& rect)
	{
		return (mousePos.x >= rect.x && mousePos.x <= rect.x + rect.z &&
			mousePos.y >= rect.y && mousePos.y <= rect.y + rect.w);
	}
}