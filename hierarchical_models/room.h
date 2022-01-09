/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ROOM_H_
#define MOSHI3D_ROOM_H_

#include "composition_node.h"
#include "renderizable.h"
#include "texture_object.h"
#include "cube.h"
#include <memory>

class Room : public Renderizable {
    CompositionNode root;
    std::shared_ptr<Cube> cube_mesh;

    static CompositionNode::iterator build_wall(CompositionNode& parent, const std::shared_ptr<Cube>& cube_mesh, const Tupla3f& scaling, const Tupla3f& location);
public:
    Room(const Tupla3f& lenwidthdepth);
    inline CompositionNode& get_root(void) { return root; };

    void draw(const Renderer& r) const;
};

#endif /* MOSHI3D_ROOM_H_ */