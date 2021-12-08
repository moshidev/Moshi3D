/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COMPOSITION_NODE_H_
#define MOSHI3D_COMPOSITION_NODE_H_

#include "renderizable.h"
#include "tuplasg.h"
#include <memory>
#include <string>
#include <vector>

class CompositionNode {
public:
    struct Location {
        Tupla3f scaling {1,1,1};
        Tupla3f position {0,0,0};
        Tupla2f rotation_polar {0,0};
        
        void apply(void) const;
    };

    struct Atributes {
        std::string name;
        Location loc;
    };

    struct Object {
        struct Atributes {
            std::string name;
            Location loc;
        };
        Atributes atributes;
        std::shared_ptr<Renderizable> renderizable_ptr;
        Object(const std::shared_ptr<Renderizable>& renderizable_ptr) : renderizable_ptr{renderizable_ptr} {   }
        Object(const Object& obj) : atributes{obj.atributes}, renderizable_ptr{obj.renderizable_ptr} {   }
    };

private:
    typedef std::vector<Object> obj_container_t;
    obj_container_t objects;

public:
    Atributes atributes;

    CompositionNode()   {   }
    CompositionNode(const Atributes& atributes)
    : atributes{atributes}
    {     }
    CompositionNode(const CompositionNode& c)
    : objects{c.objects}, atributes{c.atributes}
    {   }

    inline const obj_container_t& get_objects(void) const { return objects; }
    inline void erase_object(const obj_container_t::iterator& it) { objects.erase(it); }
    inline void emplace_object(const Object& obj) { objects.emplace_back(obj); }

    void apply(void) const;
};

#endif /* MOSHI3D_COMPOSITION_NODE_H_ */