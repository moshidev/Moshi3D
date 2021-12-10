#include "animation.h"

Animation::Animation() {
    set_percentaje(0);
}

Animation::Animation(float ini_percentaje) {
    set_percentaje(ini_percentaje);
}

Animation::Animation(const Animation& a) {
    set_percentaje(a.percentaje);
}

void Animation::apply(void) const {
    if (!translation_tt.empty()) {
        translation_tt.get_transformation(percentaje).apply();
    }
    if (!scaling_tt.empty()) {
        scaling_tt.get_transformation(percentaje).apply();
    }
    if (!rotation_tt.empty()) {
        rotation_tt.get_transformation(percentaje).apply();
    }
}

float Animation::get_lenght(void) const {
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

bool Animation::set_percentaje(float p) {
    percentaje = p > 1 ? 1 : p;
    percentaje = p < 0 ? 0 : p;
    last_time_point = std::chrono::steady_clock::now();
    return p > 1 || p < 0;
}

bool Animation::set_percentaje_loop(float p) {
    if (p < 0 || p > 1) {
        p = std::fmod(p, 1);
        p = p < 0 ? p+1 : p;
    }
    percentaje = p;
    last_time_point = std::chrono::steady_clock::now();
    return p > 1 || p < 0;
}

float Animation::calc_animation_percentaje_step_size(float time_elapsed) const {
    float len = get_lenght();
    if (len) {
        return time_elapsed * anim_factor * 1/get_lenght();
    }
    else {
        return 0;
    }
}

bool Animation::increment_anim(float time_elapsed) {
    return set_percentaje(get_percentaje() + calc_animation_percentaje_step_size(time_elapsed));
}

bool Animation::increment_anim_loop(float time_elapsed) {
    return set_percentaje_loop(get_percentaje() + calc_animation_percentaje_step_size(time_elapsed));
}

bool Animation::increment_anim(void) {
    auto tp = std::chrono::steady_clock::now();
    float time_elapsed = std::chrono::duration<float>(tp-last_time_point).count();
    return increment_anim(time_elapsed);
}

bool Animation::increment_anim_loop(void) {
    auto tp = std::chrono::steady_clock::now();
    float time_elapsed = std::chrono::duration<float>(tp-last_time_point).count();
    return increment_anim_loop(time_elapsed);
}