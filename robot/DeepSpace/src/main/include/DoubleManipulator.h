/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once


class DoubleManipulator {
  private:
    int currentPosition = 0;
    bool pickingUp = false;
 public:
  DoubleManipulator();
  void Init();
  void RotateWrist(int position);
  void SpinWheels(double motorSpeed);
  void GrabPanel();
  void ReleasePanel();
  void IncrementPosition();
  void SetBallPickup(bool value);
  bool CheckBallPickup();
};
