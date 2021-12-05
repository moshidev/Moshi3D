/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COMPOSITION_H_
#define MOSHI3D_COMPOSITION_H_

#include "renderizable.h"
#include "composition_node.h"
#include "rooted_DAG.hpp"
#include <map>

class Composition : public Renderizable {
private:
    RootedDAG<CompositionNodeData> rooted_DAG;

public:
    typedef RootedDAG<CompositionNodeData>::iterator iterator;

    bool apply(iterator it, float time_point) const;

    void draw(const Renderer& r, float time_point) const;
    inline iterator get_root(void) const { return rooted_DAG.get_root(); }
    
    iterator emplace_child(const iterator& parent, const CompositionNodeData& node);
    iterator emplace_child(const iterator& parent, const Composition& node);
    void add_child_to_parent(const iterator& parent, const iterator& child);
};

#endif /* MOSHI3D_COMPOSITION_H_ */