#pragma once

#include <cmath>
#include <functional>
#include <map>
#include <optional>
#include <queue>
#include <tuple>
#include <vector>

namespace caoc::algorithms
{
	template <typename Node>
	std::tuple<std::map<Node, double>, std::map<Node, std::optional<Node>>> findBestPath(const Node& start, std::function<std::vector<std::tuple<double, Node>>(Node)> neighbors)
	{
		using QueueType = std::tuple<double, Node>;

		std::priority_queue<QueueType, std::vector<QueueType>, std::greater<QueueType>> queue;

		std::map<Node, double> dist;
		std::map<Node, std::optional<Node>> prev;

		dist[start] = 0;
		prev[start] = std::nullopt;

		queue.push({0, start});

		while (!queue.empty())
		{
			auto [cost, pos] = queue.top();
			queue.pop();

			for (const auto& [newCost, newPos] : neighbors(pos))
			{
				auto curCost = dist.contains(newPos) ? dist[newPos] : INFINITY;
				if (cost + newCost < curCost)
				{
					prev[newPos] = pos;
					dist[newPos] = cost + newCost;
					queue.push({cost + newCost, newPos});
				}
			}
		}

		return {dist, prev};
	}

	template <typename Node>
	std::tuple<std::map<Node, double>, std::map<Node, std::optional<Node>>> findBestPath(const Node& start, const Node& end, std::function<std::vector<std::tuple<double, Node>>(Node)> neighbors)
	{
		using QueueType = std::tuple<double, Node>;

		std::priority_queue<QueueType, std::vector<QueueType>, std::greater<QueueType>> queue;

		std::map<Node, double> dist;
		std::map<Node, std::optional<Node>> prev;

		dist[start] = 0;
		prev[start] = std::nullopt;

		queue.push({0, start});

		while (!queue.empty())
		{
			auto [cost, pos] = queue.top();
			queue.pop();

      if (pos == end) break;

			for (const auto& [newCost, newPos] : neighbors(pos))
			{
				auto curCost = dist.contains(newPos) ? dist[newPos] : INFINITY;
				if (cost + newCost < curCost)
				{
					prev[newPos] = pos;
					dist[newPos] = cost + newCost;
					queue.push({cost + newCost, newPos});
				}
			}
		}

		return {dist, prev};
	}

	template <typename Node>
	std::tuple<std::map<Node, double>, std::map<Node, std::vector<Node>>> findBestPaths(const Node& start, std::function<std::vector<std::tuple<double, Node>>(Node)> neighbors)
	{
		using QueueType = std::tuple<double, Node>;

		std::priority_queue<QueueType, std::vector<QueueType>, std::greater<QueueType>> queue;

		std::map<Node, double> dist;
		std::map<Node, std::vector<Node>> prev;

		dist[start] = 0;
		prev[start] = {};

		queue.push({0, start});

		while (!queue.empty())
		{
			auto [cost, pos] = queue.top();
			queue.pop();

			for (const auto& [newCost, newPos] : neighbors(pos))
			{
				auto curCost = dist.contains(newPos) ? dist[newPos] : INFINITY;
				if (cost + newCost < curCost)
				{
					prev[newPos] = {pos};
					dist[newPos] = cost + newCost;
					queue.push({cost + newCost, newPos});
				}
				else if (cost + newCost == curCost)
				{
					prev[newPos].push_back(pos);
				}
			}
		}

		return {dist, prev};
	}

	template <typename Node>
	std::tuple<std::map<Node, double>, std::map<Node, std::vector<Node>>> findBestPaths(const Node& start, const Node& end, std::function<std::vector<std::tuple<double, Node>>(Node)> neighbors)
	{
		using QueueType = std::tuple<double, Node>;

		std::priority_queue<QueueType, std::vector<QueueType>, std::greater<QueueType>> queue;

		std::map<Node, double> dist;
		std::map<Node, std::vector<Node>> prev;

		dist[start] = 0;
		prev[start] = {};

		queue.push({0, start});

		while (!queue.empty())
		{
			auto [cost, pos] = queue.top();
			queue.pop();

      if (pos == end) break;

			for (const auto& [newCost, newPos] : neighbors(pos))
			{
				auto curCost = dist.contains(newPos) ? dist[newPos] : INFINITY;
				if (cost + newCost < curCost)
				{
					prev[newPos] = {pos};
					dist[newPos] = cost + newCost;
					queue.push({cost + newCost, newPos});
				}
				else if (cost + newCost == curCost)
				{
					prev[newPos].push_back(pos);
				}
			}
		}

		return {dist, prev};
	}
};  // namespace caoc::algorithms
