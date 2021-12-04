#include "animation.h"

void Animation::apply(float time_point, bool loop) const {
    if (!translation_tt.empty()) {
        translation_tt.get_transformation(time_point, loop).apply();
    }
    if (!scaling_tt.empty()) {
        scaling_tt.get_transformation(time_point, loop).apply();
    }
    if (!rotation_tt.empty()) {
        rotation_tt.get_transformation(time_point, loop).apply();
    }
}