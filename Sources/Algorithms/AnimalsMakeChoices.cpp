#include "Algorithms/AnimalsMakeChoices.hpp"

AnimalsMakeChoices::AnimalsMakeChoices(Gg::GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine},
	m_request{gulgEngine} {

	m_signature = gulgEngine.getComponentSignature("AgentType");
	m_signature += gulgEngine.getComponentSignature("Hunger");
	m_signature += gulgEngine.getComponentSignature("Thirst");
	m_signature += gulgEngine.getComponentSignature("Death");
	m_signature += gulgEngine.getComponentSignature("Reproduction");
	m_signature += gulgEngine.getComponentSignature("Position");
	m_signature += gulgEngine.getComponentSignature("ViewRadius");
	m_signature += gulgEngine.getComponentSignature("AnimalChoice");
	m_signature += gulgEngine.getComponentSignature("FSM");
}

AnimalsMakeChoices::~AnimalsMakeChoices() {}

void AnimalsMakeChoices::apply() {

	for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<FSM> fsm{ 
			std::static_pointer_cast<FSM>(m_gulgEngine.getComponent(currentEntity, "FSM"))
		};

		std::shared_ptr<IAChoice> choice{ 
			std::static_pointer_cast<IAChoice>(m_gulgEngine.getComponent(currentEntity, "AnimalChoice"))
		};

		*choice = fsm->makeChoice(currentEntity, m_request);
	}
}