#pragma once
#include "Manager/GameManager.h"

class ClickCommand {
public:
    virtual void execute() = 0;
    virtual ~ClickCommand() = default;
};

// 예제: 엔티티가 "문을 열기" 동작을 수행하는 커맨드
class PlayGameCommand : public ClickCommand {
public:

    PlayGameCommand(std::shared_ptr<GameManager>& gameManager) : gameManager(gameManager) {}

    void execute() override {
        if(gameManager) {
            gameManager->gameStart();
            std::cout << "Game Start" << std::endl;
        }else{
            std::cout << "gameManager is nullptr" << std::endl;
        }


        // 실제 문 열기 로직 실행
    }
private:
    std::shared_ptr<GameManager> gameManager;
};

class SelectCharacterCommand : public ClickCommand {
public:

    SelectCharacterCommand(std::shared_ptr<GameManager>& gameManager) : gameManager(gameManager) {}

    void execute() override {
        if(gameManager) {
            gameManager->goSelectScene();
           
        }else{
            std::cout << "gameManager is nullptr" << std::endl;
        }


        // 실제 문 열기 로직 실행
    }
private:
    std::shared_ptr<GameManager> gameManager;
};