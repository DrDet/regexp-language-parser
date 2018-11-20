#include <iostream>
#include <fstream>
#include "Parser.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3 || argv[1] != string("-v")) {
        cout << argc << " " << argv[1] << endl;
        cout << "Wrong input format. Usage:\n" << "main -v <regexp-string>" << endl;
        return 0;
    }
    ofstream out("___tmp.dv");
    Parser parser;
    out << parser.parse(argv[2])->to_dot();
    out.close();
    system("dot -Tps ___tmp.dv -o regexp-ast.ps");
    system("rm ___tmp.dv");
    system("evince regexp-ast.ps");
    return 0;
}