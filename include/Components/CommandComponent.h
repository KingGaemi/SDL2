#pragma once

#include "ECS/Component.h"
#include "Components/DirectionComponent.h"

// #include <vector>
#include <optional>




enum class CommandType{
    None,
    BasicAttack,
    SpecialAttack,
    Skill
};


// struct CommandData{
//     CommandType type = CommandType::None;
//     Direction direction;
//     std::optional<std::string> skillName;
// };





class CommandComponent : public Component {

public:
    // std::vector<CommandData> commandDatas;
    CommandType commandType = CommandType::None;
    Direction direction;
    bool doubleTap = false;
    std::optional<std::string> skillName;

    // CommandComponent(CommandType type, Vector2D moveDirection) {
    //      commandData.type = type;
    //      commandData.moveDirection = moveDirection;

    // }

};


