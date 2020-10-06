//
// Created by thors on 06.10.2020.
//

#ifndef AEYON3D_SYSTEM_HPP
#define AEYON3D_SYSTEM_HPP

namespace aeyon
{
	class System
	{
	public:
		virtual ~System() = default;

		virtual void setup() {}
		virtual void start() {}
		virtual void update() {}
		virtual void fixedUpdate() {}
	};
}

#endif //AEYON3D_SYSTEM_HPP
