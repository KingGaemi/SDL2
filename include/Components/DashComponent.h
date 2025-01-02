#pragma once
#include "ECS/Component.h"
#include "KeyCode.h"

class DashComponent : public Component {
public:
    float maxDoubleTapTime;
    float currentTime;
    // float keyUpTime;

    KeyCode lastArrowKey;

    bool isDashing;            // 실제로 대쉬 중인지 여부
    
    DashComponent();
    DashComponent(float maxTime) : maxDoubleTapTime{maxTime} {}


    void pressed(KeyCode keyCode) {

        // if(keyCode == KeyCode::Left) lastDirection.hDir = -1;
        // if(keyCode == KeyCode::Right) lastDirection.hDir = 1;
        // if(keyCode == KeyCode::Up) lastDirection.vDir = -1;
        // if(keyCode == KeyCode::Down) lastDirection.vDir = 1;

        lastArrowKey = keyCode;

        currentTime = maxDoubleTapTime;
    }   

    KeyCode getLastKeyCode(){
        return lastArrowKey;
    }


};
