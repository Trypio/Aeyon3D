//
//
//

#include <catch2/catch.hpp>
#include "../engine/include/Transform.hpp"
#include "../engine/include/Actor.hpp"

TEST_CASE("components can be added to entities", "[ecs]")
{
	//aeyon::Actor actor;
	//auto transform = actor.addComponent<aeyon::Transform>();

	//REQUIRE(component.getOwner() == entity);

//	SECTION("an entity can be queried for the assignment of a certain component type")
//	{
//		REQUIRE(actor.hasComponent<aeyon::Transform>());
//	}
//
//	SECTION("an added component can be retrieved")
//	{
//		REQUIRE(transform == actor.getComponent<aeyon::Transform>());
//	}
}
//
//TEST_CASE("components can be queried for non-assigned component types")
//{
//	aeyon::World world;
//	aeyon::Entity entity = world.createEntity();
//
//	REQUIRE(!entity.hasComponent<aeyon::Transform>());
//
//	SECTION("the returned component class is marked as invalid and its component pointer is null")
//	{
//		auto component = entity.getComponent<aeyon::Transform>();
//		REQUIRE(!component.isValid());
//		REQUIRE(component.get() == nullptr);
//	}
//}
//
//TEST_CASE("components can be removed from entities", "[ecs]")
//{
//	aeyon::World world;
//
//	aeyon::Entity entity = world.createEntity();
//	auto component = entity.addComponent<aeyon::Transform>();
//
//	entity.removeComponent<aeyon::Transform>();
//	REQUIRE(!entity.hasComponent<aeyon::Transform>());
//	REQUIRE(!entity.getComponent<aeyon::Transform>());
//	REQUIRE(!component.getOwner());
//
//	SECTION("trying to remove a non-existing component yields no errors")
//	{
//		entity.removeComponent<aeyon::Camera>();
//	}
//}
//
//TEST_CASE("components can be copied from one entity to another", "[ecs]")
//{
//	aeyon::World world;
//	aeyon::Entity src = world.createEntity();
//	const glm::vec3 testPos(42.0f);
//	auto srcHandle = src.addComponent<aeyon::Transform>();
//	srcHandle->setPosition(testPos);
//
//	SECTION("basic copying works")
//	{
//		aeyon::Entity dst = world.createEntity();
//		auto dstHandle = dst.copyComponent<aeyon::Transform>(src.getComponent<aeyon::Transform>());
//
//		REQUIRE(src.hasComponent<aeyon::Transform>());
//		REQUIRE(dst.hasComponent<aeyon::Transform>());
//		REQUIRE(src.getComponent<aeyon::Transform>() != dst.getComponent<aeyon::Transform>());
//		REQUIRE(srcHandle->getPosition() == dstHandle->getPosition());
//		REQUIRE(srcHandle.getOwner() == src);
//		REQUIRE(dstHandle.getOwner() == dst);
//	}
//
//	SECTION("trying to copy a non-existing component yields no errors and returns an invalid component handle")
//	{
//		aeyon::Entity dst = world.createEntity();
//		auto cpyHandle = dst.copyComponent(src.getComponent<aeyon::Camera>());
//		REQUIRE(!cpyHandle);
//	}
//}
//
//TEST_CASE("components can be moved from one entity to another", "[ecs]")
//{
//	aeyon::World world;
//	aeyon::Entity src = world.createEntity();
//	const glm::vec3 testPos(42.0f);
//	auto srcHandle = src.addComponent<aeyon::Transform>();
//	srcHandle->setPosition(testPos);
//
//	SECTION("basic moving works")
//	{
//		aeyon::Entity dst = world.createEntity();
//		auto dstHandle = dst.moveComponent(src.getComponent<aeyon::Transform>());
//		REQUIRE(!src.hasComponent<aeyon::Transform>());
//		REQUIRE(dst.hasComponent<aeyon::Transform>());
//		REQUIRE(dstHandle->getPosition() == testPos);
//		REQUIRE(srcHandle == dstHandle);
//	}
//}




