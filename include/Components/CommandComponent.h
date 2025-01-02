#pragma once

#include "ECS/Component.h"
#include "Components/DirectionComponent.h"

// #include <vector>
#include <optional>




enum class CommandType{
    None,
    Move,
    Run,
    Attack,
    Skill
};


struct CommandData{
    CommandType type = CommandType::None;
    Direction moveDirection;
    std::optional<std::string> skillName;
    
};





class CommandComponent : public Component {

public:
    // std::vector<CommandData> commandDatas;

    CommandData commandData;

    // CommandComponent(CommandType type, Vector2D moveDirection) {
    //      commandData.type = type;
    //      commandData.moveDirection = moveDirection;

    // }

};


