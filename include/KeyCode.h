#pragma once

// 게임에서 사용하는 추상화된 키 코드 열거형
enum class KeyCode {
    Unknown,
    Enter,
    Escape,
    Left,
    Right,
    Up,
    Down,
    Space,
    NUM_OF_KEY_CODES,
    Key_1,
    Key_2
    // 필요한 키 추가...
};

constexpr int toInt(KeyCode key) {
    return static_cast<int>(key);
}
