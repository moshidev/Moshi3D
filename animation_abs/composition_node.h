/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COMPOSITION_NODE_H_
#define MOSHI3D_COMPOSITION_NODE_H_

#include "animation.h"
#include "renderizable.h"
#include "point_rotation.h"
#include "rotation.h"
#include "scaling.h"
#include "translation.h"
#include "tuplasg.h"
#include <memory>
#include <string>
#include <list>

class CompositionNode {
public:
    struct Atributes {
        std::string name;
        Translation position;
        Rotation rotation[3];
        Scaling scaling;

        Atributes();
        Atributes(const Atributes& a);
        void apply(void) const;
    };

    struct Object {
        std::shared_ptr<Renderizable> renderizable_ptr;
        Atributes atributes;
    };

private:
    typedef std::list<Object> obj_container_t;
    obj_container_t objects;
    Atributes atributes;
    Animation animation;

public:
    typedef obj_container_t::iterator iterator;
    typedef obj_container_t::const_iterator const_iterator;

    CompositionNode() {     }
    CompositionNode(const CompositionNode& c)
    :objects{c.objects}, atributes{c.atributes}, animation{c.animation}
    {   }

    inline iterator begin_objects(void) { return objects.begin(); }
    inline iterator end_objects(void) { return objects.end(); }
    inline const_iterator begin_objects(void) const { return objects.begin(); }
    inline const_iterator end_objects(void) const { return objects.end(); }
    inline void erase_object(const iterator& it) { objects.erase(it); }
    inline void add_object(const Object& obj) { objects.emplace_back(obj); }
    inline void add_object(Object&& obj) { objects.emplace_back(obj); }

    inline Atributes& get_atributes(void) { return atributes; }
    inline Animation& get_animation(void) { return animation; }
};

#endif /* MOSHI3D_COMPOSITION_NODE_H_ */