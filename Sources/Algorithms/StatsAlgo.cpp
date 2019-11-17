#include "Algorithms/StatsAlgo.hpp"

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

	for(Gg::Entity currentEntity: m_entitiesToApply) {}
}