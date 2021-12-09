/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_CHIPMUNK_H_
#define MOSHI3D_CHIPMUNK_H_

#include "renderizable.h"
#include "composition.h"
#include "composition_node.h"
#include "objply.h"
#include <memory>
#include <vector>

class Chipmunk : public Renderizable {
    std::shared_ptr<ObjPLY> body_mesh {std::make_shared<ObjPLY>("resources/chipmunk/body.ply")};
    std::shared_ptr<ObjPLY> leg_mesh {std::make_shared<ObjPLY>("resources/chipmunk/leg.ply")};
    std::shared_ptr<ObjPLY> ear_R_mesh {std::make_shared<ObjPLY>("resources/chipmunk/ear_R.ply")};
    std::shared_ptr<ObjPLY> ear_L_mesh {std::make_shared<ObjPLY>("resources/chipmunk/ear_L.ply")};
    std::shared_ptr<ObjPLY> tail_1_mesh {std::make_shared<ObjPLY>("resources/chipmunk/tail_01.ply")};
    std::shared_ptr<ObjPLY> tail_2_mesh {std::make_shared<ObjPLY>("resources/chipmunk/tail_02.ply")};
    Composition composition;

    enum NodeItk {
        BODY, EAR_R, EAR_L, TAIL_1, TAIL_2, LEG_F_R, LEG_F_L, LEG_B_R, LEG_B_L
    };
    std::vector<Composition::iterator> nodes;
    std::vector<std::weak_ptr<ObjPLY>> meshes;

    static CompositionNode build_leg(float x, float z, const std::shared_ptr<ObjPLY>& leg_mesh);
    static Composition build_tail(const std::shared_ptr<ObjPLY>& tail_1_mesh, const std::shared_ptr<ObjPLY>& tail_2_mesh);
    static CompositionNode build_ear(const std::shared_ptr<ObjPLY>& ear_mesh);
    static CompositionNode build_body(float y, const std::shared_ptr<ObjPLY>& body_mesh);
public:
    Chipmunk();

    void draw(const Renderer& r) const;
};

#endif /* MOSHI3D_CHIPMUNK_H_ */