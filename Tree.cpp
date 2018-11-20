#include "Tree.h"
#include <utility>
#include <iostream>
#include <queue>
#include <sstream>

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

std::string Node::to_dot() {
    string res;
    res += "digraph G {\n";
    res += to_dot_impl();
    res += "}";
    return res;
}

std::string Node::to_dot_impl() {
    static int id = 0;
    std::stringstream ss;
    int v_id = id++;
    string color = (children.empty() ? "; color = red" : "");
    ss << "\t" << v_id << " [label = \"" << type << "\"" << color << "];\n";
    for (auto &c: children) {
        int c_id = id;
        ss << c->to_dot_impl();
        ss << "\t" << v_id << " -> " << c_id << ";\n";
    }
    return ss.str();
}


