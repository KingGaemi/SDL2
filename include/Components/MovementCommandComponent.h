#pragma once

#include "ECS/Component.h"
#include "Components/DirectionComponent.h"

// #include <vector>
#include <optional>




// struct MovementCommandData{
//     // CommandType type = CommandType::None;
//     Direction moveDirection;
//     // std::optional<std::string> skillName;
    
// };

enum class MovementCommandType{
    Hold,
    Stop,
    Move,
    GoForward,
    Spin
};





class MovementCommandComponent : public Component {

public:
    // std::vector<CommandData> commandDatas;
    MovementCommandComponent(MovementCommandType type) : moveCommandType(type) {}
    MovementCommandType moveCommandType;
    Direction direction = {0, 0};
    bool doubleTap = false;

    // CommandComponent(CommandType type, Vector2D moveDirection) {
    //      commandData.type = type;
    //      commandData.moveDirection = moveDirection;

    // }

};


