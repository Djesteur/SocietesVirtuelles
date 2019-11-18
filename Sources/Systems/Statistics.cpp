#include "Systems/Statistics.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Statistics::Statistics(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<StatsAlgo>(gulgEngine));
}

Statistics::~Statistics() {}

void Statistics::stats() {

	/*string const nomFichier("./stats.txt");
    ofstream monFlux(nomFichier.c_str());
    if(monFlux) {
		for(Gg::Entity currentEntity: m_entitiesToApply) {
        	monFlux << "hey" << endl;
    	}
	}*/
}