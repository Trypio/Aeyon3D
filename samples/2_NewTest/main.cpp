
#include "../../engine/include/Transform.hpp"
#include "../../engine/include/Actor.hpp"

using namespace aeyon;

int main(int argc, char* argv[])
{
	Actor actor;
	auto t1a = actor.getComponent<Transform>();

	actor.removeComponent<Transform>();



	return 0;
}