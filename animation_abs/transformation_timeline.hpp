/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TRANSFORMATION_TIMELINE_H_
#define MOSHI3D_TRANSFORMATION_TIMELINE_H_

#include "transformation_timeline_abs.h"
#include <map>

struct FloatCmp {
    constexpr bool operator()(const float &lhs, const float &rhs) const 
    {
        return lhs < rhs;
    }
};

template<typename _T>
class TransformationTimeline {
public:
    struct KeyFrame;

private:
    std::map<float,KeyFrame,FloatCmp> transformations;

public:
    TransformationTimeline()    {  }
    TransformationTimeline(const TransformationTimeline& tt) : transformations{tt.transformations}  {   }
    TransformationTimeline(TransformationTimeline&& tt) : transformations{tt.transformations}  {   }

    void add_key_frame(const KeyFrame& kf) {
        transformations.insert_or_assign(kf.pos, kf);
    }
    
    bool empty(void) const { return transformations.empty(); }

    _T get_transformation(float time_point) const {
        auto upper_it = transformations.upper_bound(time_point);
        auto lower_it = upper_it;
        --lower_it;
        const KeyFrame& upper_keyf = upper_it->second;
        const KeyFrame& lower_keyf = lower_it->second;

        if (lower_it == transformations.end()) {
            return upper_keyf.transformation;
        }
        else if (upper_it == transformations.end()) {
            return lower_keyf.transformation;
        }

        const float percentaje = (time_point - lower_keyf.pos)/(upper_keyf.pos - lower_keyf.pos);
        if (percentaje < 0) {
            return lower_keyf.transformation;
        }
        return interpolation(lower_keyf.transformation, upper_keyf.transformation, percentaje, lower_keyf.interpolation_function);
    }

    Transformation get_transformation_abs(float time_point) const {
        return get_transformation(time_point);
    }
};


template<typename _T>
struct TransformationTimeline<_T>::KeyFrame {
    float pos;
    _T transformation;
    std::function<float(float)> interpolation_function;

    KeyFrame() = delete;
    KeyFrame(float pos, const _T& transformation)
    : pos{pos}, transformation{transformation}, interpolation_function{[](float p){ return p; }}
    {  }
    KeyFrame(float pos, const _T& transformation, const std::function<float(float)>& interpolation_function)
    : pos{pos}, transformation{transformation}, interpolation_function{interpolation_function}
    {   }
    KeyFrame(const KeyFrame& kf)
    : pos{kf.pos}, transformation{kf.transformation}, interpolation_function{kf.interpolation_function}
    {   }
};

#endif /* MOSHI3D_TRANSFORMATION_TIMELINE_H_ */