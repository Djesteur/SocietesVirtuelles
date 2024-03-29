#include "Systems/Statistics.hpp"


Statistics::Statistics(Gg::GulgEngine &gulgEngine, const std::string folderPath): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<StatsAlgo>(gulgEngine, folderPath));
}

Statistics::~Statistics() {}

void Statistics::applyAlgorithms() {

	for(std::unique_ptr<Gg::Algorithm::AbstractAlgorithm> &currentAlgo: m_algorithms) { currentAlgo->apply(); }
}

std::vector<Gg::Entity> Statistics::getEntities() { return m_entities; }
