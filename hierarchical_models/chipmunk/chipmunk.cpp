#include "chipmunk.h"

/*CompositionNode Chipmunk::build_leg(float x, float z, const std::shared_ptr<ObjPLY>& leg_mesh) {
    CompositionNode::Object leg_obj{leg_mesh};
    CompositionNode leg;
    
    leg_obj.atributes.loc.position[0] = x;
    leg_obj.atributes.loc.position[2] = z;
    leg.emplace_object(leg_obj);

    return leg;
}

Composition Chipmunk::build_tail(const std::shared_ptr<ObjPLY>& tail_1_mesh, const std::shared_ptr<ObjPLY>& tail_2_mesh) {
    CompositionNode tail_2;
    tail_2.emplace_object({tail_2_mesh});

    Composition c;
    (*c.get_root()).emplace_object({tail_1_mesh});
    c.emplace_child(c.get_root(), tail_2);

    return c;
}

CompositionNode Chipmunk::build_ear(const std::shared_ptr<ObjPLY>& ear_mesh) {
    CompositionNode c;

    c.emplace_object({ear_mesh});

    return c;
}

CompositionNode Chipmunk::build_body(float y, const std::shared_ptr<ObjPLY>& body_mesh) {
    CompositionNode::Object body_obj{body_mesh};

    body_obj.atributes.loc.position[1] = y;
    CompositionNode c;
    c.emplace_object(body_obj);

    return c;
}*/

Chipmunk::Chipmunk() {
    /*nodes.resize(9, composition.get_root());

    nodes[BODY] = composition.get_root();
    *nodes[BODY] = build_body(1, body_mesh);
    nodes[TAIL_1] = composition.emplace_child(nodes[BODY], build_tail(tail_1_mesh, tail_2_mesh));
    nodes[TAIL_2] = nodes[TAIL_1].get_first_child();
    nodes[EAR_R] = composition.emplace_child(nodes[BODY], build_ear(ear_R_mesh));
    nodes[EAR_L] = composition.emplace_child(nodes[BODY], build_ear(ear_L_mesh));
    nodes[LEG_F_R] = composition.emplace_child(nodes[BODY], build_leg(1, 2, leg_mesh));

    meshes.push_back(body_mesh);
    meshes.push_back(tail_1_mesh);
    meshes.push_back(tail_2_mesh);
    meshes.push_back(ear_R_mesh);
    meshes.push_back(ear_L_mesh);
    meshes.push_back(leg_mesh);

    for (auto& m : meshes) {
        m.lock()->enable_chess_mode(true);
    }*/
}

void Chipmunk::draw(const Renderer& r) const {
    //composition.draw(r);
}