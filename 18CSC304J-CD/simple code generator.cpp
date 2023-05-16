#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

// Node structure to represent a DAG node
struct Node {
    int id;
    std::string label;

    Node(int nodeId, const std::string& nodeLabel) : id(nodeId), label(nodeLabel) {}
};

// DAG class to manage the graph
class DAG {
private:
    std::vector<Node> nodes;                             // Vector to store the nodes
    std::unordered_map<std::string, int> labelToNodeId;   // Map to store node labels and their corresponding IDs

public:
    // Function to add a node to the DAG
    int addNode(const std::string& label) {
        int nodeId = nodes.size();
        nodes.emplace_back(nodeId, label);
        labelToNodeId[label] = nodeId;
        return nodeId;
    }

    // Function to get the ID of a node by its label
    int getNodeId(const std::string& label) {
        if (labelToNodeId.count(label)) {
            return labelToNodeId[label];
        }
        return -1;
    }

    // Function to print the DAG
    void printDAG() {
        std::cout << "DAG:\n";
        for (const Node& node : nodes) {
            std::cout << "Node ID: " << node.id << ", Label: " << node.label << std::endl;
        }
    }
};

int main() {
    DAG dag;

    std::vector<std::string> labels;
    std::string label;

    std::cout << "Enter node labels (type 'end' to finish):\n";
    while (true) {
        std::getline(std::cin, label);
        if (label == "end") {
            break;
        }
        labels.push_back(label);
    }

    for (const std::string& label : labels) {
        dag.addNode(label);
    }

    std::string searchLabel;
    std::cout << "Enter a label to search its ID: ";
    std::getline(std::cin, searchLabel);

    int nodeId = dag.getNodeId(searchLabel);
    if (nodeId != -1) {
        std::cout << "Node ID: " << nodeId << std::endl;
    } else {
        std::cout << "Node not found!" << std::endl;
    }

    dag.printDAG();

    return 0;
}
