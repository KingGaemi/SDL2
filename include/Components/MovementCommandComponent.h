#pragma once

#include "ECS/Component.h"
#include "Components/DirectionComponent.h"

#include <queue>
#include <optional>





// struct MovementCommandData{
//     // CommandType type = CommandType::None;
//     Direction moveDirection;
//     // std::optional<std::string> skillName;
    
// };

enum class MovementCommandType{
    Hold,
    Stop,
    MoveToDirection,
    GoForward,
    Spin,
    Impulse
};

struct MovementCommand{
    MovementCommandType moveCommandType = MovementCommandType::Stop;
    Direction direction = {0, 0};
    float radian = 0.0f;
    bool doubleTap = false;
    int abilityNumber = 0;
    bool isClockwise = true;
    bool stopSpin = false;
};





class MovementCommandComponent : public Component {

public:
    // std::vector<CommandData> commandDatas;
    MovementCommandComponent(MovementCommandType type){
        MovementCommand moveCommand;
        moveCommand.moveCommandType = type;
        moveCommands.push(moveCommand);
    }

    void push(MovementCommand moveCommand){
        moveCommands.push(moveCommand);
    }

    bool pop(MovementCommand& moveCommand) {
        if (!moveCommands.empty()) {
            moveCommand = moveCommands.front();
            moveCommands.pop();
            return true;
        }
        return false; // 빈 이벤트 반환
    }

    std::queue<MovementCommand> moveCommands;
};


