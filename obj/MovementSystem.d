obj/MovementSystem.o: src/MovementSystem.cpp \
 include/Systems/MovementSystem.h include/ECS/System.h \
 include/ECS/Entity.h include/ECS/Component.h \
 include/Systems/CollisionSystem.h include/ECS/ECSManager.h \
 include/ECS/EntityFactory.h include/nlohmann/json.hpp \
 include/nlohmann/adl_serializer.hpp \
 include/nlohmann/detail/abi_macros.hpp \
 include/nlohmann/detail/conversions/from_json.hpp \
 include/nlohmann/detail/exceptions.hpp \
 include/nlohmann/detail/value_t.hpp \
 include/nlohmann/detail/macro_scope.hpp \
 include/nlohmann/detail/meta/detected.hpp \
 include/nlohmann/detail/meta/void_t.hpp \
 include/nlohmann/thirdparty/hedley/hedley.hpp \
 include/nlohmann/detail/string_escape.hpp \
 include/nlohmann/detail/input/position_t.hpp \
 include/nlohmann/detail/meta/cpp_future.hpp \
 include/nlohmann/detail/meta/type_traits.hpp \
 include/nlohmann/detail/iterators/iterator_traits.hpp \
 include/nlohmann/detail/meta/call_std/begin.hpp \
 include/nlohmann/detail/meta/call_std/end.hpp \
 include/nlohmann/json_fwd.hpp include/nlohmann/detail/string_concat.hpp \
 include/nlohmann/detail/meta/identity_tag.hpp \
 include/nlohmann/detail/meta/std_fs.hpp \
 include/nlohmann/detail/conversions/to_json.hpp \
 include/nlohmann/detail/iterators/iteration_proxy.hpp \
 include/nlohmann/detail/string_utils.hpp \
 include/nlohmann/byte_container_with_subtype.hpp \
 include/nlohmann/detail/hash.hpp \
 include/nlohmann/detail/input/binary_reader.hpp \
 include/nlohmann/detail/input/input_adapters.hpp \
 include/nlohmann/detail/input/json_sax.hpp \
 include/nlohmann/detail/input/lexer.hpp \
 include/nlohmann/detail/meta/is_sax.hpp \
 include/nlohmann/detail/input/parser.hpp \
 include/nlohmann/detail/iterators/internal_iterator.hpp \
 include/nlohmann/detail/iterators/primitive_iterator.hpp \
 include/nlohmann/detail/iterators/iter_impl.hpp \
 include/nlohmann/detail/iterators/json_reverse_iterator.hpp \
 include/nlohmann/detail/json_custom_base_class.hpp \
 include/nlohmann/detail/json_pointer.hpp \
 include/nlohmann/detail/json_ref.hpp \
 include/nlohmann/detail/output/binary_writer.hpp \
 include/nlohmann/detail/output/output_adapters.hpp \
 include/nlohmann/detail/output/serializer.hpp \
 include/nlohmann/detail/conversions/to_chars.hpp \
 include/nlohmann/ordered_map.hpp \
 include/nlohmann/detail/macro_unscope.hpp \
 include/nlohmann/thirdparty/hedley/hedley_undef.hpp include/Requests.h \
 include/Groups.h include/Components/Components.h \
 include/Components/AnimationComponent.h \
 include/Components/ColliderComponent.h include/Rect.h include/Vector2D.h \
 include/Components/CommandComponent.h \
 include/Components/DirectionComponent.h \
 include/Components/MovementCommandComponent.h \
 include/Components/CooldownComponent.h \
 include/Components/DamageComponent.h include/Components/DashComponent.h \
 include/KeyCode.h include/Components/LifeTimeComponent.h \
 include/Components/OwnerComponent.h \
 include/Components/PhysicsComponent.h include/box2d/box2d.h \
 include/box2d/base.h include/box2d/collision.h \
 include/box2d/math_functions.h include/box2d/id.h include/box2d/types.h \
 include/Components/PlayableComponent.h \
 include/Components/PositionComponent.h \
 include/Components/ProjectileComponent.h \
 include/Components/SolidComponent.h include/Components/SpriteComponent.h \
 include/Components/StateComponent.h include/Components/StatusComponent.h \
 include/Components/TransformComponent.h \
 include/Components/VelocityComponent.h \
 include/Components/ItemComponent.h \
 include/Components/FloatingEffectComponent.h \
 include/Systems/PhysicsSystem.h
include/Systems/MovementSystem.h:
include/ECS/System.h:
include/ECS/Entity.h:
include/ECS/Component.h:
include/Systems/CollisionSystem.h:
include/ECS/ECSManager.h:
include/ECS/EntityFactory.h:
include/nlohmann/json.hpp:
include/nlohmann/adl_serializer.hpp:
include/nlohmann/detail/abi_macros.hpp:
include/nlohmann/detail/conversions/from_json.hpp:
include/nlohmann/detail/exceptions.hpp:
include/nlohmann/detail/value_t.hpp:
include/nlohmann/detail/macro_scope.hpp:
include/nlohmann/detail/meta/detected.hpp:
include/nlohmann/detail/meta/void_t.hpp:
include/nlohmann/thirdparty/hedley/hedley.hpp:
include/nlohmann/detail/string_escape.hpp:
include/nlohmann/detail/input/position_t.hpp:
include/nlohmann/detail/meta/cpp_future.hpp:
include/nlohmann/detail/meta/type_traits.hpp:
include/nlohmann/detail/iterators/iterator_traits.hpp:
include/nlohmann/detail/meta/call_std/begin.hpp:
include/nlohmann/detail/meta/call_std/end.hpp:
include/nlohmann/json_fwd.hpp:
include/nlohmann/detail/string_concat.hpp:
include/nlohmann/detail/meta/identity_tag.hpp:
include/nlohmann/detail/meta/std_fs.hpp:
include/nlohmann/detail/conversions/to_json.hpp:
include/nlohmann/detail/iterators/iteration_proxy.hpp:
include/nlohmann/detail/string_utils.hpp:
include/nlohmann/byte_container_with_subtype.hpp:
include/nlohmann/detail/hash.hpp:
include/nlohmann/detail/input/binary_reader.hpp:
include/nlohmann/detail/input/input_adapters.hpp:
include/nlohmann/detail/input/json_sax.hpp:
include/nlohmann/detail/input/lexer.hpp:
include/nlohmann/detail/meta/is_sax.hpp:
include/nlohmann/detail/input/parser.hpp:
include/nlohmann/detail/iterators/internal_iterator.hpp:
include/nlohmann/detail/iterators/primitive_iterator.hpp:
include/nlohmann/detail/iterators/iter_impl.hpp:
include/nlohmann/detail/iterators/json_reverse_iterator.hpp:
include/nlohmann/detail/json_custom_base_class.hpp:
include/nlohmann/detail/json_pointer.hpp:
include/nlohmann/detail/json_ref.hpp:
include/nlohmann/detail/output/binary_writer.hpp:
include/nlohmann/detail/output/output_adapters.hpp:
include/nlohmann/detail/output/serializer.hpp:
include/nlohmann/detail/conversions/to_chars.hpp:
include/nlohmann/ordered_map.hpp:
include/nlohmann/detail/macro_unscope.hpp:
include/nlohmann/thirdparty/hedley/hedley_undef.hpp:
include/Requests.h:
include/Groups.h:
include/Components/Components.h:
include/Components/AnimationComponent.h:
include/Components/ColliderComponent.h:
include/Rect.h:
include/Vector2D.h:
include/Components/CommandComponent.h:
include/Components/DirectionComponent.h:
include/Components/MovementCommandComponent.h:
include/Components/CooldownComponent.h:
include/Components/DamageComponent.h:
include/Components/DashComponent.h:
include/KeyCode.h:
include/Components/LifeTimeComponent.h:
include/Components/OwnerComponent.h:
include/Components/PhysicsComponent.h:
include/box2d/box2d.h:
include/box2d/base.h:
include/box2d/collision.h:
include/box2d/math_functions.h:
include/box2d/id.h:
include/box2d/types.h:
include/Components/PlayableComponent.h:
include/Components/PositionComponent.h:
include/Components/ProjectileComponent.h:
include/Components/SolidComponent.h:
include/Components/SpriteComponent.h:
include/Components/StateComponent.h:
include/Components/StatusComponent.h:
include/Components/TransformComponent.h:
include/Components/VelocityComponent.h:
include/Components/ItemComponent.h:
include/Components/FloatingEffectComponent.h:
include/Systems/PhysicsSystem.h:
