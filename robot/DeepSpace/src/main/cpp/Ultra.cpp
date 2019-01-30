#include <Ultra.h>
#include <frc/WPILib.h>
#include <frc/Ultrasonic.h>

Ultra::Ultra()
{
    m_downFront->SetAutomaticMode(true);
    m_downBack->SetAutomaticMode(true);
}
float Ultra::getDistanceDownBack()
{
    m_downBack->GetRangeInches();
}
float Ultra::getDistanceDownFront()
{
    m_downFront->GetRangeInches();
}