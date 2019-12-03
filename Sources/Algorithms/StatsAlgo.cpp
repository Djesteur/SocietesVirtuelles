#include "Algorithms/StatsAlgo.hpp"
#include <iostream>
#include <fstream>
#include <string>

StatsAlgo::StatsAlgo(Gg::GulgEngine &gulgEngine, const std::string folderPath): 
	AbstractAlgorithm{gulgEngine},
	nbUpdates{0},
	moy_hunger{0.},
	moy_thirst{0.},
	moy_repro{0.},

	nombre{"./Stats/nombre.txt"},
	d_hunger{"./Stats/d_hunger.txt"},
	d_thirst{"./Stats/d_thirst.txt"},
	dead{"./Stats/dead.txt"},
	d_death{"./Stats/d_death.txt"},
	d_reproduction{"./Stats/d_reproduction.txt"},
	m_speed{"./Stats/m_speed.txt"},
	m_repro{"./Stats/repro.txt"},
	m_hunger{"./Stats/hunger.txt"},
	m_thirst{"./Stats/thirst.txt"} {

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
	int nb_mort = 0;
	int c_thirst = 0, c_hunger=0, c_dead=0;
	moy_hunger = 0.; moy_thirst = 0.; moy_repro = 0.;
	d_hunger << nbUpdates << " ";
	d_thirst << nbUpdates << " " ;
	d_reproduction << nbUpdates << " " ;

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

		std::shared_ptr<Gg::Component::Float> reproduction{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Reproduction"))
		};

		std::shared_ptr<Gg::Component::Float> deathDecrease{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "DeathDecrease"))
		};

		std::shared_ptr<Gg::Component::Float> maxSpeed{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "MaxSpeed"))
		};

		std::shared_ptr<Gg::Component::Float> hungerFitness{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "HungerFitness"))
		};

		std::shared_ptr<Gg::Component::Float> thirstFitness{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "ThirstFitness"))
		};

		std::shared_ptr<Gg::Component::Float> reproductionFitness{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "ReproductionFitness"))
		};


		d_hunger << hunger->value << " ";
		d_thirst << thirst->value << " ";
		d_reproduction << reproduction->value << " ";
		if(death->value <= 2) {
			nb_mort++; c_dead++;
		}
		if(hunger->value <= 2) {
			c_hunger++;
		}
		if(thirst->value <=2) {
			c_hunger++;
		}
		moy_hunger += hungerFitness->value;
		moy_thirst += thirstFitness->value;
		moy_repro += reproductionFitness->value;
		

	}
	moy_repro = moy_repro / (float)m_entitiesToApply.size();
	moy_hunger = moy_hunger / (float)m_entitiesToApply.size();
	moy_thirst = moy_thirst / (float)m_entitiesToApply.size();

	dead << nbUpdates << " " << c_dead << " " << c_hunger<< " " << c_thirst << std::endl;
	d_hunger << std::endl;
	d_thirst << std::endl;
	d_reproduction << std::endl;
	d_death << nbUpdates << " " << nb_mort << std::endl;
	m_repro << nbUpdates << " " << moy_repro << std::endl;
	m_hunger << nbUpdates << " " << moy_hunger << std::endl;
	m_thirst << nbUpdates << " " << moy_thirst << std::endl;

	nombre << nbUpdates << " " << m_entitiesToApply.size() << std::endl;

	nbUpdates++;

	d_thirst.flush();
	nombre.flush();
		d_hunger.flush();
		dead.flush();
		d_death.flush();
	 d_reproduction.flush();
		m_speed.flush();
	 m_repro.flush();
		m_hunger.flush();
	 m_thirst.flush();

}