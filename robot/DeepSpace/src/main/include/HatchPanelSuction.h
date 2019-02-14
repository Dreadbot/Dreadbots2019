#include <frc/WPILib.h>

class HatchPanelSuction
{
    public:
        HatchPanelSuction();
        void SetHatchPanelSuction(bool engage);
    private:
        frc::Solenoid leftSol{0};
        frc::Solenoid rightSol{1};
};