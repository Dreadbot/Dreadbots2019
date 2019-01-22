#pragma

#include <frc/WPILib.h>
#include <ctre/Phoenix.h>

class Stilts
{
    public:
        Stilts();
        void setFrontToHeight(float heigt);//Height in inches
        void setBackToHeight(float height);//Height in inches
        void driveWheels(float speed);//Speed from -1 to 1

}