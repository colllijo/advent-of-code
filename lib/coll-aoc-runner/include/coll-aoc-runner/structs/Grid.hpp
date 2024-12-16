#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "coll-aoc-runner/strings/Format.hpp"
#include "coll-aoc-runner/structs/Direction.hpp"
#include "coll-aoc-runner/structs/Vector2.hpp"

namespace caoc::structs
{
	template <typename T>
	class Grid
	{
	public:
		Grid();
		Grid(int width, int height);
		Grid(int width, int height, T defaultValue);
		Grid(std::vector<std::vector<T>>);
		Grid(const std::string& gridRepresentation, const std::function<T(char)>& transform = [](char c) { return c; });

		int width() const;
		int height() const;

		void set(int x, int y, T value);
		void set(Vector2<int> pos, T value);
		T get(int x, int y) const;
		T get(Vector2<int> pos) const;
		T move(int x, int y, Direction direction, int magnitude = 1) const;
		T move(Vector2<int> pos, Direction direction, int magnitude = 1) const;

		bool inBounds(int x, int y) const;
		bool inBounds(Vector2<int> pos) const;

		std::vector<T> row(int y) const;
		std::vector<std::vector<T>> rows() const;
		std::vector<T> column(int x) const;
		std::vector<std::vector<T>> columns() const;
		std::vector<std::vector<T>> dexterDiagonals() const;
		std::vector<std::vector<T>> sinisterDiagonals() const;
		std::vector<std::vector<T>> diagonals() const;

    void print() const;

		T& operator()(int x, int y);
		const T& operator()(int x, int y) const;

	private:
		int m_width;
		int m_height;

		std::vector<std::vector<T>> m_grid;
	};

	template <typename T>
	Grid<T>::Grid() : m_width(0), m_height(0)
	{
	}

	template <typename T>
	Grid<T>::Grid(int width, int height) : m_width(width), m_height(height), m_grid(height, std::vector<T>(width))
	{
	}

	template <typename T>
	Grid<T>::Grid(int width, int height, T defaultValue) : m_width(width), m_height(height), m_grid(height, std::vector<T>(width, defaultValue))
	{
	}

	template <typename T>
	Grid<T>::Grid(std::vector<std::vector<T>> grid) : m_width(grid[0].size()), m_height(grid.size()), m_grid(grid)
	{
	}

	template <typename T>
	Grid<T>::Grid(const std::string& gridRepresentation, const std::function<T(char)>& transform) : m_width(0), m_height(0)
	{
		for (const auto& row : caoc::strings::trim(gridRepresentation) | std::ranges::views::split('\n'))
		{
			m_grid.push_back(std::vector<T>());
			for (const auto& cell : row)
			{
				m_grid.back().push_back(transform(cell));
			}
			m_width = std::max(m_width, static_cast<int>(m_grid.back().size()));
		}
		m_height = m_grid.size();
	}

	template <typename T>
	void Grid<T>::set(int x, int y, T value)
	{
		if (y < 0 || y >= m_height || x < 0 || x >= m_width) throw std::out_of_range("Out of bounds");

		m_grid[y][x] = value;
	}

	template <typename T>
	void Grid<T>::set(Vector2<int> pos, T value)
	{
		set(pos.x(), pos.y(), value);
	}

	template <typename T>
	T Grid<T>::get(int x, int y) const
	{
		if (y < 0 || y >= m_height || x < 0 || x >= m_width) throw std::out_of_range("Out of bounds");

		return m_grid[y][x];
	}

	template <typename T>
	T Grid<T>::get(Vector2<int> pos) const
	{
		return get(pos.x(), pos.y());
	}

	template <typename T>
	T Grid<T>::move(int x, int y, Direction direction, int magnitude) const
	{
		auto scaled = direction.direction() * magnitude;

		int mX = x + scaled.x();
		int mY = y + scaled.y();

		if (mY < 0 || mY >= m_height || mX < 0 || mX >= m_width) throw std::out_of_range("Out of bounds");

		return m_grid[mY][mX];
	}

	template <typename T>
	T Grid<T>::move(Vector2<int> pos, Direction direction, int magnitude) const
	{
		return move(pos.x(), pos.y(), direction, magnitude);
	}

	template <typename T>
	bool Grid<T>::inBounds(int x, int y) const
	{
		return x >= 0 && x < m_width && y >= 0 && y < m_height;
	}

	template <typename T>
	bool Grid<T>::inBounds(Vector2<int> pos) const
	{
		return inBounds(pos.x(), pos.y());
	}

	template <typename T>
	int Grid<T>::width() const
	{
		return m_width;
	}

	template <typename T>
	int Grid<T>::height() const
	{
		return m_height;
	}

	template <typename T>
	std::vector<T> Grid<T>::row(int y) const
	{
		if (y < 0 || y >= m_height) throw std::out_of_range("Out of bounds");

		return m_grid[y];
	}

	template <typename T>
	std::vector<std::vector<T>> Grid<T>::rows() const
	{
		return m_grid;
	}

	template <typename T>
	std::vector<T> Grid<T>::column(int x) const
	{
		if (x < 0 || x >= m_width) throw std::out_of_range("Out of bounds");

		std::vector<T> column;
		for (int y = 0; y < m_height; y++)
		{
			column.push_back(m_grid[y][x]);
		}
		return column;
	}

	template <typename T>
	std::vector<std::vector<T>> Grid<T>::columns() const
	{
		std::vector<std::vector<T>> columns;
		for (int x = 0; x < m_width; x++)
		{
			columns.push_back(column(x));
		}

		return columns;
	}

	template <typename T>
	std::vector<std::vector<T>> Grid<T>::dexterDiagonals() const
	{
		std::vector<std::vector<T>> diagonals;
		for (int i = 0; i < m_height + m_width - 1; i++)
		{
			std::vector<T> diagonal;
			for (int j = 0; j <= i; j++)
			{
				int x = i - j;
				int y = j;
				if (x < m_width && y < m_height)
				{
					diagonal.push_back(m_grid[y][x]);
				}
			}
			diagonals.push_back(diagonal);
		}
		return diagonals;
	}

	template <typename T>
	std::vector<std::vector<T>> Grid<T>::sinisterDiagonals() const
	{
		std::vector<std::vector<T>> diagonals;
		for (int i = 0; i < m_height + m_width - 1; i++)
		{
			std::vector<T> diagonal;
			for (int j = 0; j <= i; j++)
			{
				int x = (m_width - 1) - (i - j);
				int y = j;
				if (x >= 0 && y < m_height)
				{
					diagonal.push_back(m_grid[y][x]);
				}
			}
			diagonals.push_back(diagonal);
		}
		return diagonals;
	}

	template <typename T>
	std::vector<std::vector<T>> Grid<T>::diagonals() const
	{
		auto dexter = dexterDiagonals();
		auto sinister = sinisterDiagonals();

		std::vector<std::vector<T>> diagonals;
		diagonals.insert(diagonals.end(), dexter.begin(), dexter.end());
		diagonals.insert(diagonals.end(), sinister.begin(), sinister.end());

		return diagonals;
	}

  template <typename T>
  void Grid<T>::print() const
  {
    for (const auto& row : m_grid)
    {
      for (const auto& cell : row)
      {
        std::cout << cell;
      }
      std::cout << "\n";
    }
  }

	template <typename T>
	T& Grid<T>::operator()(int x, int y)
	{
		if (y < 0 || y >= m_height || x < 0 || x >= m_width) throw std::out_of_range("Out of bounds");

		return m_grid[y][x];
	}

	template <typename T>
	const T& Grid<T>::operator()(int x, int y) const
	{
		if (y < 0 || y >= m_height || x < 0 || x >= m_width) throw std::out_of_range("Out of bounds");

		return m_grid[y][x];
	}
};  // namespace caoc::structs
