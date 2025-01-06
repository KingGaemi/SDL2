#pragma once

#include "ECS/Component.h"

enum class TeamCode{
    Neutral,
    Ally,
    Enemy
};


enum class SceneCode{
    Global,
    Menu,
    Game,
    Pause
};


class UITag : public Component{};
class TextTag : public Component{};
class PlayerTag : public Component{};
class Player2Tag : public Component{};
class IMGTag : public Component{};



class SceneTag : public Component{
public:
    SceneCode sceneCode = SceneCode::Global;
    SceneTag();
    SceneTag(SceneCode sceneCode) : sceneCode(sceneCode) {}
};


class TeamComponent : public Component{
public:
	TeamCode teamCode = TeamCode::Neutral;
	TeamComponent(TeamCode teamCode) : teamCode(teamCode) {}
};