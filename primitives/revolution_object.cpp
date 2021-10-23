#include "ply_reader.h"
#include "revolution_object.h"

void RevolutionObject::make_mesh(std::vector<Tupla3f> revolution_coordinates, std::vector<Tupla3f>& result, int num_instances) {
    std::vector<Tupla3f>& rv = revolution_coordinates;
    Tupla3f south, north;
    result.clear();
    result.reserve(rv.size()*num_instances);

    if (rv.back()[1] == 0.0) {
        north = rv.back();
        rv.pop_back();
    }
    if (rv.front()[1] == 0.0) {
        south = rv.back();
        rv.erase(rv.begin());
    }

    for (int i = 0; i < num_instances; i++) {
        double angle = 2*M_PI/num_instances * i;
        for (const auto& c : rv) {
            result.emplace_back(c[0]*cos(angle)*150.0f, c[1]*150.0f, c[0]*sin(angle)*150.0f);
        }
    }

    for (int i = 0; i < num_instances; i++) {
        for (int j = 0; j < revolution_coordinates.size()-1; j++) {
            indices.emplace_back(i*revolution_coordinates.size()+j, ((i+1)%num_instances)*revolution_coordinates.size()+j+1, ((i+1)%num_instances)*revolution_coordinates.size()+j);
            indices.emplace_back(i*revolution_coordinates.size()+j, i*revolution_coordinates.size()+j+1, ((i+1)%num_instances)*revolution_coordinates.size()+j+1);
        }
    }
}

RevolutionObject::RevolutionObject(const std::string& ifile, int num_instances, bool upper_surface, bool lower_surface) {
    std::vector<Tupla3f> coordinates;
    ply::read_vertices(ifile, coordinates);
    make_mesh(coordinates, vertices, num_instances);
    color.init(*this);
    //color.set_chess(*this);
}

RevolutionObject::RevolutionObject(const std::vector<Tupla3f>& revolution_coordinates, int num_instances, bool upper_surface, bool lower_surface) {
    make_mesh(revolution_coordinates, vertices, num_instances);
    color.init(*this);
}