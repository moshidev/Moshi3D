#include "composition_node.h"

CompositionNode::Atributes::Atributes()
:position{Tupla3f{0,0,0}}, rotation{{0,Tupla3f{1,0,0}} , {0,Tupla3f{0,1,0}} , {0,Tupla3f{0,0,1}}}, scaling{{1,1,1}}
{   }

CompositionNode::Atributes::Atributes(const Atributes& a)
:position{a.position}, rotation{a.rotation[0], a.rotation[1], a.rotation[2]}, scaling{a.scaling}
{

}

void CompositionNode::Atributes::apply(void) const {
    scaling.apply();
    position.apply();
    for (int i = 0; i < 3; i++) {
        rotation[i].apply();
    }
}