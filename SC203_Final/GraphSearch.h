#include <iostream>
#include <vector>
#include <algorithm>
#include "RandomGraphGenerator.h"

class GraphSearch {
public:
    const RandomGraphGenerator& graph;
    int num_nodes;

public:
    GraphSearch(const RandomGraphGenerator& graph) :
        graph(graph),
        num_nodes(graph.num_vertices) {}

    int dfid(int start_node, const std::vector<int>& target_values) {
        for (int depth_limit = 0; depth_limit < num_nodes; ++depth_limit) {
            std::vector<bool> visited(num_nodes, false);
            int result = depth_limited_search(start_node, target_values, depth_limit, visited);
            if (result != -1) {
                return result;
            }
        }
        return -1;
    }

private:
    int depth_limited_search(int current_node, const std::vector<int>& target_values,
        int depth_limit, std::vector<bool>& visited) {
        if (has_target_values(current_node, target_values)) {
            return current_node;
        }
        if (depth_limit == 0) {
            return -1;
        }

        visited[current_node] = true;

        for (int neighbor = 0; neighbor < num_nodes; ++neighbor) {
            if (graph.adj_matrix[current_node][neighbor] != 0 && !visited[neighbor]) {
                int result = depth_limited_search(neighbor, target_values, depth_limit - 1, visited);
                if (result != -1) {
                    return result;
                }
            }
        }

        return -1;
    }

    bool has_target_values(int node, const std::vector<int>& target_values) {
        return std::find(target_values.begin(), target_values.end(), graph.node_values[node]) != target_values.end();
    }
};
