#include <GL/glut.h>
#include"settings.h"

// Function to initialize lighting
void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  // Enable Light 0 (front)
    glEnable(GL_LIGHT1);  // Enable Light 1 (back)

    // Set ambient light
    GLfloat ambientLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };  // Higher ambient light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Light 0 (front light)
    GLfloat diffuseLight0[] = { lightPower, lightPower, lightPower, 1.0f }; 
    GLfloat lightPos0[] = { 0.0f, 10.0f, -40.0f, 1.0f  };  // Positioned above the scene
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    // Light 1 (back light)
    GLfloat diffuseLight1[] = { lightPower, lightPower, lightPower, 1.0f };  
    GLfloat lightPos1[] = { 0.0f, 10.0f, 40.0f, 1.0f };  // Positioned behind the camera
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    // Set material properties for the floor
    GLfloat floorMaterial[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorMaterial);
}

// Function to draw the floor
void drawFloor() {
    // Set material properties for the floor
    GLfloat floorMaterial[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // Bright green diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, floorMaterial);

    // Set ambient light color (optional)
    GLfloat floorAmbientMaterial[] = { 0.0f, 0.5f, 0.0f, 1.0f }; // Darker green for ambient
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, floorAmbientMaterial);

    glBegin(GL_QUADS);
    for (int x = -floorSize; x < floorSize; x++) {
        for (int z = -floorSize; z < floorSize; z++) {
            if ((x + z) % 2 == 0) {
                glColor3f(0.2f, 0.8f, 0.2f); // Lighter green
            } else {
                glColor3f(0.0f, 0.5f, 0.0f); // Darker green
            }

            glVertex3f((GLfloat)x, 0.0f, (GLfloat)z);
            glVertex3f((GLfloat)(x + 1), 0.0f, (GLfloat)z);
            glVertex3f((GLfloat)(x + 1), 0.0f, (GLfloat)(z + 1));
            glVertex3f((GLfloat)x, 0.0f, (GLfloat)(z + 1));
        }
    }
    glEnd();
}



void drawCube(float x, float y, float z, float size) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Define the material properties for the cube
    GLfloat cubeDiffuseMaterial[] = { 1.0f, 0.0f, 0.0f, 1.0f };  // Red diffuse color
    GLfloat cubeAmbientMaterial[] = { 0.5f, 0.0f, 0.0f, 1.0f };  // Darker red for ambient
    GLfloat cubeSpecularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // White specular highlights
    GLfloat cubeShininess[] = { 50.0f };  // Shininess factor

    // Set material properties
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cubeDiffuseMaterial);
    glMaterialfv(GL_FRONT, GL_AMBIENT, cubeAmbientMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cubeSpecularMaterial);
    glMaterialfv(GL_FRONT, GL_SHININESS, cubeShininess);

    glutSolidCube(size); // Use a filled cube

    glPopMatrix();
}

void drawMetallicSphere(float x, float y, float z, float radius) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Define the material properties for the metallic sphere
    GLfloat sphereDiffuseMaterial[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // Light gray diffuse color
    GLfloat sphereAmbientMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // Darker gray for ambient
    GLfloat sphereSpecularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // White specular highlights
    GLfloat sphereShininess[] = { 100.0f };  // High shininess factor for a metallic look

    // Set material properties
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sphereDiffuseMaterial);
    glMaterialfv(GL_FRONT, GL_AMBIENT, sphereAmbientMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sphereSpecularMaterial);
    glMaterialfv(GL_FRONT, GL_SHININESS, sphereShininess);

    // Draw the metallic sphere
    glutSolidSphere(radius, 20, 20); // Use a filled sphere

    glPopMatrix();
}



// Function to draw a cylinder for the robot's limbs
void drawCylinder(float baseRadius, float topRadius, float height) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, baseRadius, topRadius, height, 20, 20);
    gluDeleteQuadric(quad);
}


// Function to draw the robot with blue color, accepting a rotation angle
void drawRobot(float x, float y, float z, float angle) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Apply rotation using the passed angle
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rotate around the Y-axis (yaw)

    // Disable lighting to set a flat color for the robot
    glDisable(GL_LIGHTING);
    
    // Set the color for the robot
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color

    // Draw the body
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f); // Position the body above the floor
    glScalef(1.5f, 2.5f, 1.0f); // Scale the cube to make it taller for the body
    drawCube(0.0f, 0.0f, 0.0f, 2.0f); // Main body as a cube
    glPopMatrix();

    // Draw the head
    glPushMatrix();
    glTranslatef(0.0f, 8.5f, 0.0f); // Position above the body
    drawCube(0.0f, 0.0f, 0.0f, 1.5f); // Smaller cube for the head
    glPopMatrix();

    // Draw the left arm
    glPushMatrix();
    glTranslatef(-2.5f, 6.0f, 0.0f); // Left side of the body
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate for a vertical arm
    drawCylinder(0.3f, 0.3f, 2.0f); // Arm as a cylinder
    glPopMatrix();

    // Draw the right arm
    glPushMatrix();
    glTranslatef(2.5f, 6.0f, 0.0f); // Right side of the body
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate for a vertical arm
    drawCylinder(0.3f, 0.3f, 2.0f); // Arm as a cylinder
    glPopMatrix();

    // Draw the left leg
    glPushMatrix();
    glTranslatef(-0.7f, 2.0f, 0.0f); // Left leg, positioned below the body
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate for vertical leg
    drawCylinder(0.5f, 0.5f, 3.0f); // Leg as a thicker cylinder
    glPopMatrix();

    // Draw the right leg
    glPushMatrix();
    glTranslatef(0.7f, 2.0f, 0.0f); // Right leg
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate for vertical leg
    drawCylinder(0.5f, 0.5f, 3.0f); // Leg as a thicker cylinder
    glPopMatrix();

    glPopMatrix();
    
    // Re-enable lighting if you need it for other objects
    glEnable(GL_LIGHTING);
}