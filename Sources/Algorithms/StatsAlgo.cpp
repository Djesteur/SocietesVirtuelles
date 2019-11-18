#include "Algorithms/StatsAlgo.hpp"
#include <iostream>
#include <fstream>
#include <string>

StatsAlgo::StatsAlgo(Gg::GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine} {

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

StatsAlgo::~StatsAlgo() {}


void StatsAlgo::apply() {
		std::string const nomFichier("./Stats/nombre.txt");
	    std::ofstream monFlux(nomFichier.c_str());

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

		monFlux << hunger->value << " " << thirst->value << " " << death->value << std::endl;
	}
}