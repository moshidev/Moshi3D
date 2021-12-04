/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COMPOSITION_H_
#define MOSHI3D_COMPOSITION_H_

#include "renderizable.h"
#include "composition_node.h"
#include "rooted_DAG.hpp"

class Composition : public Renderizable {
private:
    RootedDAG<CompositionNode> rooted_DAG;
public:
    typedef RootedDAG<CompositionNode>::iterator iterator;
    void draw_node(const Renderer& r, const iterator& it, float time_point) const;
    void draw(const Renderer& r) const;

    inline iterator begin(void) { return rooted_DAG.begin(); }
    inline iterator end(void) { return rooted_DAG.end(); }
    inline iterator get_root(void) { return rooted_DAG.get_root(); }

    iterator adquire_ownership(iterator& parent_it, Composition&& c);
    void add_child(iterator& parent_it, iterator& child_it);
    void add_child(iterator& parent_it, const CompositionNode& c);
};

#endif /* MOSHI3D_COMPOSITION_H_ */