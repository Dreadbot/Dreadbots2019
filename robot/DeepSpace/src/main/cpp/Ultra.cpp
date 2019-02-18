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
    m_leftFront->GetRangeInches();
}
float Ultra::getDistanceRightBack()
{
    m_rightFront->GetRangeInches();
}
float Ultra::getDistanceLeftBack()
{
    m_leftBack->GetRangeInches();
}
float Ultra::getDistanceRightBack()
{
    m_rightBack->GetRangeInches();
}