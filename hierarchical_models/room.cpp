#include "room.h"

CompositionNode::iterator Room::build_wall(CompositionNode& parent, const std::shared_ptr<Cube>& cube_mesh, const Tupla3f& scaling, const Tupla3f& location) {
    CompositionNode::Object obj{location, cube_mesh};
    obj.loc.scaling = scaling;
    std::shared_ptr<CompositionNode> node = std::make_shared<CompositionNode>(obj);
    return parent.add_child(node);
}

Room::Room(const Tupla3f& d) {
    constexpr float wall_width = 0.5;
    std::shared_ptr<TextureObject> cube_texture;
    cube_mesh = std::make_shared<Cube>(1);
    cube_texture = std::make_shared<TextureObject>("resources/text-madera.jpg");
    cube_mesh->set_texture(cube_texture);
    cube_mesh->enable_shaded_mode(true);

    CompositionNode::iterator floor_it = build_wall(root, cube_mesh, {d[1], wall_width, d[0]}, {0,-wall_width/2,0});
    CompositionNode& floor = *floor_it->second;
    build_wall(floor, cube_mesh, {wall_width, d[2], d[0]}, {-d[1]/2+wall_width/2, +d[2]/2, 0});
    build_wall(floor, cube_mesh, {wall_width, d[2], d[0]}, {+d[1]/2-wall_width/2, +d[2]/2, 0});
    build_wall(floor, cube_mesh, {d[1]-wall_width*2, d[2], wall_width}, {0, +d[2]/2, -d[0]/2+wall_width/2});
    build_wall(floor, cube_mesh, {d[1]-wall_width*2, d[2], wall_width}, {0, +d[2]/2, +d[0]/2-wall_width/2});
    build_wall(floor, cube_mesh, {d[1], wall_width, d[0]}, {0,d[2]+wall_width/2,0});
}

void Room::draw(const Renderer& r) const {
    root.draw(r);
}

void Room::apply_to_meshes(const std::function<void(Mesh3D&)>& func) {
    func(*cube_mesh);
}