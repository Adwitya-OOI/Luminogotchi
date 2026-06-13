#ifndef MOTION_H
#define MOTION_H


// Pin definitions
const int pinBase  = 12;
const int pinLower = 13;
const int pinMid   = 14;
const int pinUpper = 15;

// Servo angle limits
const int baseMin  = 20;
const int baseMax  = 160;
const int lowerMin = 30;
const int lowerMax = 150;
const int midMin   = 30;
const int midMax   = 150;
const int upperMin = 20;
const int upperMax = 160;

// Easing types
enum EaseType {
  linear,
  easeIn,
  easeOut,
  easeInOut
};

// Pose definition
struct Pose {
  int base;
  int lower;
  int mid;
  int head;
};

// Initialisation function
void initMotion();

// Move to a target pose over `duration` ms, using the given easing curve
void motionMoveToPose(Pose targetPose, int duration, EaseType ease = easeInOut);

// Returns the current pose (last position written to servos)
Pose motionGetCurrentPose();

// Returns true if the current pose is (close to) neutral
bool motionIsNeutral();

// Named poses
extern const Pose neutralPose;
extern const Pose happyPose;
extern const Pose sadPose;
extern const Pose alertPose;
extern const Pose sleepPose;
extern const Pose excitedPose;
extern const Pose lookLeftPose;
extern const Pose lookRightPose;

#endif
//