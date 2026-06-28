# luminogotchi

a robotic desk lamp inspired by jacob jacobsen's original luxo l-1 — a statement piece that's both functional as a desk lamp and brings
tamagotchi-like personality to any space.

in v1, emotions and behaviors are entirely hardcoded state machines rather
than ai-driven — keeping the project cost-free, offline, and fast to respond.
servo-driven joints animate the arm, while the lampshade itself doubles as a
capacitive touch sensor, letting the lamp react when you interact with it.
an esp32 runs the whole show.

built for hack club stardance.

## hardware

- esp32 dev board
- 4x mg996r servos (base, lower arm, mid arm, head)
- steel rods for the arm structure
- aluminium lampshade (also acts as a touch sensor)
- warm white led

## software

firmware is in `firmware/Luminogotchi/`, written for the arduino ide.

- `motion.h` / `motion.cpp` — servo control, easing, named poses
- `touch.h` / `touch.cpp` — capacitive touch sensing
- `mood.h` / `mood.cpp` — personality/state engine (coming soon)

### setup

1. install `esp32servo` via the arduino library manager
2. copy `secrets.example.h` to `secrets.h` and add your wifi credentials
3. open `Luminogotchi.ino` and flash to your esp32

## v2 ideas

- gesture recognition via camera
- spring-assisted joints
- wake-up animation on boot

## license

mit
