#include "Algorithms/StatsAlgo.hpp"
#include <iostream>
#include <fstream>
#include <string>

StatsAlgo::StatsAlgo(Gg::GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine},
	nbUpdates{0},
	nombre{"./Stats/nombre.txt"},
	d_hunger{"./Stats/d_hunger.txt"},
	d_thirst{"./Stats/d_thirst.txt"},
	dead{"./Stats/dead.txt"},
	d_death{"./Stats/d_death.txt"},
	d_reproduction{"./Stats/d_reproduction.txt"},
	m_speed{"./Stats/m_speed.txt"},
	choice{"./Stats/choice.txt"} {

	m_signature = gulgEngine.getComponentSignature("AgentType");
	m_signature += gulgEngine.getComponentSignature("Hunger");
	//m_signature += gulgEngine.getComponentSignature("HungerDecrease");
	m_signature += gulgEngine.getComponentSignature("Thirst");
	m_signature += gulgEngine.getComponentSignature("Death");
	m_signature += gulgEngine.getComponentSignature("Reproduction");
	m_signature += gulgEngine.getComponentSignature("Position");
	m_signature += gulgEngine.getComponentSignature("ViewRadius");
	m_signature += gulgEngine.getComponentSignature("AnimalChoice");
	m_signature += gulgEngine.getComponentSignature("FSM");
}

StatsAlgo::~StatsAlgo() {}


void StatsAlgo::apply() {

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

		std::shared_ptr<Gg::Component::Float> hungerDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "HungerDecrease"))
		};

		std::shared_ptr<Gg::Component::Float> thirstDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "ThirstDecrease"))
		};

		std::shared_ptr<Gg::Component::Float> reproductionDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "ReproductionDecrease"))
		};

		std::shared_ptr<Gg::Component::Float> deathDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "DeathDecrease"))
		};

		std::shared_ptr<Gg::Component::Float> maxSpeed{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "MaxSpeed"))
		};


		d_hunger << currentEntity << " " << hungerDecrease << std::endl;
		d_thirst << currentEntity << " " << thirstDecrease << std::endl;
		d_reproduction << currentEntity << " " << reproductionDecrease << std::endl;
		d_death << currentEntity << " " << deathDecrease << std::endl;
		m_speed << currentEntity << " " << maxSpeed << std::endl;
		

	}

	nombre << nbUpdates << " " << m_entitiesToApply.size() << std::endl;

	nbUpdates++;
}