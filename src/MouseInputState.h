//
// Created by Carlo Baretta on 07/08/2025.
//

#ifndef MOUSEINPUT_H
#define MOUSEINPUT_H

typedef struct MouseInputState {
    double lastX;
    double lastY;
    float yaw;
    float pitch;
    bool firstFrame;
    float sensitivity;
    bool rotationChanged;
} MouseInputState;

#endif //MOUSEINPUT_H
