#include "EngineRequest.hpp"

EngineRequest::EngineRequest(Gg::GulgEngine &gulgEngine):
	m_engine{gulgEngine} {}


std::vector<Gg::Entity> EngineRequest::getNearAgentType(const Gg::Entity asker, const unsigned int agentType) {

	std::vector<Gg::Entity> entities{m_engine.getAllEntities()}, result;

	std::shared_ptr<Gg::Component::Float> viewRadius{ 
		std::static_pointer_cast<Gg::Component::Float>(m_engine.getComponent(asker, "ViewRadius"))
	};

	for(Gg::Entity currentEntity: entities) {

		std::shared_ptr<Gg::Component::UnsignedInt> entityType{ 
			std::static_pointer_cast<Gg::Component::UnsignedInt>(m_engine.getComponent(currentEntity, "AgentType"))
		};

		if(currentEntity != asker 
		&& agentType == entityType->value
		&& distanceBetweenAgent(asker, currentEntity) < viewRadius->value) { result.emplace_back(currentEntity); }

	}

	return result;
}

std::vector<Gg::Entity> EngineRequest::getNeareastAgentType(const Gg::Entity asker, const unsigned int agentType) {

	std::vector<Gg::Entity> result{getNearAgentType(asker, agentType)};

	if(result.size() != 0) {

		while(result.size() != 1) {

			if(distanceBetweenAgent(asker, result[0]) > distanceBetweenAgent(asker, result[1])) { result[0] = result[1]; }
			result.erase(result.begin() + 1);
		}
	}

	return result;
}

float EngineRequest::distanceBetweenAgent(const Gg::Entity agent1, const Gg::Entity agent2) {

	std::shared_ptr<Gg::Component::Vector2D> pos1{ 
		std::static_pointer_cast<Gg::Component::Vector2D>(m_engine.getComponent(agent1, "Position"))
	};

	std::shared_ptr<Gg::Component::Vector2D> pos2{ 
		std::static_pointer_cast<Gg::Component::Vector2D>(m_engine.getComponent(agent2, "Position"))
	};

	return Gg::Maths::distance(*pos1, *pos2);
}