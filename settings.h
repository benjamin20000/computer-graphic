#ifndef SETTINGS_H
#define SETTINGS_H

// Camera properties
extern float cameraX;
extern float cameraY;
extern float cameraZ;
extern float cameraAngleX;

// Robot properties
extern float robotAngle;
extern float robotX;
extern float robotZ;
extern float robotDistance;

// Floor size and cube properties
const int floorSize = 40;
const float cubeSize = 3.0f;
const float cubeX = 5.0f, cubeY = 4.0f, cubeZ = -10.0f;

// Sphere properties
const float sphereX = -15.0f, sphereY = 2.0f, sphereZ = 20.0f, sphereRadius = 5.0f;

// Robot size
const float robotRadius = 2.0f;

extern float lightPower;

#endif // SETTINGS_H
