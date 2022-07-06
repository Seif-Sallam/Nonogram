#pragma once
#include <iostream>
#include <math.h>
#include "SFML/System/Vector2.hpp"

template<class T>
class Vec2 {
public:
	T x, y;

	inline Vec2() : x(T()), y(T()) {}
	inline Vec2(const sf::Vector2<T>& sfVec2) : x(sfVec2.x), y(sfVec2.y) {}
	inline Vec2(T x, T y) : x(x), y(y) {}
	inline Vec2(const Vec2& vec2) : x(vec2.x), y(vec2.y) {}
	inline Vec2<T>& operator=(const Vec2& vec2) { x = vec2.x; y = vec2.y; return *this; }
	inline Vec2<T>& Zero() { x = 0; y = 0; return *this; }
	inline Vec2<T>& One() { x = 0; y = 0; return *this; }
	inline Vec2<T>& Normalize(){
		double length = sqrt(pow(x, 2) + pow(y, 2));
		x = x / length;
		y = y / length;
		return *this;
	}
	
	inline operator Vec2<float>() { return Vec2<float>(x, y); }

	template<class U = T>
	inline sf::Vector2<U> sfVec()
	{
		return sf::Vector2<U>(x, y);
	}
	operator sf::Vector2<T>() { return sf::Vector2<T>(x,y); }
	
	inline friend std::ostream& operator<<(std::ostream& stream, const Vec2<T>& vec) {
		stream << "(" << vec.x << ", " << vec.y << ")";
		return stream;
	}

	inline Vec2<T> operator+(const Vec2<T>& vec)
	{
		return Vec2<T>(x + vec.x, y + vec.y);
	}
	inline Vec2<T> operator-(const Vec2<T>& vec)
	{
		return Vec2<T>(x - vec.x, y - vec.y);
	}
	inline Vec2<T> operator-=(const Vec2<T>& vec)
	{
		return Vec2<T>(x - vec.x, y - vec.y);
	}
	inline Vec2<T> operator+=(const Vec2<T>& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	inline Vec2<T> operator*(const Vec2<T>& vec)
	{
		return Vec2<T>(x * vec.x, y * vec.y);
	}
	inline Vec2<T> operator*(const T& scaler)
	{
		return Vec2<T>(x * scaler, y * scaler);
	}
	inline Vec2<T> operator/(const T& scaler)
	{
		if (scaler == 0)
			return Vec2<T>();
		return Vec2<T>(x / scaler, y / scaler);
	}
	inline Vec2<T> operator/= (const T& scaler)
	{
		if (scaler == 0)
			return Vec2<T>();
		x /= scaler;
		y /= scaler;
		return *this;
	}
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
using Vec2d = Vec2<float>;
