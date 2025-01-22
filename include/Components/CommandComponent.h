#pragma once

#include "ECS/Component.h"
#include "Components/DirectionComponent.h"

// #include <vector>
#include <optional>
#include <queue>




enum class CommandType{
    None,
    BasicAttack,
    SpecialAttack,
    Cast,
    Shoot
};

struct Command{
    CommandType commandType = CommandType::None;
    Direction direction = {0, 0};
    bool doubleTap = false;
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
        return {CommandType::None, {0, 0}, false}; // 빈 이벤트 반환
    }

    std::queue<Command> commands;
};


