#include "Tree.h"
#include <utility>
#include <iostream>
#include <queue>

using std::string;
using std::queue;

Node::Node(std::string type) : type(std::move(type)) {}

void Node::append_child(node_t node) {
    children.emplace_back(std::move(node));
}

string Node::to_string() {
    string res(type);
    for (auto &it : children) {
        res += it->to_string();
    }
    return res;
}

//void Node::print(size_t n) {
//    using std::cout;
//    using std::endl;
//    std::string pad(2*n, ' ');
//    cout << pad << type << endl;
//    for (auto &it : children) {
//        it.get()->print(n + 1);
//    }
//}

