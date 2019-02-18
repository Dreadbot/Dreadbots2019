#include <Ultra.h>
#include <frc/WPILib.h>
#include <frc/Ultrasonic.h>

Ultra::Ultra()
{
    m_leftFront->SetAutomaticMode(true);
    m_rightFront->SetAutomaticMode(true);
    m_leftBack->SetAutomaticMode(true);
    m_rightBack->SetAutomaticMode(true);
}
float Ultra::getDistanceLeftFront()
{
    return m_leftFront->GetRangeInches();
}
float Ultra::getDistanceRightFront()
{
    return m_rightFront->GetRangeInches();
}
float Ultra::getDistanceLeftBack()
{
    return m_leftBack->GetRangeInches();
}
float Ultra::getDistanceRightBack()
{
    return m_rightBack->GetRangeInches();
}