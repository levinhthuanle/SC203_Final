#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class RandomGraphGenerator {
public:
    vector<vector<int>> adj_matrix;
    vector<int> node_values;
    long int num_vertices;
    long int num_edges;

public:
    RandomGraphGenerator(long int v, long int e) :
        num_vertices(v),
        num_edges(e),
        adj_matrix(v, vector<int>(v, 0)),
        node_values(v, 0) {}

    RandomGraphGenerator() :
        num_vertices(0),
        num_edges(0) {}

    int randomNumber(int a, int b) {
        static random_device rd;
        static mt19937 generator(rd());
        uniform_int_distribution<int> distribution(a, b);
        return distribution(generator);
    }

    bool readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file " << filename << endl;
            return false;
        }

        string line;
        getline(file, line); // Skip the first line
        getline(file, line);
        stringstream ss_edges(line.substr(line.find(":") + 2));
        ss_edges >> num_edges;

        getline(file, line);
        stringstream ss_vertices(line.substr(line.find(":") + 2));
        ss_vertices >> num_vertices;

        getline(file, line); // Skip the adjacency matrix header

        adj_matrix.resize(num_vertices, vector<int>(num_vertices, 0));
        node_values.resize(num_vertices, 0);

        for (long int i = 0; i < num_vertices; ++i) {
            getline(file, line);
            stringstream ss(line);
            for (long int j = 0; j < num_vertices; ++j) {
                ss >> adj_matrix[i][j];
            }
        }

        getline(file, line); // Skip the node values header

        stringstream ss_node_values(line.substr(line.find(":") + 2));
        for (long int i = 0; i < num_vertices; ++i) {
            ss_node_values >> node_values[i];
        }

        file.close();
        return true;
    }

    void generateGraph() {
        if (num_edges > max_possible_edges()) {
            cerr << "Error: Number of edges exceeds the maximum possible for the given number of vertices." << endl;
            return;
        }

        random_device rd;
        mt19937 generator(rd());
        uniform_int_distribution<int> distribution(0, num_vertices - 1);

        long int edges_added = 0;
        while (edges_added < num_edges) {
            int node1 = distribution(generator);
            int node2 = distribution(generator);

            // Ensure no self-loops or duplicate edges
            if (node1 != node2 && adj_matrix[node1][node2] == 0) {
                int temp = randomNumber(1, 100);
                while (temp == 0)
                    temp = randomNumber(1, 100);

                adj_matrix[node1][node2] = temp;
                adj_matrix[node2][node1] = temp;
                edges_added++;
            }
        }

        // Generate random node values (modify as needed)
        for (int i = 0; i < num_vertices; ++i) {
            node_values[i] = randomNumber(0, num_vertices - 1); // Example: Random values between 0 and v-1
        }
    }

    void printGraph() const {
        cout << "Number of edges: " << num_edges << endl;
        cout << "Number of vertices: " << num_vertices << endl;
        cout << "Adjacency Matrix:\n";
        for (const auto& row : adj_matrix) {
            for (const auto& val : row) {
                cout << val << " ";
            }
            cout << endl;
        }

        cout << "Node Values:\n";
        for (const auto& val : node_values) {
            cout << val << " ";
        }
        cout << endl;
    }

    void saveToFile(const string& title, const string& path) const {
        ofstream fout(path);
        if (!fout.is_open()) {
            cerr << "Cannot open output file!" << endl;
            return;
        }

        fout << title << endl;
        fout << "Edges: " << num_edges << endl;
        fout << "Vertices: " << num_vertices << endl;
        fout << "Adjacency Matrix:\n";
        for (const auto& row : adj_matrix) {
            for (const auto& val : row) {
                fout << val << " ";
            }
            fout << endl;
        }

        fout << "Node Values:\n";
        for (const auto& val : node_values) {
            fout << val << " ";
        }
        fout << endl;

        cout << "Success!" << endl;
    }

    long int get_num_vertices() const {
        return num_vertices;
    }

    long int get_num_edges() const {
        return num_edges;
    }

private:
    long long max_possible_edges() const {
        return static_cast<long long>(num_vertices) * (num_vertices - 1) / 2;
    }
};
