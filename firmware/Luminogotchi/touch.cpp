#include "touch.h"

struct ZoneState {
  bool          isTouched;
  unsigned long touchStartTime;
  int           tapCount;
  unsigned long lastTapTime;
  TouchType     pending;
};

static ZoneState zones[3] = {
  {false, 0, 0, 0, touchNone},
  {false, 0, 0, 0, touchNone},
  {false, 0, 0, 0, touchNone}
};

static const int zonePins[3] = { pinTouchShade, pinTouchBase, pinTouchArm };

void initTouch() {
  // ESP32 touch pins need no setup, just printing raw values so I can
  // calibrate touchThreshold without guessing
  Serial.print("shade: "); Serial.println(touchRead(pinTouchShade));
  Serial.print("base:  "); Serial.println(touchRead(pinTouchBase));
  Serial.print("arm:   "); Serial.println(touchRead(pinTouchArm));
}

void updateTouch() {
  unsigned long now = millis();

  for (int i = 0; i < 3; i++) {
    ZoneState& z          = zones[i];
    bool currentlyTouched = (touchRead(zonePins[i]) < touchThreshold);

    if (currentlyTouched && !z.isTouched) {
      z.touchStartTime = now;
      z.isTouched      = true;
    }
    else if (!currentlyTouched && z.isTouched) {
      unsigned long heldFor = now - z.touchStartTime;
      z.isTouched           = false;

      if (heldFor > holdThreshold) {
        z.pending  = touchHold;
        z.tapCount = 0;
      } else {
        // count tap — reset sequence if gap was too long
        if (now - z.lastTapTime < (unsigned long)petWindow) {
          z.tapCount++;
        } else {
          z.tapCount = 1;
        }
        z.lastTapTime = now;

        if (z.tapCount >= petTapCount) {
          z.pending  = touchPet;
          z.tapCount = 0;
        } else {
          z.pending = touchTap;
        }
      }
    }
  }
}

TouchType readTouch(TouchZone zone) {
  TouchType result    = zones[zone].pending;
  zones[zone].pending = touchNone;
  return result;
}
