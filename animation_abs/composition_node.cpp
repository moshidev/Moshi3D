#include "composition_node.h"
#include "scaling.h"
#include "translation.h"
#include "rotation.h"

void CompositionNode::Location::apply(void) const {
    Scaling::apply(scaling);
    Translation::apply(position);
    Rotation::apply(rotation_polar);
}

void CompositionNode::apply(void) const {
    atributes.loc.apply();
}