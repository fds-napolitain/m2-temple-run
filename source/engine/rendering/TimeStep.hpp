//
// Created by edgar on 26/11/2021.
//

#ifndef TEMPLERUN_TIMESTEP_HPP
#define TEMPLERUN_TIMESTEP_HPP

class TimeStep{
public:
    TimeStep(float time =0.0f) : m_time(time) {}
    [[nodiscard]] float getTMilliSeconds() const { return m_time * 1000.0f;}
    [[nodiscard]] float getSeconds() const { return m_time ;}
    operator float() const {return m_time;}
private:
    float m_time;


};

#endif //TEMPLERUN_TIMESTEP_HPP
