#include <GL/glut.h>
#include <cmath>
#include "settings.h"

// Function to check for collisions with objects (cube, sphere, or boundaries)
bool checkCollision(float x, float z) {
    // Collision with the cube
    if (x > cubeX - (cubeSize / 2 + robotRadius) && x < cubeX + (cubeSize / 2 + robotRadius) &&
        z > cubeZ - (cubeSize / 2 + robotRadius) && z < cubeZ + (cubeSize / 2 + robotRadius)) {
        return true;
    }

    // Collision with the sphere
    float dx = x - sphereX;
    float dz = z - sphereZ;
    if (sqrt(dx * dx + dz * dz) < (sphereRadius + robotRadius)) {
        return true;
    }

    // Collision with the floor boundaries
    if (x < -floorSize + robotRadius || x > floorSize - robotRadius ||
        z < -floorSize + robotRadius || z > floorSize - robotRadius) {
        return true;
    }

    return false;
}

// Function to update robot position based on camera movement and handle collision
void updateRobotPosition() {
    float newRobotX = float(cameraX + robotDistance * sin(cameraAngleX));
    float newRobotZ = float(cameraZ - robotDistance * cos(cameraAngleX));
    
    // Update position if no collision occurs
    if (!checkCollision(newRobotX, newRobotZ)) {
        robotX = newRobotX;
        robotZ = newRobotZ;
    } else {
        // Adjust robotDistance to avoid collision
        for (float testDistance = robotDistance; testDistance > 0; testDistance -= 0.1f) {
            newRobotX = float(cameraX + testDistance * sin(cameraAngleX));
            newRobotZ = float(cameraZ - testDistance * cos(cameraAngleX));
            if (!checkCollision(newRobotX, newRobotZ)) {
                robotX = newRobotX;
                robotZ = newRobotZ;
                robotDistance = testDistance;
                break;
            }
        }
    }

    // Calculate robot rotation based on camera position
    float dx = cameraX - robotX;
    float dz = cameraZ - robotZ;
    robotAngle = float(atan2(dx, dz) * (180.0f / M_PI));
}

// Function to handle keyboard inputs for movement
void keyboard(int key, int x, int y) {
    const float moveSpeed = 2.0f;       // Speed of camera movement
    const float angleSpeed = 0.05f;     // Speed of camera rotation

    float newCameraX = cameraX;
    float newCameraZ = cameraZ;

    // Handle movement or rotation based on arrow key input
    switch (key) {
        case GLUT_KEY_LEFT:
            cameraAngleX -= angleSpeed;  // Rotate camera left
            break;
        case GLUT_KEY_RIGHT:
            cameraAngleX += angleSpeed;  // Rotate camera right
            break;
        case GLUT_KEY_UP:
            newCameraX += float(moveSpeed * sin(cameraAngleX)); // Move camera forward
            newCameraZ -= float(moveSpeed * cos(cameraAngleX));
            break;
        case GLUT_KEY_DOWN:
            newCameraX -= float(moveSpeed * sin(cameraAngleX)); // Move camera backward
            newCameraZ += float(moveSpeed * cos(cameraAngleX));
            break;
    }

    // Check for collisions with new camera and robot positions
    float testRobotX = float(newCameraX + robotDistance * sin(cameraAngleX));
    float testRobotZ = float(newCameraZ - robotDistance * cos(cameraAngleX));

    if (!checkCollision(testRobotX, testRobotZ)) {
        cameraX = newCameraX;  // Update camera position
        cameraZ = newCameraZ;
        updateRobotPosition(); // Update robot position
    }

    glutPostRedisplay(); // Redraw the scene
}

// Function to adjust the viewport and projection when the window is resized
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);  // Set perspective projection
    glMatrixMode(GL_MODELVIEW);
}
