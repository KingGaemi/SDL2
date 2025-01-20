// #pragma once

// #include "ECS/Component.h"

// #include <memory>

// enum ActionType
// {
// 	Attack,
// 	Cast,
// 	Throw,
// 	None
	
// };

// struct Action{
// 	ActionType actionType;
// 	std::string actionName;
// 	std::size_t casterId;
// 	std::size_t actionId;
// };



// class ActionComponent : public Component {

// public:

// 	void push(Action action){
// 		actions.push(action);
// 	}
// 	Action pop() {
//         if (!actions.empty()) {
//             Action action = actions.front();
//             actions.pop();
//             return action;
//         }
//         return {ActionType::None, "None", 0, 0}; // 빈 이벤트 반환
//     }

// private:
// 	std::queue<Action> actions;


// };