#pragma once


class GameManager {


public:

	int currentHour;
	int currentMinute;
	int currentRound;

	std::size_t playerId;
	bool isGameover = false;

};