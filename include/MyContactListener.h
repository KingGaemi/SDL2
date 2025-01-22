// #pragma once
// #include <box2d/box2d.h>

// class MyContactListener : public b2ContactListener {
// public:
//     // 충돌이 시작될 때(한 번)
//     void BeginContact(b2Contact* contact) override {
//         // contact->GetFixtureA(), contact->GetFixtureB() 등으로 컬라이더 정보 확인
//         // 여기에 “큐에 이벤트 쌓기” 등 원하는 로직을 넣으면 됨.
//     }

//     // 충돌이 끝날 때(두 물체가 떨어졌을 때)
//     void EndContact(b2Contact* contact) override {
//         // ...
//     }

//     // 충돌이 일어나는 중, 매 프레임 호출 (충돌 해결 전)
//     void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {
//         // ...
//     }

//     // 충돌 계산이 끝난 후 (충돌 해결 후)
//     void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {
//         // impulse->normalImpulses, tangentImpulses 등으로 충돌 강도 확인 가능
//     }
// };