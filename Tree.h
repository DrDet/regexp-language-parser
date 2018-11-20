#pragma once
#include <memory>
#include <list>

class Node {
public:
    explicit Node(std::string type);
    Node(const Node & other) = delete;
    void append_child(std::unique_ptr<Node> node);
    void print(size_t = 1);
private:
    std::list<std::unique_ptr<Node>> children;
    std::string type;
};