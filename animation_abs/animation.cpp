#include "animation.h"

float Animation::calc_max_time_point(void) const {
    float max = 0;
    if (!translation_tt.empty()) {
        max = std::max(translation_tt.rbegin()->first, max);
    }
    if (!scaling_tt.empty()) {
        max = std::max(scaling_tt.rbegin()->first, max);
    }
    if (!rotation_tt.empty()) {
        max = std::max(rotation_tt.rbegin()->first, max);
    }
    return max;
}

void Animation::apply(float time_point) const {
    if (loop) {
        float max = calc_max_time_point();
        time_point = fmod(time_point, max);
    }
    if (!translation_tt.empty()) {
        translation_tt.get_transformation(time_point).apply();
    }
    if (!scaling_tt.empty()) {
        scaling_tt.get_transformation(time_point).apply();
    }
    if (!rotation_tt.empty()) {
        rotation_tt.get_transformation(time_point).apply();
    }
}