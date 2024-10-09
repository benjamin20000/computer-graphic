#include <GL/glut.h>
#include <cstring>
#include "settings.h"

// Function to switch to 2D rendering
void switchTo2D() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);  // Set up a 2D orthographic projection (window size dependent)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to render bitmap text at a specified position
void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);  // Position where the text will be rendered
    while (*string) {
        glutBitmapCharacter(font, *string);  // Draw each character
        string++;
    }
}

// Function to draw a button with specified coordinates, dimensions, and text
void drawButton(float x, float y, float width, float height, const char* text) {
    // Draw the button rectangle with a white color
    glColor3f(1.0f, 1.0f, 1.0f);  // Button color (white)
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // Set text color to black
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Calculate the position to center the text on the button
    float textX = x + (width / 2) - float((strlen(text) * 4));  // Adjust horizontal centering
    float textY = float(y + (height / 2) - 10);                 // Adjust vertical centering
    renderBitmapString(textX, textY, GLUT_BITMAP_HELVETICA_18, text);  // Render the button text
}

// Function to detect if the button was clicked based on mouse coordinates
bool isButtonClicked(float mouseX, float mouseY, float x, float y, float width, float height) {
    return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
}

// Mouse callback function to handle button clicks
void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Invert y-coordinate since GLUT's origin is at the top-left corner
        float mouseX = float(x);
        float mouseY = float(600 - y);  // Adjust based on your window height (600 in this case)

        // Define button coordinates and dimensions
        float buttonX1 = 0.0f, buttonY1 = 110.0f, buttonWidth1 = 50.0f, buttonHeight1 = 50.0f;
        float buttonX2 = 0.0f, buttonY2 = 55.0f, buttonWidth2 = 50.0f, buttonHeight2 = 50.0f;
        float buttonX3 = 0.0f, buttonY3 = 0.0f, buttonWidth3 = 50.0f, buttonHeight3 = 50.0f;

        // Check if the mouse click is within the first button's bounds
        if (isButtonClicked(mouseX, mouseY, buttonX1, buttonY1, buttonWidth1, buttonHeight1)) {
            lightPower = 1.0f;  // Action for first button (example: turn on the light)
        }

        // Check if the mouse click is within the second button's bounds
        else if (isButtonClicked(mouseX, mouseY, buttonX2, buttonY2, buttonWidth2, buttonHeight2)) {
            lightPower = 0.0f;  // Action for second button (example: turn off the light)
        }

        // Check if the mouse click is within the third button's bounds
        else if (isButtonClicked(mouseX, mouseY, buttonX3, buttonY3, buttonWidth3, buttonHeight3)) {
            exit(0);  // Action for third button (example: exit the application)
        }
    }
    glutPostRedisplay();  // Redraw the scene after mouse action
}
