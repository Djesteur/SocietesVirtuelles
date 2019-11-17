#ifndef ENGINE_REQUEST_HPP
#define ENGINE_REQUEST_HPP

#include "GulgEngine/GulgEngine.hpp"
#include "GulgEngine/GulgDeclarations.hpp"

#include "Mathematics/Basics.hpp"

class EngineRequest {

	public:

		EngineRequest(Gg::GulgEngine &gulgEngine);

		std::vector<Gg::Entity> getNearAgentType(const Gg::Entity asker, const unsigned int agentType);
		std::vector<Gg::Entity> getNeareastAgentType(const Gg::Entity asker, const unsigned int agentType);
		std::vector<Gg::Entity> getPartners(const Gg::Entity asker);

		float distanceBetweenAgent(const Gg::Entity agent1, const Gg::Entity agent2);

		bool isUnderHungerThreshold(const Gg::Entity asker);
		bool isUnderThirstThreshold(const Gg::Entity asker);
		bool canReproduce(const Gg::Entity agent);

		float entityHitboxSize(const Gg::Entity agent);

	protected:

		Gg::GulgEngine &m_engine;      
};

#endif