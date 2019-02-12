// Functions used to align with hatch panel and place automatically

#include "Robot.h"
#include "frc/WPILib.h"
#include "AutoHatchPanel.h"
#include "Drive.h"

AutoHatchPanel::AutoHatchPanel() {}

void AutoHatchPanel::alignToTarget() {

}

void AutoHatchPanel::driveToTarget() {}

void AutoHatchPanel::placePanel(int level) {
    lifter.SetLift(level);
    suction.SetHatchPanelSuction(false);
}

void AutoHatchPanel::GrabPanel() {
    if(lifter.GetCurrentLevel() > 0) {
        lifter.SetLift(0);
    }

    suction.SetHatchPanelSuction(true);
}

