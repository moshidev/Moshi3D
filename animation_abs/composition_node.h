/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COMPOSITION_NODE_H_
#define MOSHI3D_COMPOSITION_NODE_H_

#include "renderizable.h"
#include "tuplasg.h"
#include <memory>
#include <list>

class CompositionNode : public Renderizable {
public:
    struct Location {
        Tupla3f position;
        Tupla3f rotation;
        Tupla3f scaling;
        Location(const Location& l)
        : position{l.position}, rotation{l.rotation}, scaling{l.scaling}
        {    }
        Location(const Tupla3f& position={0,0,0}, const Tupla3f& rotation={0,0,0}, const Tupla3f& scaling={1,1,1})
        : position{position}, rotation{rotation}, scaling{scaling}
        {   }
    };

    struct Object {
        Location loc;
        std::shared_ptr<Renderizable> renderizable;
        Object(const Object& obj)
        : loc{obj.loc}, renderizable{obj.renderizable}
        {   }
        Object(const std::shared_ptr<Renderizable>& r)
        : renderizable{r}
        {   }
        Object(const Location& loc, const std::shared_ptr<Renderizable>& r)
        : loc{loc}, renderizable{r}
        {   }
    };

private:
    typedef std::list<std::pair<Location,std::shared_ptr<CompositionNode>>> node_container_t;
    typedef std::list<Object> obj_container_t;
    node_container_t childs;
    obj_container_t objects;
    Location location;

    void apply_location(const Location& l) const;

public:
    typedef node_container_t::iterator iterator;
    typedef obj_container_t::iterator obj_iterator;

    CompositionNode();
    CompositionNode(const Object& obj);
    CompositionNode(const CompositionNode& n) = default;
    CompositionNode(CompositionNode&& n);

    inline iterator add_child(const std::shared_ptr<CompositionNode>& c) { return childs.insert(childs.begin(), {{}, c}); }
    inline iterator add_child(const Location& loc, const std::shared_ptr<CompositionNode>& c) { return childs.insert(childs.begin(), {loc, c}); }
    inline obj_iterator add_obj(const Object& obj) { return objects.insert(objects.begin(), obj); }

    void draw(const Renderer& r) const;
};

#endif /* MOSHI3D_COMPOSITION_NODE_H_ */