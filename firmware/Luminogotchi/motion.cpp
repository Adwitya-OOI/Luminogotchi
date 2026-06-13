#include "motion.h"
#include <math.h>

// servo objects
Servo servoBase;
Servo servoLower;
Servo servoMid;
Servo servoUpper;

// Named poses
const Pose neutralPose  = {90, 90, 90, 90};
const Pose happyPose    = {90, lowerMax - 20, midMax - 20, headMax - 15};
const Pose sadPose      = {90, lowerMin + 10, midMin + 10, headMin + 5};
const Pose alertPose    = {90, lowerMax - 5,  midMax - 10, headMax - 10};
const Pose sleepPose    = {90, lowerMin + 15, midMin + 5,  headMin};
const Pose excitedPose  = {90, lowerMax,      midMax - 5,  headMax};
const Pose lookLeftPose  = {baseMin + 10, 90, 90, headMin + 20};
const Pose lookRightPose = {baseMax - 10, 90, 90, headMin + 20};

// track arm - must come AFTER neutralPose is defined above
static Pose currentPose = neutralPose;

// Easing function curves
static float linearCurve(float t) {
  return t;
}
static float easeInCurve(float t) {
  return t * t * t;
}
static float easeOutCurve(float t) {
  return t * (2 - t);
}
static float easeInOutCurve(float t) {
  return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

// Easing function dispatcher
float ease(EaseType type, float t) {
  switch (type) {
    case linear:    return linearCurve(t);
    case easeIn:    return easeInCurve(t);
    case easeOut:   return easeOutCurve(t);
    case easeInOut: return easeInOutCurve(t);
    default:        return t;
  }
}

// setup function to attach servos
void initMotion() {
  servoBase.attach(pinBase, 500, 2400);
  servoLower.attach(pinLower, 500, 2400);
  servoMid.attach(pinMid, 500, 2400);
  servoUpper.attach(pinUpper, 500, 2400);

  servoBase.write(neutralPose.base);
  servoLower.write(neutralPose.lower);
  servoMid.write(neutralPose.mid);
  servoUpper.write(neutralPose.head);

  delay(500); // wait for servos to physically reach neutral
}

// move to a target pose,using the given easing curve
void motionMoveToPose(Pose targetPose, int duration, EaseType easeType) {
  Pose startPose = currentPose;
  unsigned long startTime = millis();
  unsigned long endTime = startTime+duration;

  while (millis()<endTime) {
    float t = (float)(millis()-startTime)/duration;
    float easedT = ease(easeType, t);

    // interpolate each servo angle
    int baseAngle  = startPose.base+easedT*(targetPose.base-startPose.base);
    int lowerAngle = startPose.lower+easedT*(targetPose.lower-startPose.lower);
    int midAngle   = startPose.mid+easedT*(targetPose.mid-startPose.mid);
    int headAngle  = startPose.head+easedT*(targetPose.head-startPose.head);

    // clamp to safe servo ranges before writing
    baseAngle  = constrain(baseAngle,  baseMin,  baseMax);
    lowerAngle = constrain(lowerAngle, lowerMin, lowerMax);
    midAngle   = constrain(midAngle,   midMin,   midMax);
    headAngle  = constrain(headAngle,  upperMin, upperMax);

    servoBase.write(baseAngle);
    servoLower.write(lowerAngle);
    servoMid.write(midAngle);
    servoUpper.write(headAngle);

    delay(20); // small delay for smooth movement
  }

  // ensure final position is set exactly (loop may exit slightly early)
  servoBase.write(targetPose.base);
  servoLower.write(targetPose.lower);
  servoMid.write(targetPose.mid);
  servoUpper.write(targetPose.head);

  currentPose = targetPose; // update current pose
}

// Returns the current pose (last position written to servos)
Pose motionGetCurrentPose() {
  return currentPose;
}

// Returns true if the current pose is (close to) neutral
bool motionIsNeutral() {
  const int threshold = 10; // allow some tolerance
  return abs(currentPose.base  - neutralPose.base)  < threshold &&
         abs(currentPose.lower - neutralPose.lower) < threshold &&
         abs(currentPose.mid   - neutralPose.mid)   < threshold &&
         abs(currentPose.head  - neutralPose.head)  < threshold;
}