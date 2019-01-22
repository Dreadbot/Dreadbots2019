#include <Stilts.h>
#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

Stilts::Stilts(TalonSRX& driveMotor, TalonSRX& backMotor, TalonSRX& frontMotor) : m_backMotor(backMotor), m_driveMotor(driveMotor), m_frontMotor(frontMotor)
{

}