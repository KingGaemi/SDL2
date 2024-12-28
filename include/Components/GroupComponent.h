// #pragma once
// #include "ECS/Component.h"
// #include <bitset>




// enum GroupIDs {
// 	// General Groups
// 	UI = 0,
// 	GameObject,
// 	Unit,
// 	Player,


// 	// Scene Groups
//     Scene_Menu,
//     Scene_Game,


//     // Team Groups
//     Team_Ally,
//     Team_Enemy,
//     Team_Nutral,


//     // Item Groups
//     Item_Consume,
//     Item_Equip

//     // ... 추가 그룹
// };


// class GroupComponent : public Component {


// public:


// 	bool hasGroup(GroupIDs groupID) const
// 	{
// 		return groupBitset.test(groupID);
// 	}

// 	void addGroup(GroupIDs groupID)
// 	{
// 		groupBitset.set(groupID);
// 	} 

// 	void delGroup(GroupIDs groupID)
// 	{
// 		 groupBitset.reset(groupID);
// 	}

// 	void printGroups() const {
//         for (std::size_t i = 0; i < groupBitSet.size(); ++i) {
//             if (groupBitset.test(i)) {
//                 std::cout << "Group " << i << " is active.\n";
//             }
//         }
//     }


// private:
// 	std::bitset<MAX_GROUPS> groupBitSet;
// }

