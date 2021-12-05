#include "composition_node.h"

void CompositionNode::Location::apply(void) const {
    Scaling::apply(scaling);
    Translation::apply(position);
    Rotation::apply(rotation_polar);
}