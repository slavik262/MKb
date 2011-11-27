#pragma once

#include <string>

#include "MKMath.h"

//! A two-dimensional vector using floats for each dimension
class Vector2
{
public:
	float X;
	float Y;

	//! Initializes vector to zero
	Vector2() : X(0.0f), Y(0.0f) {} 

	//! Initializes vector to provided x and y values
	Vector2(float x, float y) : X(x), Y(y) {}

	//! Initializes x and y values to v
	explicit Vector2(float v) : X(v), Y(v) {}

	//! Initializes vector with a provided vector's values
	Vector2(const Vector2& o) : X(o.X), Y(o.Y) {}

	//! Initializes vector with the first two values in the provided array
	explicit Vector2(float* arr) : X(arr[0]), Y(arr[1]) {}
	
	Vector2 operator-() const { return Vector2(-X, -Y); }
	
	Vector2& operator=(const Vector2& o)
		{ X = o.X; Y = o.Y; return *this; }

	Vector2 operator+(const Vector2& o) const
		{ return Vector2(X + o.X, Y + o.Y); }
	Vector2& operator +=(const Vector2& o)
		{ X += o.X; Y += o.Y; return *this; }
	Vector2 operator+(float v) const
		{ return Vector2(X + v, Y + v); }
	Vector2& operator+=(float v)
		{ X += v; Y += v; return *this; }

	Vector2 operator-(const Vector2& o) const
		{ return Vector2(X - o.X, Y - o.Y); }
	Vector2& operator -=(const Vector2& o)
		{ X -= o.X; Y -= o.Y; return *this; }
	Vector2 operator-(float v) const
		{ return Vector2(X - v, Y - v); }
	Vector2& operator-=(float v)
		{ X -= v; Y -= v; return *this; }

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y
	bool operator<=(const Vector2& o) const
	{
		return 	(X < o.X || Math::Equals(X, o.X)) ||
				(Math::Equals(X, o.X) && (Y < o.Y || Math::Equals(Y, o.Y))) ||
				(Math::Equals(X, o.X) && Math::Equals(Y, o.Y));
	}

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y
	bool operator>=(const Vector2& o) const
	{
		return 	(X > o.X || Math::Equals(X, o.X)) ||
				(Math::Equals(X, o.X) && (Y > o.Y || Math::Equals(Y, o.Y))) ||
				(Math::Equals(X, o.X) && Math::Equals(Y, o.Y));
	}

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y
	bool operator<(const Vector2& o) const
	{
		return 	(X < o.X && !Math::Equals(X, o.X)) ||
				(Math::Equals(X, o.X) && Y < o.Y && !Math::Equals(Y, o.Y)) ||
				(Math::Equals(X, o.X) && Math::Equals(Y, o.Y));
	}

	//! Comparison operators can be used to sort vectors with respect to X,
	//! then Y
	bool operator>(const Vector2& o) const
	{
		return 	(X > o.X && !Math::Equals(X, o.X)) ||
				(Math::Equals(X, o.X) && Y > o.Y && !Math::Equals(Y, o.Y)) ||
				(Math::Equals(X, o.X) && Math::Equals(Y, o.Y));
	}

	/*!
	\brief Checks equality using Math::kFloatRoundError as tolerance
	\see Math::kFloatRoundError
	*/
	bool operator==(const Vector2& o) const { return IsWithinTolerance(o); }
	/*!
	\brief Checks inequality using Math::kFloatRoundError as tolerance
	\see Math::kFloatRoundError
	*/
	bool operator!=(const Vector2& o) const { return !IsWithinTolerance(o); }

	/*
	\brief Checks if another vector is equal to this one within a
			provided tolerance
	\param o The other vector
	\param tolerance The tolerance allowed for each component of the
						two vectors to be within and still be considered equal
	\return True if this vector and o are equal within tolerance
	\see Math::kFloatRoundError
	*/
	bool IsWithinTolerance(const Vector2& o,
			float tolerance = Math::kFloatRoundError) const
	{
		return Math::Equals(X, o.X, tolerance)
			&& Math::Equals(Y, o.Y, tolerance);
	}

	//! Gets the length of this vector
	float GetLength() const { return std::sqrt(X*X + Y*Y); }

	//! Gets the length squared of this vector,
	//! which is faster to calculate than the length
	float GetLengthSq() const { return X*X + Y*Y; }

	//! Gets the distance from this vector to another one,
	//! interpreting both vectors as points
	float GetDistanceFrom(const Vector2& o) const
	{
		float dx, dy;
		dx = X - o.X;
		dy = Y - o.Y;
		return std::sqrt(dx*dx + dy*dy);
	}

	//! Gets the distance squared from this vector to another one,
	//! interpreting both vectors as points.
	//! This is faster to calculate than the distance itself.
	float GetDistanceSqFrom(const Vector2& o) const
	{
		float dx, dy;
		dx = X - o.X;
		dy = Y - o.Y;
		return dx*dx + dy*dy;
	}

	//! Returns true if this vector is a unit vector (with a length of 1)
	bool IsNormalized() const
		{ return Math::Equals(std::sqrt(X*X + Y*Y), 1.0f); }

	//! Copies this vector into the first two values of the provided array
	void GetAsArray(float* arr) const
	{
		arr[0] = X;
		arr[1] = Y;
	}

	//! Sets this vector to the provided values
	void Set(float x, float y, float z) { X = x; Y = y; }

	//! Sets this vector's values from the first two values of the
	//! provided array
	void SetFromArray(float* asArray)
		{ X = asArray[0]; Y = asArray[1]; }

	//! Set's vector's components to their mulitplicative inverses
	void SetToInverse() { X = 1.0f / X; Y = 1.0f / Y; }

	//! Gets an array with components (1/x, 1/y, 1/z) of this vector
	Vector2 GetInverse() const
		{ Vector2 ret(*this); ret.SetToInverse(); return ret; }

	//! Scales this vector by the components of the provided vector
	void Scale(const Vector2& o)
		{ X *= o.X; Y *= o.Y; }

	//! Returns a copy of this vector, scaled by the provided vector
	Vector2 GetScaledBy(const Vector2& o) const
		{ Vector2 ret(*this); ret.Scale(o); return ret; }

	//! Scales this vector by a provided scalar
	void Scale(float v)
		{ X *= v; Y *= v; }

	//! Returns a copy of this vector, scaled by the provided scalar
	Vector2 GetScaledBy(float v) const
		{ Vector2 ret(*this); ret.Scale(v); return ret; }

	//! Sets the length of this vector to 1
	void Normalize()
	{
		float len = std::sqrt(X*X + Y*Y);
		
		// Normalized already if our length is zero.
		// Also stops NaN errors
		if (Math::IsZero(len))
			return;

		X /= len;
		Y /= len;
	}

	//! Returns a copy of this vector with a length of 1
	Vector2 GetNormalized() const
		{ Vector2 ret(*this); ret.Normalize(); return ret; }

	//! Sets the length of this vector to a provided scalar
	void SetLength(float len)
	{
		Normalize();
		Scale(len);
	}

	//! Returns a copy of this vector with a length of the provided scalar
	Vector2 SetLength(float len) const
		{ Vector2 ret(*this); ret.SetLength(len); return ret; }

	/*!
	\brief Calculates the dot product of two vectors
	\param a The first vector in the dot product
	\param b The second vector in the dot product
	\return a dot b
	*/
	static float DotProduct(const Vector2& a, const Vector2& b)
	{
		return a.X * b.X + a.Y * b.Y;
	}

	//! Gets the left world vector (-1, 0, 0)
	static const Vector2& GetLeft()
	{
		static Vector2 left(-1.0f, 0.0f);
		return left;
	}

	//! Gets the right world vector, (1, 0, 0)
	static const Vector2& GetRight()
	{
		static Vector2 right(1.0f, 0.0f);
		return right;
	}

	//! Gets the up world vector, (0, 1, 0)
	static const Vector2& GetUp()
	{
		static Vector2 up(0.0f, 1.0f);
		return up;
	}

	//! Gets the down world vector, (0, -1, 0)
	static const Vector2& GetDown()
	{
		static Vector2 down(0.0f, -1.0f);
		return down;
	}

	//! Gets (0, 0)
	static const Vector2& GetZero()
	{
		static Vector2 zero(0.0f);
		return zero;
	}

	//! Gets (1, 1)
	static const Vector2& GetOne()
	{
		static Vector2 one(1.0f);
		return one;
	}
};
