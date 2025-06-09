#include "DeltaTime.h"

float deltaTime = 0.0f;
static float lastFrame = 0.0f;

void UpdateDeltaTime(float time) {
  float currentFrame = static_cast<float>(time);
  deltaTime = currentFrame - lastFrame;

  if (deltaTime > 0.1f) deltaTime = 0.1f;

  lastFrame = currentFrame;
}
