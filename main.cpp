#include <iostream>
#include <queue>
#include <vector>

// Class Tree represents a tree constructed from a Prufer code
class Tree {
 public:
  // Constructor takes a Prufer code and constructs the tree
  Tree(const std::vector<int>& prufer_code) {
    int n = prufer_code.size() + 2;
    std::vector<int> degree(n, 1);
    for (int node : prufer_code) {
      degree[node]++;
    }

    // Priority queue to store leaves
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < n; ++i) {
      if (degree[i] == 1) {
        pq.push(i);
      }
    }

    edges_.reserve(n - 1);
    for (int node : prufer_code) {
      int leaf = pq.top();
      pq.pop();
      edges_.push_back({leaf, node});
      if (--degree[node] == 1) {
        pq.push(node);
      }
    }

    int u = pq.top();
    pq.pop();
    int v = pq.top();
    edges_.push_back({u, v});
  }

  // Method to print all edges of the tree
  void PrintEdges() const {
    for (const auto& edge : edges_) {
      std::cout << edge.first << " - " << edge.second << std::endl;
    }
  }

 private:
  std::vector<std::pair<int, int>> edges_; // Vector to store the edges of the tree

 public:
  // Method to print the bracket sequence of the tree
  void PrintBracketsSeq(int root) const {
    std::vector<std::vector<int>> adj(edges_.size() + 1);
    for (const auto& edge : edges_) {
      adj[edge.first].push_back(edge.second);
      adj[edge.second].push_back(edge.first);
    }

    std::string brackets;
    GenerateBrackets(root, -1, adj, brackets);

    std::cout << brackets << std::endl;
  }

 private:
  // Recursive method to generate the bracket sequence
  void GenerateBrackets(int node, int parent,
                        const std::vector<std::vector<int>>& adj,
                        std::string& brackets) const {
    brackets.push_back('(');
    for (int neighbor : adj[node]) {
      if (neighbor != parent) {
        GenerateBrackets(neighbor, node, adj, brackets);
      }
    }
    brackets.push_back(')');
  }
};

int main() {
  std::vector<int> prufer_code;
  int n;
  std::cout << "Enter the length of the Prufer code: ";
  std::cin >> n;
  prufer_code.resize(n);

  std::cout << "Enter the Prufer code: ";
  for (int i = 0; i < n; ++i) {
    std::cin >> prufer_code[i];
  }

  Tree tree(prufer_code);

  while (true) {
    std::cout << "Enter a command (edges, brackets, exit): ";
    std::string command;
    std::cin >> command;

    if (command == "edges") {
      tree.PrintEdges();
    } else if (command == "brackets") {
      int root;
      std::cout << "Enter root node: ";
      std::cin >> root;
      tree.PrintBracketsSeq(root);
    } else if (command == "exit") {
      break;
    } else {
      std::cout << "Unknown command. Please try again." << std::endl;
    }
  }
}