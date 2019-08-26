#pragma once

namespace utils
{
	bool IsPointInRect(const glm::vec2& mousePos, const glm::vec4& rect);
	bool IsOverlapping(const glm::vec4& r1, const glm::vec4& r2);
}