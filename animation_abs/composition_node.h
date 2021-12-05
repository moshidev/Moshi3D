/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_COMPOSITION_NODE_H_
#define MOSHI3D_COMPOSITION_NODE_H_

#include "animation.h"
#include "renderizable.h"
#include "tuplasg.h"
#include <memory>
#include <string>
#include <vector>

class CompositionNodeData {
public:
    struct Location {
        Tupla3f scaling {1,1,1};
        Tupla3f position {0,0,0};
        Tupla2f rotation_polar {0,0};
        
        void apply(void) const;
    };

    struct Atributes {
        std::string name;
        bool visible {true};
        float init_time {0};
        float duration {0};
        bool loop {false};
        Location location;

        inline bool in_range(float time_point) const { return loop || (time_point >= init_time && time_point <= init_time+duration); }
        inline bool is_visible(float time_point) const { return visible && in_range(time_point); }
    };

    struct Object {
        struct Atributes {
            std::string name;
            Location location;
        };
        Atributes atributes;
        std::shared_ptr<Renderizable> renderizable_ptr;
        Object(const std::shared_ptr<Renderizable>& renderizable_ptr) : renderizable_ptr{renderizable_ptr} {   }
        Object(const Object& obj) : renderizable_ptr{obj.renderizable_ptr} {   }
    };

private:
    typedef std::vector<Object> obj_container_t;
    obj_container_t objects;

public:
    Atributes atributes;
    Animation animation;

    CompositionNodeData()   {   }
    CompositionNodeData(const Atributes& atributes)
    : atributes{atributes}
    {     }
    CompositionNodeData(const CompositionNodeData& c)
    : objects{c.objects}, atributes{c.atributes}, animation{c.animation}
    {   }

    inline const obj_container_t& get_objects(void) const { return objects; }
    inline void erase_object(const obj_container_t::iterator& it) { objects.erase(it); }
    inline void emplace_object(const Object& obj) { objects.emplace_back(obj); }
};

#endif /* MOSHI3D_COMPOSITION_NODE_H_ */