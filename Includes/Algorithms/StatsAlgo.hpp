#ifndef STATS_ALGO_HPP
#define STATS_ALGO_HPP

#include <random>

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/IAChoice.hpp"

#include "Mathematics/Basics.hpp"

class StatsAlgo: public Gg::Algorithm::AbstractAlgorithm {

	public:

		StatsAlgo(Gg::GulgEngine &gulgEngine);
		
		virtual ~StatsAlgo(); 

		void apply(); 

	protected:

};

#endif