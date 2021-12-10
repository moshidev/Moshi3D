/**
 * 2021 © Daniel Pedrosa Montes <pedrosam.sh@gmail.com>
 * GPLv3 License.
 */

#ifndef MOSHI3D_TRANSFORMATION_TIMELINE_H_
#define MOSHI3D_TRANSFORMATION_TIMELINE_H_

#include <map>

template<typename _T>
class TransformationTimeline {
public:
    struct KeyFrame;

private:
    std::map<float,KeyFrame> transformations;

public:
    TransformationTimeline() = default;
    TransformationTimeline(const TransformationTimeline& tt) = default;

    typedef typename std::map<float,KeyFrame>::iterator iterator;
    typedef typename std::map<float,KeyFrame>::const_iterator const_iterator;
    inline auto begin(void) const { return transformations.begin(); }
    inline auto begin(void) { return transformations.begin(); }
    inline auto end(void) const { return transformations.end(); }
    inline auto rbegin(void) const { return transformations.rbegin(); }
    inline auto rbegin(void) { return transformations.rbegin(); }
    inline auto rend(void) const { return transformations.rend(); }

    void add_key_frame(const KeyFrame& kf) {
        transformations.insert_or_assign(kf.pos, kf);
    }
    
    bool empty(void) const { return transformations.empty(); }

    _T get_transformation(float percentaje) const {
        auto last_it = transformations.rbegin();
        float time_point = percentaje * last_it->first;
        
        if (transformations.size() < 2) {
            return last_it->second.transformation;
        }

        auto upper_it = transformations.upper_bound(time_point);
        auto lower_it = upper_it;
        --lower_it;
        const KeyFrame& upper_keyf = upper_it->second;
        const KeyFrame& lower_keyf = lower_it->second;

        const float inter_percentaje = (time_point - lower_keyf.pos)/(upper_keyf.pos - lower_keyf.pos);
        if (inter_percentaje < 0) {
            return lower_keyf.transformation;
        }
        return interpolation(lower_keyf.transformation, upper_keyf.transformation, inter_percentaje, lower_keyf.interpolation_function);
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
    KeyFrame(const KeyFrame& kf) = default;
};

#endif /* MOSHI3D_TRANSFORMATION_TIMELINE_H_ */