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
    Rotation::apply(l.rotation, l.position);
    Scaling::apply(l.scaling);
}

void CompositionNode::draw(const Renderer& r) const {
    Transformation::push_matrix();
    apply_location(this->location);
    animation.apply();
    for (const auto& c : childs) {
        Transformation::push_matrix();
        apply_location(c.first);
        c.second->draw(r);
        Transformation::pop_matrix();
    }
    for (const auto& obj : objects) {
        Transformation::push_matrix();
        apply_location(obj.loc);
        if (obj.light) {
            obj.light->apply();
        }
        if (obj.renderizable) {
            obj.renderizable->draw(r);
        }
        Transformation::pop_matrix();
    }
    Transformation::pop_matrix();
}

void CompositionNode::apply_lights(void) const {
    Transformation::push_matrix();
    apply_location(this->location);
    animation.apply();
    for (const auto& c : childs) {
        Transformation::push_matrix();
        apply_location(c.first);
        c.second->apply_lights();
        Transformation::pop_matrix();
    }
    for (const auto& obj : objects) {
        Transformation::push_matrix();
        apply_location(obj.loc);
        if (obj.light) {
            obj.light->apply();
        }
        Transformation::pop_matrix();
    }
    Transformation::pop_matrix();
}

void CompositionNode::execute_preorder(const std::function<void(CompositionNode&)>& f) {
    for (const auto& c : childs) {
        c.second->execute_preorder(f);
    }
    f(*this);
}