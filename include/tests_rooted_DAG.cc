#include <iostream>
#include <string>
#include "rooted_DAG.hpp"

int main() {
    RootedDAG<std::string> copypasta{std::string("u so warm")};
    auto a = copypasta.begin();
    auto b = copypasta.make_child(a, std::string("pounces "));
    auto e = copypasta.make_child(b, std::string("x3 "));
    auto f = copypasta.make_child(b, std::string("nuzzles "));
    auto c = copypasta.make_child(a, std::string("u "));
    auto g = copypasta.make_child(c, std::string("on "));
    auto d = copypasta.make_child(a, std::string("uwu "));
    copypasta.add_child(d, e);
    copypasta.add_child(a, f);
    copypasta.erase_leaf(g);

    std::cout << *copypasta.get_root();

    auto it = copypasta.begin();
    while (it != copypasta.end()) {
        std::cout << *it++;
    }
    std::cout << std::endl;

    return 0;
}