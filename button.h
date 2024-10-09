#ifndef BUTTON_H
#define BUTTON_H

void switchTo2D();
void renderBitmapString(float x, float y, void *font, const char *string);
void drawButton(float x, float y, float width, float height, const char* text);
bool isButtonClicked(float mouseX, float mouseY, float x, float y, float width, float height);
void mouseCallback(int button, int state, int x, int y);

#endif // BUTTON_H
