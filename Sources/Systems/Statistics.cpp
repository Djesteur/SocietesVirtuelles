#include "Systems/Statistics.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Statistics::Statistics(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<StatsAlgo>(gulgEngine));
}

Statistics::~Statistics() {}

void Statistics::applyAlgorithms() {

	for(std::unique_ptr<Gg::Algorithm::AbstractAlgorithm> &currentAlgo: m_algorithms) { currentAlgo->apply(); }
}

std::vector<Gg::Entity> Statistics::getEntities() { return m_entities; }
