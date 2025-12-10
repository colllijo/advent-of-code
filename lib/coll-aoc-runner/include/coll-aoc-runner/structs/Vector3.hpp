#pragma once

#include <cmath>
#include <compare>
#include <concepts>
#include <cstdio>
#include <cstdlib>

namespace caoc::structs
{
	template <typename T>
	concept arithmetic = std::integral<T> or std::floating_point<T>;

	template <arithmetic T> class Vector3
	{
	public:
		Vector3();
		Vector3(T x, T y, T z);

		T x() const;
		void setX(T x);

		T y() const;
		void setY(T y);

		T z() const;
		void setZ(T y);

		T length() const;

		Vector3<T> normal() const;
		Vector3<T> &normalize();

		T distance(const Vector3<T> &other) const;

		Vector3<T> operator+(const Vector3<T> &other) const;
		Vector3<T> operator-(const Vector3<T> &other) const;
		Vector3<T> operator*(T scalar) const;

		Vector3<T> &operator+=(const Vector3<T> &other);
		Vector3<T> &operator-=(const Vector3<T> &other);
		Vector3<T> &operator*=(T scalar);

		bool operator==(const Vector3<T> &other) const;
		bool operator!=(const Vector3<T> &other) const;
		std::strong_ordering operator<=>(const Vector3<T> &other) const;

		T operator*(const Vector3<T> &other) const;

	private:
		T m_x;
		T m_y;
		T m_z;
	};

	template <arithmetic T> Vector3<T>::Vector3() : m_x(0), m_y(0), m_z(0) {}

	template <arithmetic T> Vector3<T>::Vector3(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}

	template <arithmetic T> T Vector3<T>::x() const
	{
		return m_x;
	}

	template <arithmetic T> void Vector3<T>::setX(T x)
	{
		m_x = x;
	}

	template <arithmetic T> T Vector3<T>::y() const
	{
		return m_y;
	}

	template <arithmetic T> void Vector3<T>::setY(T y)
	{
		m_y = y;
	}

	template <arithmetic T> T Vector3<T>::z() const
	{
		return m_z;
	}

	template <arithmetic T> void Vector3<T>::setZ(T z)
	{
		m_z = z;
	}

	template <arithmetic T> T Vector3<T>::length() const
	{
		if (m_x == 0 && m_y == 0 && m_z) return 0;

		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	template <arithmetic T> Vector3<T> Vector3<T>::normal() const
	{
		T length = this->length();

		return Vector3<T>(m_x / length, m_y / length, m_z / length);
	}

	template <arithmetic T> Vector3<T> &Vector3<T>::normalize()
	{
		T length = this->length();

		m_x /= length;
		m_y /= length;
		m_z /= length;

		return *this;
	}

	template <arithmetic T> T Vector3<T>::distance(const Vector3<T> &other) const
	{
		T diff = (other - *this).length();

		if (diff < 0) return -diff;
		return diff;
	}

	template <arithmetic T> Vector3<T> Vector3<T>::operator+(const Vector3<T> &other) const
	{
		return Vector3<T>(m_x + other.x(), m_y + other.y(), m_z + other.z());
	}

	template <arithmetic T> Vector3<T> Vector3<T>::operator-(const Vector3<T> &other) const
	{
		return Vector3<T>(m_x - other.x(), m_y - other.y(), m_z - other.z());
	}

	template <arithmetic T> Vector3<T> Vector3<T>::operator*(T scalar) const
	{
		return Vector3<T>(m_x * scalar, m_y * scalar, m_z * scalar);
	}

	template <arithmetic T> Vector3<T> &Vector3<T>::operator+=(const Vector3<T> &other)
	{
		setX(m_x + other.x());
		setY(m_y + other.y());
		setZ(m_z + other.z());

		return *this;
	}

	template <arithmetic T> Vector3<T> &Vector3<T>::operator-=(const Vector3<T> &other)
	{
		setX(m_x - other.x());
		setY(m_y - other.y());
		setZ(m_z - other.z());

		return *this;
	}

	template <arithmetic T> Vector3<T> &Vector3<T>::operator*=(T scalar)
	{
		setX(m_x * scalar);
		setY(m_y * scalar);
		setZ(m_z * scalar);

		return *this;
	}

	template <arithmetic T> bool Vector3<T>::operator==(const Vector3<T> &other) const
	{
		return m_x == other.x() && m_y == other.y() && m_z == other.z();
	}

	template <arithmetic T> bool Vector3<T>::operator!=(const Vector3<T> &other) const
	{
		return m_x != other.x() || m_y != other.y() || m_z != other.z();
	}

	template <arithmetic T> std::strong_ordering Vector3<T>::operator<=>(const Vector3<T> &other) const
	{
		if (auto cmp = length() <=> other.length(); cmp != 0) return cmp;
	}

	template <arithmetic T> T Vector3<T>::operator*(const Vector3<T> &other) const
	{
		return m_x * other.x() + m_y * other.y() + m_z * other.z();
	}
}; // namespace caoc::structs
