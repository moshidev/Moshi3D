#include "transformation.h"
#include "translation.h"
#include "rotation.h"
#include "scaling.h"
#include "composition_node.h"

CompositionNode::CompositionNode()
{    }

CompositionNode::CompositionNode(const Object& obj) {
    add_obj(obj);
}

CompositionNode::CompositionNode(CompositionNode&& n) {
    std::swap(childs, n.childs);
    std::swap(objects, n.objects);
}

void CompositionNode::apply_location(const Location& l) const {
    Translation::apply(l.position);
    Rotation::apply(l.rotation);
    Scaling::apply(l.scaling);
}

void CompositionNode::draw(const Renderer& r) const {
    Transformation::push_matrix();
    apply_location(this->location);
    for (const auto& c : childs) {
        Transformation::push_matrix();
        apply_location(c.first);
        c.second->draw(r);
        Transformation::pop_matrix();
    }
    for (const auto& obj : objects) {
        Transformation::push_matrix();
        apply_location(obj.loc);
        obj.renderizable->draw(r);
        Transformation::pop_matrix();
    }
    Transformation::pop_matrix();
}
