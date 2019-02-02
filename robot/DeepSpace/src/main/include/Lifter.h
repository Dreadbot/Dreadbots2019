/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#pragma once
#include "frc/WPILib.h"
#include "ctre/Phoenix.h"
  
class Lifter 
{
  private:
    int currentLiftLevel = 0;
  public:
    Lifter();
    void SetLift(int level);
    void LiftInit();
    int GetEncoderPosition();
    void MoveLift(double motorSpeed);
    int CheckHeight();
    void IncreaseCurrentLevel();
    void DecreaseCurrentLevel();
    int GetCurrentLevel();
    int InchesLift(float inches);
    
};