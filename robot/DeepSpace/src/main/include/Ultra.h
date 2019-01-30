#pragma once

#include <frc/WPILib.h>
#include <frc/Ultrasonic.h>

class Ultra
{
    public:
        Ultra();
        float getDistanceDownFront();
        float getDistanceDownBack();
        frc::Ultrasonic *m_downFront = new frc::Ultrasonic(0, 1);
        frc::Ultrasonic *m_downBack = new frc::Ultrasonic(2, 3);
};