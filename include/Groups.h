#pragma once
#include "ECS/Component.h"
#include <string>

enum class TeamCode{
    Neutral,
    Ally,
    Enemy
};


enum class SceneCode{
    Global,
    Menu,
    Game,
    Pause,
    Select
};


class UITag : public Component{};
class TextTag : public Component{};
class PlayerTag : public Component{};
class Player2Tag : public Component{};
class HpBarTag: public Component{};
class IMGTag : public Component{};



class SceneTag : public Component{
public:
    SceneCode sceneCode;
    SceneTag(SceneCode sceneCode) : sceneCode(sceneCode) {}
};


class TeamTag : public Component{
public:
	TeamCode teamCode;
	TeamTag(TeamCode teamCode) : teamCode(teamCode) {}

    std::string getTeamString(){
        std::string teamString = "defaultTeam";
        if(teamCode == TeamCode::Enemy) teamString = "Enemy";
        else if(teamCode == TeamCode::Ally) teamString = "Ally";
        else if(teamCode == TeamCode::Neutral) teamString = "Neutral";

        return teamString;
    }
};