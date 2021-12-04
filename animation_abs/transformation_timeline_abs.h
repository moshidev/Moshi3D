/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TRANSFORMATION_TIMELINE_ABS_H_
#define MOSHI3D_TRANSFORMATION_TIMELINE_ABS_H_

#include "transformation.h"

class TransformationTimelineAbs {
public:
    virtual bool empty(void) const = 0;
    virtual Transformation&& get_transformation_abs(float time_point, bool loop) const = 0;
};

#endif /* MOSHI3D_TRANSFORMATION_TIMELINE_ABS_H_ */