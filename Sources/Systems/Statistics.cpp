#include "Systems/Statistics.hpp"

Statistics::Statistics(Gg::GulgEngine &gulgEngine): AbstractSystem{gulgEngine} {

	m_algorithms.emplace_back(std::make_unique<StatsAlgo>(gulgEngine));
}

Statistics::~Statistics() {}