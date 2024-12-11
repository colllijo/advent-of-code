#pragma once

#include <cmath>
#include <compare>
#include <concepts>
#include <cstdio>
#include <functional>

template <typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

namespace caoc::structs
{
	template <arithmetic T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(T x, T y);

		T x() const;
		void setX(T x);

		T y() const;
		void setY(T y);

		T magnitude() const;
		void setMagnitude(T magnitude);

		double direction() const;
		void setDirection(double direction);

		Vector2<T> normal() const;
		Vector2<T>& normalize();

		Vector2<T> operator+(const Vector2<T>& other) const;
		Vector2<T> operator-(const Vector2<T>& other) const;
		Vector2<T> operator*(T scalar) const;

		Vector2<T>& operator+=(const Vector2<T>& other);
		Vector2<T>& operator-=(const Vector2<T>& other);
		Vector2<T>& operator*=(T scalar);

		bool operator==(const Vector2<T>& other) const;
		bool operator!=(const Vector2<T>& other) const;
		std::strong_ordering operator<=>(const Vector2<T>& other) const;

		T operator*(const Vector2<T>& other) const;

	private:
		T m_x;
		T m_y;

		T m_magnitude;
		double m_direction;
	};

	template <arithmetic T>
	Vector2<T>::Vector2() : m_x(0), m_y(0), m_magnitude(0), m_direction(0)
	{
	}

	template <arithmetic T>
	Vector2<T>::Vector2(T x, T y) : m_x(x), m_y(y)
	{
		if (x == 0 && y == 0)
		{
			m_magnitude = 0;
			m_direction = 0;
		}
		else
		{
			m_magnitude = std::sqrt(x * x + y * y);
			m_direction = std::atan2(y, x);
		}
	}

	template <arithmetic T>
	T Vector2<T>::x() const
	{
		return m_x;
	}

	template <arithmetic T>
	void Vector2<T>::setX(T x)
	{
		m_x = x;

		if (m_y == 0 && x == 0)
		{
			m_magnitude = 0;
			m_direction = 0;
		}
		else
		{
			m_magnitude = std::sqrt(x * x + m_y * m_y);
			m_direction = std::atan2(m_y, x);
		}
	}

	template <arithmetic T>
	T Vector2<T>::y() const
	{
		return m_y;
	}

	template <arithmetic T>
	void Vector2<T>::setY(T y)
	{
		m_y = y;

		if (m_x == 0 && y == 0)
		{
			m_magnitude = 0;
			m_direction = 0;
		}
		else
		{
			m_magnitude = std::sqrt(m_x * m_x + y * y);
			m_direction = std::atan2(y, m_x);
		}
	}

	template <arithmetic T>
	T Vector2<T>::magnitude() const
	{
		return m_magnitude;
	}

	template <arithmetic T>
	void Vector2<T>::setMagnitude(T magnitude)
	{
		m_magnitude = magnitude;
		m_x = m_magnitude * std::cos(m_direction);
		m_y = m_magnitude * std::sin(m_direction);
	}

	template <arithmetic T>
	double Vector2<T>::direction() const
	{
		return m_direction;
	}

	template <arithmetic T>
	void Vector2<T>::setDirection(double direction)
	{
		m_direction = direction;
		m_x = m_magnitude * std::cos(m_direction);
		m_y = m_magnitude * std::sin(m_direction);
	}

	template <arithmetic T>
	Vector2<T> Vector2<T>::normal() const
	{
		return Vector2<T>(m_x / m_magnitude, m_y / m_magnitude);
	}

	template <arithmetic T>
	Vector2<T>& Vector2<T>::normalize()
	{
		m_x /= m_magnitude;
		m_y /= m_magnitude;
		m_magnitude = 1;
		return *this;
	}

	template <arithmetic T>
	Vector2<T> Vector2<T>::operator+(const Vector2<T>& other) const
	{
		return Vector2<T>(m_x + other.x(), m_y + other.y());
	}

	template <arithmetic T>
	Vector2<T> Vector2<T>::operator-(const Vector2<T>& other) const
	{
		return Vector2<T>(m_x - other.x(), m_y - other.y());
	}

	template <arithmetic T>
	Vector2<T> Vector2<T>::operator*(T scalar) const
	{
		return Vector2<T>(m_x * scalar, m_y * scalar);
	}

	template <arithmetic T>
	Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& other)
	{
		setX(m_x + other.x());
		setY(m_y + other.y());

		return *this;
	}

	template <arithmetic T>
	Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& other)
	{
		setX(m_x - other.x());
		setY(m_y - other.y());

		return *this;
	}

	template <arithmetic T>
	Vector2<T>& Vector2<T>::operator*=(T scalar)
	{
		setMagnitude(m_magnitude * scalar);

		return *this;
	}

	template <arithmetic T>
	bool Vector2<T>::operator==(const Vector2<T>& other) const
	{
		return m_x == other.x() && m_y == other.y();
	}

	template <arithmetic T>
	bool Vector2<T>::operator!=(const Vector2<T>& other) const
	{
		return m_x != other.x() || m_y != other.y();
	}

	template <arithmetic T>
	std::strong_ordering Vector2<T>::operator<=>(const Vector2<T>& other) const
	{
		if (auto cmp = m_magnitude <=> other.m_magnitude; cmp != 0)
			return cmp;

		auto direction_cmp = m_direction <=> other.m_direction;
		if (direction_cmp == std::partial_ordering::less)
			return std::strong_ordering::less;
		if (direction_cmp == std::partial_ordering::greater)
			return std::strong_ordering::greater;
		return std::strong_ordering::equal;
	}

	template <arithmetic T>
	T Vector2<T>::operator*(const Vector2<T>& other) const
	{
		return m_x * other.x() + m_y * other.y();
	}

};  // namespace caoc::structs

// Extend the std namespace to allow standard functions to work with Vector2
namespace std
{
	template <arithmetic T>
	struct hash<caoc::structs::Vector2<T>>
	{
		size_t operator()(const caoc::structs::Vector2<T>& v) const
		{
			return (hash<T>()(v.magnitude()) ^ (hash<double>()(v.direction()) << 1));
		}
	};
}  // namespace std
