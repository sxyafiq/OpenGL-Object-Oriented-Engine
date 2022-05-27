#pragma once
#include <string_view>
#include "Object.h"
#include "Collision.h"

inline constexpr auto hash(const std::string_view sv) {
    unsigned long hash{ 5381 };
    for (unsigned char c : sv) {
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

inline constexpr auto operator"" _sh(const char* str, size_t len) {
    return hash(std::string_view{ str, len });
}

class CollisionSystem
{
public:
	void DoCollision(Object& firstObj, Object& secondObj);

	bool IsIntersecting() const noexcept { return m_IsIntersecting; }
private:
	bool m_IsIntersecting = false;
};