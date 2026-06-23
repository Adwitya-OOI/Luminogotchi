#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

// T0, T8, T9 — picked these because they don't overlap with servo pins (12-15)
const int pinTouchShade = 4;
const int pinTouchBase  = 33;
const int pinTouchArm   = 32;

// 40 worked on my desk but the shade reads higher than the foil strips
// TODO: per-zone thresholds once everything is wired up properly
const int touchThreshold = 40;

const int holdThreshold = 600;  // ms — feels natural for "intentional hold"
const int petWindow     = 500;  // ms between taps to count as a sequence
const int petTapCount   = 3;

enum TouchZone {
  zoneShade,
  zoneBase,
  zoneArm
};

enum TouchType {
  touchNone,
  touchTap,
  touchHold,
  touchPet
};

void initTouch();
void updateTouch();
TouchType readTouch(TouchZone zone);

#endif
