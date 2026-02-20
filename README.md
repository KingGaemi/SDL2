Physics 2D Platformer (SDL2)

소개 (Introduction)
Physics 2D Platformer는 SDL2와 Box2D를 사용하여 개발한 2D 액션 플랫포머 게임입니다 (제목 미정).
Entity-Component-System (ECS) 아키텍처를 기반으로, 확장성과 유지보수성을 고려하여 제작되었습니다.

Physics 2D Platformer is a 2D action platformer developed using SDL2 and Box2D (Title TBD).
Built on an Entity-Component-System (ECS) architecture, it is designed with a strong focus on scalability and maintainability.


주요 특징 (Key Features)
SDL2 기반 렌더링 및 입력 처리
(SDL2-based rendering and input handling)

Box2D 기반 2D 물리 시뮬레이션
(Box2D-based 2D physics simulation)

Entity-Component-System (ECS) 구조 적용
(Entity-Component-System (ECS) architecture)

EventManager를 통한 유연한 이벤트 처리
(Flexible event handling via EventManager)

SceneManager를 통한 씬 전환 관리
(Scene transition management via SceneManager)

JSON 파일 기반 데이터 드리븐 엔티티 구성
(Data-driven entity configuration using JSON files)

Tiled 외부 툴을 이용해 제작된 맵 (.tmx) 파일 로드 기능 구현
(Map loading feature for .tmx files created with Tiled)

Aseprite 외부 툴을 이용하여 제작된 스프라이트 시트 & 애니메이션 로드 기능 구현
(Sprite sheet and animation loading functionality for assets created with Aseprite)




사용 기술 (Tech Stack)
Language: C++

Libraries/Tools: SDL2, Box2D, nlohmann/json


엔티티 생성 로직 (Entity Spawning Logic)
SpawnRequest를 통해 엔티티의 타입, 이름, 좌표, 크기 등 간단한 데이터를 직접 할당해준 뒤 ecsManager의 pendingSpawn 큐에 푸쉬합니다 (ecsManager를 호출할 수 있으면 어디서든 가능).

Allocate basic data (entity type, name, coordinates, size) via SpawnRequest and push it to ecsManager's pendingSpawn queue. (This can be called from anywhere with access to ecsManager).

ecsManager는 EntityFactory에게 빈 엔티티 전달 후, 팩토리에서 엔티티의 타입과 이름을 경로 삼아 json 형태로 저장된 데이터를 기반으로 그 엔티티가 붙여야 할 컴포넌트(Component)들을 부착합니다.

ecsManager passes an empty entity to the EntityFactory. Using the entity's type and name as a directory path, the factory reads the stored JSON data and attaches the required Components to the entity.

마지막으로 Request에 담긴 지정 좌표와 크기 등, 유닛이 가진 고유값이 아닌 데이터를 부여합니다.

Finally, non-intrinsic data specified in the Request, such as target coordinates and size, are applied to the entity.

🚀 실행 방법 (How to Run)
2DPlatformer.exe 실행 파일을 실행합니다.
(Run the 2DPlatformer.exe executable.)

Game start를 클릭합니다.
(Click Game start.)

필요한 SDL2 관련 DLL 파일들은 함께 제공됩니다.
(Required SDL2-related DLL files are included in the repository.)

※ 추가 설치나 빌드 과정 없이 바로 실행 가능합니다.
(Note: The game can be played immediately without any additional installation or build process.)

Known Issue (재시작 기능 관련):
재시작 버튼은 씬 전환 시 부하가 쌓이는 문제로 현재 미구현 상태입니다. (메모리 Clear 과정 미흡 및 Map 로드 관련 이슈로 추정되며 개선 예정입니다.)
The Restart button is currently disabled due to performance overhead upon restarting. (Suspected to be related to incomplete memory clearance and map loading issues; planned for future refactoring.)




게임 플레이 방법 (How to Play)
이동 (Move): 키보드 화살표 키 (Arrow Keys)

대쉬 (Dash): 빠르게 같은 방향키를 두 번 누르기 (Double-tap an arrow key quickly)

근접 공격 (Melee Attack): 스페이스바 (Spacebar)

원거리 공격 (Shoot Arrow): Q 키 (Q key)

승리 및 패배 조건 (Win/Loss Conditions):

패배 (Defeat): 플레이어가 죽거나, 코어스톤이 파괴되면 패배합니다.
(You lose if the player dies or the Core Stone is destroyed.)

승리 (Victory): 북쪽에서 주기적으로 생성되는 고블린 무리를 막아내고, '고블린 킹'을 처치하면 스테이지가 클리어됩니다.
(Defend against the goblins spawning periodically from the north. Defeat the 'Goblin King' to clear the stage and win.)

아이템 (Items):

포션 (Potion): 획득 시 체력이 모두 회복되며 이동속도, 공격속도, 공격력이 소폭 증가합니다.
(Acquiring a potion fully restores health and grants a temporary buff to movement speed, attack speed, and attack power.)
