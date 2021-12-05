/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ANIMATION_H_
#define MOSHI3D_ANIMATION_H_

#include "tuplasg.h"
#include "point_rotation.h"
#include "rotation.h"
#include "scaling.h"
#include "translation.h"
#include "transformation_timeline.hpp"
#include <vector>

class Animation {
public:
    TransformationTimeline<Translation> translation_tt;
    TransformationTimeline<Scaling> scaling_tt;
    TransformationTimeline<PointRotation> rotation_tt;
    
    void apply(float time_point) const;
};

#endif /* MOSHI3D_ANIMATION_H_ */