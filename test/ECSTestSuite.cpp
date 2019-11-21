//
//
//

#include <catch2/catch.hpp>
#include <ECS/World.hpp>
#include <ECS/Entity.hpp>
#include <Transform.hpp>
#include <Camera.hpp>
#include <ECS/Component.hpp>

TEST_CASE("entities can be created and destroyed", "[ecs]")
{
	aeyon::World world;

	SECTION("the default entity is invalid and has a nil ID")
	{
		aeyon::Entity entity;
		REQUIRE(!entity.isValid());
	}

	SECTION("a world-created entity is inherently valid")
	{
		aeyon::Entity entity = world.createEntity();
		REQUIRE(entity.isValid());
	}

	SECTION("an entity is invalid if it has an invalid ID (not nil) or belongs to no world")
	{
		aeyon::UUID userID = aeyon::UUID::generate();
		aeyon::Entity entity(userID, nullptr);
		REQUIRE(!entity.isValid());

		entity = aeyon::Entity(userID, &world);
		REQUIRE(!entity.isValid());
	}

	SECTION("a destroyed entity is marked as invalid while retaining its original ID")
	{
		aeyon::Entity entity = world.createEntity();
		aeyon::UUID id = entity.getID();
		entity.destroy();
		REQUIRE(id == entity.getID());
		REQUIRE(!entity.isValid());
	}
}

TEST_CASE("components can be added to entities", "[ecs]")
{
	aeyon::World world;

	aeyon::Entity entity = world.createEntity();
	auto component = entity.addComponent<aeyon::Transform>();

	SECTION("an entity can be queried for the assignment of a certain component type")
	{
		REQUIRE(entity.hasComponent<aeyon::Transform>());
	}

	SECTION("an added component can be retrieved")
	{
		REQUIRE(component.get() == entity.getComponent<aeyon::Transform>().get());
	}
}

TEST_CASE("components can be queried for non-assigned component types")
{
	aeyon::World world;
	aeyon::Entity entity = world.createEntity();

	REQUIRE(!entity.hasComponent<aeyon::Transform>());

	SECTION("the returned component class is marked as sinvalid and its component pointer is null")
	{
		auto component = entity.getComponent<aeyon::Transform>();
		REQUIRE(!component.isValid());
		REQUIRE(component.get() == nullptr);
	}
}


