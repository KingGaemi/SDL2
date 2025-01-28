#pragma once

#include "ECS/Component.h"
#include "Components/DirectionComponent.h"

// #include <vector>
#include <optional>
#include <queue>




enum class ActionCommandType{
    None,
    BasicAttack,
    SpecialAttack,
    Cast,
    Shoot
};
enum class MovementCommandType{
    Hold,
    Stop,
    Move
};


struct Command{
    ActionCommandType actionCommandType = ActionCommandType::None;
    MovementCommandType moveCommandType = MovementCommandType::Hold;
    Direction actionDir = {0, 0};
    Direction moveDir = {0, 0};
    bool actionDoubleTap = false;
    bool moveDoubleTap = false;
    int abilityNumber = 0;
};


class CommandComponent : public Component {

public:

    void push(Command command){
        commands.push(command);
    }

    Command pop() {
        if (!commands.empty()) {
            Command command = commands.front();
            commands.pop();
            return command;
        }
        return {ActionCommandType::None, MovementCommandType::Hold, {0, 0}, {0, 0}, false, false, 0}; // 빈 이벤트 반환
    }

    std::queue<Command> commands;
};


