Physics 2D Platformer (SDL2)
소개 (Introduction)
Physics 2D Platformer는 SDL2와 Box2D를 사용하여 개발한 2D 액션 플랫포머 게임입니다 (제목 미정).
Entity-Component-System (ECS) 아키텍처를 기반으로, 확장성과 유지보수성을 고려하여 제작되었습니다.

주요 특징 (Key Features)
SDL2 기반 렌더링 및 입력 처리

Box2D 기반 2D 물리 시뮬레이션

Entity-Component-System (ECS) 구조 적용

EventManager를 통한 유연한 이벤트 처리

SceneManager를 통한 씬 전환 관리

JSON 파일 기반 데이터 드리븐 엔티티 구성

Tiled 외부 툴을 이용해 제작된 맵 (.tmx)파일 로드 기능 구현

Asprite 외부 툴을 이용하여 제작된 스프라이트 시트 & 애니메이션 로드 기능 구현

사용 기술 (Tech Stack)
C++

SDL2, Box2D, nlohmann/json

실행 방법 (How to Run)
release/ 폴더로 이동합니다.

2DPlatformer.exe 실행 파일을 실행합니다.

필요한 SDL2 관련 DLL 파일들은 함께 제공됩니다.

※ 추가 설치나 빌드 과정 없이 바로 실행 가능합니다.


엔티티를 생성 로직

1. SpawnRequest를 통해 엔티티의 타입, 이름, 좌표, 크기 등 간단한 데이터를 직접 할당해준 뒤 ecsManager의 pendingSpawn 큐에 푸쉬 (ecsManager를 호출할 수 있으면 어디서든 가능).
2. ecsManager는 EntityFactory에게 빈 엔티티 전달 후 팩토리에서 엔티티의 타입과 이름을 경로삼아 json 형태로 저장된 데이터를 기반으로 그 엔티티가 붙여야 할 컴포넌트(Component)들을 부착.
3. 마지막으로 Request에 담긴 지정 좌표와 크기 등, 유닛이 가진 고유값이 아닌 데이터를 부여


----
게임 플레이 방법

키보드 화살표 키로 이동 가능합니다.

빠르게 같은 방향키를 두 번 누를 경우 대쉬합니다.

스페이스바 키로 근접 범위공격 합니다.

Q 키로 화살을 발사합니다.

플레이어가 죽거나, 코어스톤이 파괴되면 패배합니다.

포션을 획득 시 이동속도, 공격속도, 공격력이 소폭 증가하고 체력이 모두 회복됩니다.


북쪽에서 고블린들이 주기적으로 생성됩니다.

고블린킹을 처치하면 스테이지가 클리어되고 게임이 끝납니다.



