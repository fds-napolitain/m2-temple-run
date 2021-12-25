//
// Created by edgar on 26/11/2021.
//

#ifndef TEMPLERUN_TIMESTEP_HPP
#define TEMPLERUN_TIMESTEP_HPP

class TimeStep {

public:
    TimeStep(float time = 0.0f);
    [[nodiscard]] float getTMilliSeconds() const;
    [[nodiscard]] float getSeconds() const;
    operator float() const;
private:
    float m_time;


};

#endif //TEMPLERUN_TIMESTEP_HPP
