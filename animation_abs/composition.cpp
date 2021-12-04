#include "composition.h"

void Composition::draw_node(const Renderer& r, const iterator& it, float time_point) const {
    auto obj = (*it).begin_objects();
    while (obj != (*it).end_objects()) {
        auto p = it;
        Transformation::push_matrix();
        while (p != rooted_DAG.end()) {
            (*p).get_atributes().apply();
            (*p).get_animation().apply(time_point, true);
            p = p.get_last_parent();
        }
        (*obj).renderizable_ptr->draw(r);
        ++obj;
        Transformation::pop_matrix();
    }
}

void Composition::draw(const Renderer& r) const {
    auto it = rooted_DAG.begin();
    while (it != rooted_DAG.end()) {
        static float prueba = 0;
        prueba += 0.01;
        if (prueba > 10) {
            prueba = 0.01;
        }
        draw_node(r, it, prueba);
        ++it;
    }
}

Composition::iterator Composition::adquire_ownership(iterator& parent_it, Composition&& c) {
    return rooted_DAG.own_child(parent_it, std::move(c.rooted_DAG));
}

void Composition::add_child(iterator& parent_it, iterator& child_it) {
    rooted_DAG.add_child(parent_it, child_it);
}

void Composition::add_child(iterator& parent_it, const CompositionNode& c) {
    rooted_DAG.make_child(parent_it, c);
}