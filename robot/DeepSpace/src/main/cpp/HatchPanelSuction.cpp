#include <HatchPanelSuction.h>

HatchPanelSuction::HatchPanelSuction()
{}

void HatchPanelSuction::SetHatchPanelSuction(bool engage)
{
    if(engage)
    {
        leftSol->Set(true);
        rightSol->Set(true);
    } else {
        leftSol->Set(false);
        rightSol->Set(false);
    }
}