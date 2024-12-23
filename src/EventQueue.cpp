#include "EventQueue.h"

void EventQueue::push(const Event& event) {
    events.push(event);
}

Event EventQueue::pop() {
    if (!events.empty()) {
        Event event = events.front();
        events.pop();
        return event;
    }
    return {"", 0, ""}; // 빈 이벤트 반환
}

bool EventQueue::isEmpty() const {
    return events.empty();
}