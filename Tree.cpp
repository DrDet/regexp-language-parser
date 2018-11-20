#include "Tree.h"
#include <utility>
#include <iostream>

Node::Node(std::string type) : type(std::move(type)) {}

void Node::append_child(std::unique_ptr<Node> node) {
    children.emplace_back(std::move(node));
}

void Node::print(size_t n) {
    using std::cout;
    using std::endl;
    std::string pad(2*n, ' ');
    cout << pad << type << endl;
    for (auto &it : children) {
        it.get()->print(n + 1);
    }
}

