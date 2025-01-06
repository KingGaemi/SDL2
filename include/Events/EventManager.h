#pragma once

#include "Events/EventQueue.h"
#include <queue>
// #include <mutex>




class EventManager {

public:
	void pushEvent(const Event& event){
		// std::lock_guard<std::mutex> lock(mtx);
		eventQueue.push(event);
	}

	void pushBigEvent(const Event& event){
		bigEventQueue.push(event);
	}

	void pushMiddleEvent(const Event& event){
		middleEventQueue.push(event);
	}


	bool pollEvent(Event& outEvent) {
		// std::lock_guard<std::mutex> lock(mtx);
		if(eventQueue.empty()) return false;
		outEvent = eventQueue.front();
		eventQueue.pop();

		return true;
	}

	bool pollMiddleEvent(Event& outEvent){

		if(middleEventQueue.empty()) return false;
		outEvent = middleEventQueue.front();
		middleEventQueue.pop();

		return true;
	}

	bool pollBigEvent(Event& outEvent) {

		if(bigEventQueue.empty()) return false;
		outEvent = bigEventQueue.front();
		bigEventQueue.pop();

		return true;
	}


	EventManager* get(){
		return this;
	}

private:
	std::queue<Event> eventQueue;
	std::queue<Event> bigEventQueue;
	std::queue<Event> middleEventQueue;
	// std::mutex mtx;
};