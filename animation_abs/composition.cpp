#include "composition.h"
#include <queue>

void Composition::draw(const Renderer& r) const {
    auto it = rooted_DAG.begin();
    while (it != rooted_DAG.end()) {
        auto parent = it;
        auto child = it;
        while (parent != rooted_DAG.end()) {
            const auto& v {(*parent).child_atributes};
            auto atributes_it = std::find(v.begin(), v.end(), child);
            (*child).node_data.get_atributes(); //<--- nos falta un ".apply" o algo parecido;
            //aquí tendríamos que manejar de algua forma el "si es o no visible", si está en loop o no...
        }
    }
}

Composition::iterator Composition::emplace_child(const iterator& parent, const CompositionNodeData& node) {
    CompositionNode fnode{node};
    rooted_DAG.make_child(parent, fnode);
}

Composition::iterator Composition::emplace_child(const iterator& parent, const Composition& node) {
    std::queue<Composition::iterator> queue;    // Debería ser responsabilidad de rooted_DAG
    queue.emplace(node.get_root());
    if (node.get_root() != node.rooted_DAG.end()) {
        rooted_DAG.make_child(parent, *queue.front());
    }
    while (!queue.empty()) {
        auto wparent = queue.front();
        auto rbrother = parent.get_first_child();
        while (rbrother != node.rooted_DAG.end()) {
            queue.emplace(rbrother);
            rooted_DAG.make_child(wparent, *rbrother);
        }
        queue.pop();
    }
}

void Composition::add_child_to_parent(const iterator& parent, const iterator& child) {
    rooted_DAG.add_child(parent, child);
}