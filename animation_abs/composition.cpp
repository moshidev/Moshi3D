#include "composition.h"
#include <queue>
#include <stack>

bool Composition::apply(iterator it, float time_point) const {
    bool visible = true;
    std::stack<Composition::iterator> stack;
    stack.push(it);
    auto it_parent = it.get_last_parent();
    while (it_parent != rooted_DAG.end()) {
        stack.push(it_parent);
        it_parent = it_parent.get_last_parent();
    }
    float init_time = 0;
    while (visible && !stack.empty()) {
        auto& it = stack.top();
        const auto& atributes = (*it).atributes;
        const auto& animation = (*it).animation;

        init_time = std::max(init_time, atributes.init_time);
        visible = atributes.is_visible(time_point);
        if (visible) {
            atributes.location.apply();

            float local_time_point = time_point;
            if (atributes.loop) {
                local_time_point = fmod(local_time_point+init_time, atributes.duration);
            }
            animation.apply(local_time_point);
        }
        stack.pop();
    }
    return visible;
}

void Composition::draw(const Renderer& r, float time_point) const {
    std::cout << "tp: " << time_point << std::endl;
    auto it = rooted_DAG.begin();
    while (it != rooted_DAG.end()) {
        for (const auto& obj : (*it).get_objects()) {
            Transformation::push_matrix();
            if (apply(it, time_point)) {
                obj.atributes.location.apply();
                obj.renderizable_ptr->draw(r);
            }
            Transformation::pop_matrix();
        }
        ++it;
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