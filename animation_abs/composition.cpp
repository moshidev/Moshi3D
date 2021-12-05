#include "composition.h"
#include <queue>

bool Composition::apply(iterator it, float time_point) const {
    bool visible = true;
    while (visible && it != rooted_DAG.end()) {
        auto it_parent = it.get_last_parent();
        const auto& atributes = (*it).atributes;
        const auto& animation = (*it).animation;
        visible = atributes.is_visible(time_point);
        if (visible) {
            atributes.location.apply();

            float local_time_point = time_point;
            if (atributes.loop) {
                local_time_point = fmod(local_time_point+atributes.init_time, atributes.duration);
            }
            animation.apply(local_time_point);
        }
        it = it_parent;
    }
    return visible;
}

void Composition::draw(const Renderer& r, float time_point) const {
    std::cout << "tp: " << time_point << std::endl;
    auto it = rooted_DAG.begin();
    while (it != rooted_DAG.end()) {
        const auto& obj_v {(*it).get_objects()};
        for (const auto& obj : obj_v) {
            Transformation::push_matrix();
            obj.atributes.location.apply();
            if (apply(it, time_point)) {
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

//<--- nos falta un ".apply" o algo parecido;
            //aquí tendríamos que manejar de algua forma el "si es o no visible", si está en loop o no...
            // hay que limitar la asignación de valores a tiempo inicio y tiempo de duración según en el ámbito
            // donde se modifiquen/pertenezcan los atributos
            // Algo así como una estructura de datos temporal que tenga constancia de cada nivel del árbol superior  para el nodo actual;