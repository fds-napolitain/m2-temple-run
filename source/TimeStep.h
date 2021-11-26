//
// Created by edgar on 26/11/2021.
//

#ifndef TEMPLERUN_TIMESTEP_H
#define TEMPLERUN_TIMESTEP_H

class TimeStep{
public:
    TimeStep(float time =0.0f) : m_time(time) {}
    float getTMilliSeconds() { return m_time * 1000.0f;}
    float getSeconds() { return m_time ;}
    operator float() const {return m_time;}
private:
    float m_time;


};

#endif //TEMPLERUN_TIMESTEP_H
