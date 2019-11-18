#include "Algorithms/StatsAlgo.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
	string const nomFichier("./stats.txt");
    ofstream monFlux(nomFichier.c_str());
    if(monFlux) {
		for(Gg::Entity currentEntity: m_entitiesToApply) {
        	monFlux << "hey" << endl;
    	}
	}
}