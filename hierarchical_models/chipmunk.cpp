#include "chipmunk.h"

std::shared_ptr<CompositionNode> Chipmunk::build_node(const Tupla3f& pos, const std::shared_ptr<ObjPLY>& mesh) {
    CompositionNode::Object obj{mesh};
    auto node = std::make_shared<CompositionNode>(obj);
    node->get_location().position = pos;
    return node;
}

CompositionNode::iterator Chipmunk::build_leg(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor) {
    auto it = parent.add_child(build_node(pos, leg_mesh));
    set_animation_leg_moving(it->second->get_animation(), percentaje_offset, M_PI_4/2, speed_factor);
    return it;
}

CompositionNode::iterator Chipmunk::build_body(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor) {
    auto it = parent.add_child(build_node(pos, body_mesh));
    set_animation_body_moving(it->second->get_animation(), percentaje_offset, -M_PI_4/16, speed_factor);
    return it;
}

CompositionNode::iterator Chipmunk::build_tail(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor) {
    auto it = parent.add_child(build_node(pos, tail_mesh));
    set_animation_tail_moving(it->second->get_animation(), percentaje_offset, M_PI_4/2, speed_factor);
    return it;
}

CompositionNode::iterator Chipmunk::build_ear_L(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor) {
    CompositionNode::Object obj{ear_L_mesh};
    obj.loc.rotation = {M_PI_4/2, -M_PI_4, -M_PI_4/2};
    auto it_L = parent.add_child(std::make_shared<CompositionNode>(obj));
    it_L->second->get_location().position = pos;
    set_animation_ears_moving(it_L->second->get_animation(), percentaje_offset, -M_PI_4/2, speed_factor);
    return it_L;
}

CompositionNode::iterator Chipmunk::build_ear_R(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor) {
    CompositionNode::Object obj{ear_L_mesh};
    obj.loc.rotation = {M_PI_4/2, -M_PI_2-M_PI_4, -M_PI_4/2};
    auto it_R = parent.add_child(std::make_shared<CompositionNode>(obj));
    it_R->second->get_location().position = pos;
    it_R->second->get_location().rotation = {0, 0, 0};
    set_animation_ears_moving(it_R->second->get_animation(), percentaje_offset, -M_PI_4/2, speed_factor);
    return it_R;
}

void Chipmunk::set_animation_leg_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor) {
    Rotation rot_a{{peak_angle,0,0}};
    Rotation rot_b{{-peak_angle,0,0}};
    auto func = [] (float p) { return 1-(p-1)*(p-1);};
    anim.rotation_tt.add_key_frame({0, rot_a, func});
    anim.rotation_tt.add_key_frame({1, rot_b, func});
    anim.rotation_tt.add_key_frame({2, rot_a});
    anim.set_percentaje(percentaje_offset);
    anim.set_speed_factor(speed_factor);
}

void Chipmunk::set_animation_body_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor) {
    Rotation rot_a{{0,0,0}};
    Rotation rot_b{{peak_angle,0,0}};
    auto func = [] (float p) { return 1-(p-1)*(p-1);};
    anim.rotation_tt.add_key_frame({0, rot_b, func});
    anim.rotation_tt.add_key_frame({0.26, rot_a, func});
    anim.rotation_tt.add_key_frame({1, rot_b, func});
    anim.set_percentaje(percentaje_offset);
    anim.set_speed_factor(speed_factor);
}

void Chipmunk::set_animation_tail_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor) {
    Rotation rot_a{{0,peak_angle,0}};
    Rotation rot_b{{0,-peak_angle,0}};
    auto func = [] (float p) { return std::cos((p+1)*M_PI)/2 + 0.5;};
    anim.rotation_tt.add_key_frame({0, rot_a, func});
    anim.rotation_tt.add_key_frame({1, rot_b, func});
    anim.rotation_tt.add_key_frame({2, rot_a});
    anim.set_percentaje(percentaje_offset);
    anim.set_speed_factor(speed_factor);
}

void Chipmunk::set_animation_ears_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor) {
    Rotation rot_a{{0,0,peak_angle}, {+0.075, 0, 0}};
    Rotation rot_b{{0,0,-peak_angle}, {-0.075, 0.05, 0}};
    auto func = [] (float p) { return std::cos((p+1)*M_PI)/2 + 0.5;};
    anim.rotation_tt.add_key_frame({0, rot_a, func});
    anim.rotation_tt.add_key_frame({1, rot_b, func});
    anim.rotation_tt.add_key_frame({2, rot_a});
    anim.set_percentaje(percentaje_offset);
    anim.set_speed_factor(speed_factor);
}

void Chipmunk::init_meshes_vector(void) {
    meshes.push_back(body_mesh);
    meshes.push_back(ear_L_mesh);
    meshes.push_back(leg_mesh);
    meshes.push_back(tail_mesh);
}

Chipmunk::Chipmunk() {
    parts.resize(kPARTS_SIZE);

    root.get_location().scaling = {2,2,2};  // rotación graciosa : 1/(std::tanh((p-0.5)*3)/2 + 0.5)
    root.get_location().position = {0, 0.44, 0};

    parts[kBody] = build_body(root, {0,0,0}, 0.1, 1.8);
    auto& body = *parts[kBody]->second;

    parts[kLeg_F_R] = build_leg(body, {-0.125, 0.3, +0.3}, 0.6, 1.8);
    parts[kLeg_F_L] = build_leg(body, {+0.125, 0.3, +0.3}, 0.1, 1.8);
    parts[kLeg_B_R] = build_leg(body, {-0.125, 0.3, -0.15}, 0, 1.8);
    parts[kLeg_B_L] = build_leg(body, {+0.125, 0.3, -0.15}, 0.5, 1.8);

    parts[kTail] = build_tail(body, {0, 0.175, -0.3}, 0, 2);

    parts[kEar_L] = build_ear_L(body, {-0.175, 0.5, 0.65}, 0, 1.8);
    parts[kEar_R] = build_ear_R(body, {+0.175, 0.5, 0.65}, 0, 1.8);

    init_meshes_vector();
}

void Chipmunk::draw(Renderer& r) const {
    root.draw(r);
}

void Chipmunk::apply_to_meshes(const std::function<void(Mesh3D&)>& func) {
    for (const auto& m : meshes) {
        func(*m.lock());
    }
}

void Chipmunk::increment_animation_aut(void) {
    auto func = [] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(std::abs(a.get_speed_factor()));
        a.increment_anim_loop();
    };
    root.execute_preorder(func);
}

void Chipmunk::increment_animation_man(void) {
    auto func = [this] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(std::abs(a.get_speed_factor()));
        a.increment_anim_loop(manual_step_size);
    };
    root.execute_preorder(func);
}

void Chipmunk::increment_animation_man(enum Parts part) {
    increment_animation_man(parts[part]);
}

void Chipmunk::increment_animation_man(CompositionNode::iterator& it) {
    auto& a = it->second->get_animation();
    a.set_speed_factor(std::abs(a.get_speed_factor()));
    a.increment_anim_loop(manual_step_size);
}

void Chipmunk::decrement_animation_man(void) {
    auto func = [this] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(-std::abs(a.get_speed_factor()));
        a.increment_anim_loop(manual_step_size);
    };
    root.execute_preorder(func);
}

void Chipmunk::decrement_animation_man(enum Parts part) {
    decrement_animation_man(parts[part]);
}

void Chipmunk::decrement_animation_man(CompositionNode::iterator& it) {
    auto& a = it->second->get_animation();
    a.set_speed_factor(-std::abs(a.get_speed_factor()));
    a.increment_anim_loop(manual_step_size);
}

void Chipmunk::multiply_speed_factor(float factor) {
    auto func = [factor] (CompositionNode& c) {
        auto& a = c.get_animation();
        a.set_speed_factor(factor*std::abs(a.get_speed_factor()));
    };
    root.execute_preorder(func);
}

void Chipmunk::multiply_speed_factor(float factor, enum Parts part) {
    auto& anim = parts[part]->second->get_animation();
    anim.set_speed_factor(factor*std::abs(anim.get_speed_factor()));
}