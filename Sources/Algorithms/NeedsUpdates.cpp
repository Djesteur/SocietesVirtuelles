#include "Algorithms/NeedsUpdates.hpp"

NeedsUpdates::NeedsUpdates(Gg::GulgEngine &gulgEngine): AbstractAlgorithm{gulgEngine} {

	m_signature = gulgEngine.getComponentSignature("Hunger");
	m_signature += gulgEngine.getComponentSignature("HungerDecrease");

	m_signature += gulgEngine.getComponentSignature("Thirst");
	m_signature += gulgEngine.getComponentSignature("ThirstDecrease");

	m_signature += gulgEngine.getComponentSignature("Death");
	m_signature += gulgEngine.getComponentSignature("DeathDecrease");

	m_signature += gulgEngine.getComponentSignature("Reproduction");
	m_signature += gulgEngine.getComponentSignature("ReproductionDecrease");

}

NeedsUpdates::~NeedsUpdates() {}

void NeedsUpdates::apply() {

	for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Gg::Component::Float> hunger{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Hunger"))
		};

		std::shared_ptr<Gg::Component::Float> hungerDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "HungerDecrease"))
		};

		hunger->value -= hungerDecrease->value;
		if(hunger->value < 0) { hunger->value = 0; }



		std::shared_ptr<Gg::Component::Float> thirst{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Thirst"))
		};

		std::shared_ptr<Gg::Component::Float> thirstDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "ThirstDecrease"))
		};

		thirst->value -= thirstDecrease->value;
		if(thirst->value < 0) { thirst->value = 0; }



		std::shared_ptr<Gg::Component::Float> death{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Death"))
		};

		std::shared_ptr<Gg::Component::Float> deathDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "DeathDecrease"))
		};

		death->value -= deathDecrease->value;
		if(death->value < 0) { death->value = 0; }



		std::shared_ptr<Gg::Component::Float> reproduction{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Reproduction"))
		};

		std::shared_ptr<Gg::Component::Float> reproductionDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "ReproductionDecrease"))
		};

		reproduction->value -= reproductionDecrease->value;
		if(reproduction->value < 0) { reproduction->value = 0; }
	}
}