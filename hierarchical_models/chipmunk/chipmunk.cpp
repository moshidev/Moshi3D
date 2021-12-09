#include "chipmunk.h"

std::shared_ptr<CompositionNode> Chipmunk::build_leg(float x, float z, const std::shared_ptr<ObjPLY>& leg_mesh) {
    CompositionNode::Object obj{Tupla3f{x,z,0}, leg_mesh};
    return std::make_shared<CompositionNode>(obj);
}

std::shared_ptr<CompositionNode> Chipmunk::build_tail(const std::shared_ptr<ObjPLY>& tail_1_mesh, const std::shared_ptr<ObjPLY>& tail_2_mesh) {
    CompositionNode::Object obj{tail_1_mesh};
    std::shared_ptr<CompositionNode> tail_1 {std::make_shared<CompositionNode>(obj)};

    obj.renderizable = tail_2_mesh;
    std::shared_ptr<CompositionNode> tail_2 {std::make_shared<CompositionNode>(obj)};

    tail_1->add_child(tail_2);
    return tail_1;
}

std::shared_ptr<CompositionNode> Chipmunk::build_ear(const std::shared_ptr<ObjPLY>& ear_mesh) {
    CompositionNode::Object obj{ear_mesh};
    return std::make_shared<CompositionNode>(obj);
}

std::shared_ptr<CompositionNode> Chipmunk::build_body(float y, const std::shared_ptr<ObjPLY>& body_mesh) {
    CompositionNode::Object obj{Tupla3f{0,y,0}, body_mesh};
    return std::make_shared<CompositionNode>(obj);
}

Chipmunk::Chipmunk() {
    auto body = root.add_child(build_body(0, body_mesh));
    body->first.rotation[0] = M_PI_2;
    body->first.scaling = {2,2,2};
    body->second->add_child(build_ear(ear_R_mesh));
    body->second->add_child(build_ear(ear_L_mesh));
    body->second->add_child(build_tail(tail_1_mesh, tail_2_mesh));
    body->second->add_child(build_leg(-0.2, 0.1, leg_mesh));    //BL
    body->second->add_child(build_leg(0.2, 0.1, leg_mesh));     //BR
    body->second->add_child(build_leg(-0.15, -0.3, leg_mesh));  //FL
    body->second->add_child(build_leg(0.15, -0.3, leg_mesh));   //FR

    meshes.push_back(body_mesh);
    meshes.push_back(tail_1_mesh);
    meshes.push_back(tail_2_mesh);
    meshes.push_back(ear_R_mesh);
    meshes.push_back(ear_L_mesh);
    meshes.push_back(leg_mesh);

    for (auto& m : meshes) {
        m.lock()->enable_polygon_modes(GL_LINE);
    }
}

void Chipmunk::draw(const Renderer& r) const {
    root.draw(r);
}

void Chipmunk::apply_to_meshes(const std::function<void(ObjPLY&)>& func) {
    for (const auto& m : meshes) {
        func(*m.lock());
    }
}