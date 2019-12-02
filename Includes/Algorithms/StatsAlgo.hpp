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

		unsigned int nbUpdates;
		std::ofstream nombre;
		std::ofstream d_hunger;
		std::ofstream d_thirst;
		std::ofstream dead;
		std::ofstream d_death;
		std::ofstream d_reproduction;
		std::ofstream m_speed;
		std::ofstream choice;


};

#endif