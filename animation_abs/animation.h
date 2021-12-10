/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_ANIMATION_H_
#define MOSHI3D_ANIMATION_H_

#include "tuplasg.h"
#include "rotation.h"
#include "scaling.h"
#include "translation.h"
#include "transformation_timeline.hpp"
#include <chrono>
#include <vector>

class Animation {
    float percentaje {0};
    float anim_factor {1};
    std::chrono::time_point<std::chrono::steady_clock> last_time_point;
    
    float calc_animation_percentaje_step_size(float time_elapsed) const;

public:
    TransformationTimeline<Translation> translation_tt;
    TransformationTimeline<Scaling> scaling_tt;
    TransformationTimeline<Rotation> rotation_tt;

    Animation();
    Animation(float ini_percentaje);
    Animation(const Animation& a);
    
    void apply(void) const;
    float get_lenght(void) const;
    inline float get_percentaje(void) const { return percentaje; }
    
    bool set_percentaje(float percentaje);
    bool set_percentaje_loop(float percentaje);

    inline float get_speed_factor(void) const { return anim_factor; }
    inline void set_speed_factor(float f) { anim_factor = f; }

    bool increment_anim(float time_elapsed);
    bool increment_anim_loop(float time_elapsed);

    bool increment_anim(void);
    bool increment_anim_loop(void);
};

#endif /* MOSHI3D_ANIMATION_H_ */