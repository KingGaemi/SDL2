#pragma once

#include "Events/EventQueue.h"


#include <queue>
#include <mutex>




class EventManager {

public:
	void pushEvent(const Event& event){
		std::lock_guard<std::mutex> lock(mtx);
		eventQueue.push(event);
	}

	bool pollEvent(Event& outEvent) {
		std::lock_guard<std::mutex> lock(mtx);
		if(eventQueue.empty()) return false;
		outEvent = eventQueue.front();
		eventQueue.pop();

		return true;
	}

	EventManager* get(){
		return this;
	}

private:
	std::queue<Event> eventQueue;
	std::mutex mtx;
};