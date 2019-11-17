#include "Algorithms/CheckDeath.hpp"

CheckDeath::CheckDeath(Gg::GulgEngine &gulgEngine, std::vector<Gg::Entity> &entitiesToKill): 

	AbstractAlgorithm{gulgEngine},
	m_entitiesToKill{entitiesToKill} {

	m_signature = gulgEngine.getComponentSignature("Hunger");
	m_signature += gulgEngine.getComponentSignature("Thirst");
	m_signature += gulgEngine.getComponentSignature("Death");
}

CheckDeath::~CheckDeath() {}

void CheckDeath::apply() {

	for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Gg::Component::Float> hunger{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Hunger"))
		};

		std::shared_ptr<Gg::Component::Float> thirst{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Thirst"))
		};

		std::shared_ptr<Gg::Component::Float> death{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Death"))
		};

		if(hunger->value <= 0.f || thirst->value <= 0.f /*|| death->value <= 0.f*/) { m_entitiesToKill.emplace_back(currentEntity); }

	}
}