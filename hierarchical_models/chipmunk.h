/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_CHIPMUNK_H_
#define MOSHI3D_CHIPMUNK_H_

#include "renderizable.h"
#include "composition_node.h"
#include "objply.h"
#include <memory>
#include <vector>

class Chipmunk : public Renderizable {
    CompositionNode root;
    float manual_step_size {0.1};

    std::vector<std::weak_ptr<ObjPLY>> meshes;
    std::vector<CompositionNode::iterator> parts;

    void init_meshes_vector(void);

    void increment_animation_man(CompositionNode::iterator& it);
    void decrement_animation_man(CompositionNode::iterator& it);
public:
    enum Parts {
        kBody, kLeg_F_R, kLeg_F_L, kLeg_B_R, kLeg_B_L, kEar_R, kEar_L, kTail, kPARTS_SIZE
    };
    Chipmunk();
    inline CompositionNode& get_root(void) { return root; };

    void draw(Renderer& r) const;
    void apply_to_meshes(const std::function<void(Mesh3D&)>& func);
    
    void increment_animation_aut(void);

    void increment_animation_man(void);
    void increment_animation_man(enum Parts part);
    void decrement_animation_man(void);
    void decrement_animation_man(enum Parts part);

    void multiply_speed_factor(float factor);
    void multiply_speed_factor(float factor, enum Parts part);

    inline float get_man_step_size(void) const { return manual_step_size; }
    inline void set_man_step_size(float step_size) { manual_step_size = step_size; }

private:
    std::shared_ptr<ObjPLY> body_mesh {std::make_shared<ObjPLY>("resources/chipmunk/body.ply")};
    std::shared_ptr<ObjPLY> leg_mesh {std::make_shared<ObjPLY>("resources/chipmunk/leg.ply")};
    std::shared_ptr<ObjPLY> ear_L_mesh {std::make_shared<ObjPLY>("resources/chipmunk/ear_L.ply")};
    std::shared_ptr<ObjPLY> tail_mesh {std::make_shared<ObjPLY>("resources/chipmunk/tail.ply")};

    CompositionNode::iterator build_leg(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor=1);
    CompositionNode::iterator build_body(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor=1);
    CompositionNode::iterator build_tail(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor=1);
    CompositionNode::iterator build_ear_L(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor=1);
    CompositionNode::iterator build_ear_R(CompositionNode& parent, const Tupla3f& pos, float percentaje_offset, float speed_factor=1);

    static std::shared_ptr<CompositionNode> build_node(const Tupla3f& pos, const std::shared_ptr<ObjPLY>& mesh);

    static void set_animation_leg_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor);
    static void set_animation_body_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor);
    static void set_animation_tail_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor);
    static void set_animation_ears_moving(Animation& anim, float percentaje_offset, float peak_angle, float speed_factor);
};

#endif /* MOSHI3D_CHIPMUNK_H_ */