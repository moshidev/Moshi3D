#include "rectangle.h"

Rectangle::Rectangle(const Tupla2f& d) {
    //cube_init_vertices(vertices.data, lado);
    //cube_init_indices(indices.data);
    //cube_init_texture_coordinates(texture_coordinates.data);
    vertices.data.emplace_back(-d[0]/2, -d[1]/2, 0);
    vertices.data.emplace_back(+d[0]/2, -d[1]/2, 0);
    vertices.data.emplace_back(-d[0]/2, +d[1]/2, 0);
    vertices.data.emplace_back(+d[0]/2, +d[1]/2, 0);
    indices.data.emplace_back(0, 1, 2);
    indices.data.emplace_back(1, 3, 2);
    texture_coordinates.data.emplace_back(0, 0);
    texture_coordinates.data.emplace_back(1, 0);
    texture_coordinates.data.emplace_back(0, 1);
    texture_coordinates.data.emplace_back(1, 1);
    init_color(vertices.data.size());
    init_normal_vectors();
}

void Rectangle::set_texture(const std::shared_ptr<TextureObject>& texture) {
    this->texture = std::make_unique<Texture>(texture, texture_coordinates);
    make_current_data_lists();
}