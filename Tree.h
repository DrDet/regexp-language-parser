#pragma once
#include <memory>
#include <list>

class Node;
using node_t = std::unique_ptr<Node>;

class Node {
public:
    explicit Node(std::string type);
    Node(const Node & other) = delete;
    void append_child(std::unique_ptr<Node> node);
    std::string to_string();
    std::string to_dot();
private:
    std::string to_dot_impl();
    std::list<std::unique_ptr<Node>> children;
    std::string type;
};