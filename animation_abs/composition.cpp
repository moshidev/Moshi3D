#include "composition.h"
#include <queue>
#include <stack>

void Composition::draw_node(const RootedDAG<CompositionNode>::iterator& it, const Renderer& r) const {
    for (auto& obj : (*it).get_objects()) {
        obj.renderizable_ptr->draw(r);
    }
}

void Composition::draw(const Renderer& r) const {
    const auto end = rooted_DAG.end();
    auto it = rooted_DAG.get_root();
    while (it != end) {
        auto child = it;
        while (child != end) {
            Transformation::push_matrix();
            (*child).apply();
            draw_node(child, r);
            it = child;
            child = it.get_first_child();
        }

        auto rbrother = it.get_rbrother();
        while (it != end && rbrother == end) {
            Transformation::pop_matrix();
            it = it.get_last_parent();
            rbrother = it.get_rbrother();
        }
        Transformation::pop_matrix();
        it = rbrother;
    }
}

Composition::iterator Composition::emplace_child(const iterator& parent, const CompositionNode& node) {
    return rooted_DAG.make_child(parent, node);
}

Composition::iterator Composition::emplace_child(const iterator& parent, const Composition& node) {
    std::queue<Composition::iterator> queue;    // Debería ser responsabilidad de rooted_DAG
    queue.emplace(node.get_root());

    iterator ret_it = rooted_DAG.make_child(parent, *queue.front());
    while (!queue.empty()) {
        auto wparent = queue.front();
        auto rbrother = parent.get_first_child();
        while (rbrother != node.rooted_DAG.end()) {
            queue.emplace(rbrother);
            rooted_DAG.make_child(wparent, *rbrother);
        }
        queue.pop();
    }
    return ret_it;
}

void Composition::add_child_to_parent(const iterator& parent, const iterator& child) {
    rooted_DAG.add_child(parent, child);
}