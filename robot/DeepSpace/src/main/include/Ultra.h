#pragma once

#include <frc/WPILib.h>
#include <frc/Ultrasonic.h>

class Ultra
{
    public:
        Ultra();
        float getDistanceLeftFront();
        float getDistanceRightFront();
        float getDistanceLeftBack();
        float getDistanceRightBack();
        frc::Ultrasonic *m_leftFront = new frc::Ultrasonic(0, 1);
        frc::Ultrasonic *m_rightFront = new frc::Ultrasonic(2, 3);
        frc::Ultrasonic *m_leftBack = new frc::Ultrasonic(4,5);
        frc::Ultrasonic *m_rightBack = new frc::Ultrasonic(6,7);
};