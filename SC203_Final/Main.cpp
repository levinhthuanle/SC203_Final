#include "GraphSearch.h"
#include <chrono>

void testDepthFirstIterativeDeepening(RandomGraphGenerator& sampleGraph) {
    GraphSearch searcher(sampleGraph); // Pass the graph object
    std::vector<int> target_values = {3};
    int start_node = 0;
    int found_node = searcher.dfid(start_node, target_values);

    if (found_node != -1) {
        std::cout << "Node found at index: " << found_node << std::endl;
    }
    else {
        std::cout << "Node not found." << std::endl;
    }
}

void testDFID(RandomGraphGenerator& sampleGraph) {
    auto start = chrono::high_resolution_clock::now();
    cout << "Testing for Depth First Iterative Deepening Algorithm \n";
    testDepthFirstIterativeDeepening(sampleGraph);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;
    cout << "Time consume: " << duration.count() << "s\n";
}

void case1() {
    long int v = 7;
    long int e = 6;


    RandomGraphGenerator sampleGraph(v, e);
    //sampleGraph.generateGraph();

    //sampleGraph.saveToFile("Initial Test case!", "./Dataset/Testcase0.txt");

    string path = "./Dataset/Testcase8.txt";
    sampleGraph.readFromFile(path);
    sampleGraph.printGraph();


    //testDFID(sampleGraph);
}

int main() {
    case1();

    return 0;
}
