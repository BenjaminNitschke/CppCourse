#pragma once

namespace CppGameEngine
{
	struct Vector2D
	{
		float x, y;

		Vector2D()
		{
			x = y = 0;
		}

		Vector2D(const float& x, const float& y)
			: x(x), y(y) {}

		Vector2D operator*(const float& scale) const
		{
			return Vector2D(x*scale, y*scale);
		}

		Vector2D operator+(const Vector2D& other) const
		{
			return Vector2D(x+other.x, y+other.y);
		}
	};
}