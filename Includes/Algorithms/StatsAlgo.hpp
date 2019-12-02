#ifndef STATS_ALGO_HPP
#define STATS_ALGO_HPP

#include <random>

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/IAChoice.hpp"

#include "Mathematics/Basics.hpp"

class StatsAlgo: public Gg::Algorithm::AbstractAlgorithm {

	public:

		StatsAlgo(Gg::GulgEngine &gulgEngine, const std::string folderPath);
		
		virtual ~StatsAlgo(); 

		void apply(); 

	protected:

		unsigned int nbUpdates;
<<<<<<< HEAD
		std::ofstream file;
=======
		std::ofstream nombre;
		std::ofstream d_hunger;
		std::ofstream d_thirst;
		std::ofstream dead;
		std::ofstream d_death;
		std::ofstream d_reproduction;
		std::ofstream m_speed;
		std::ofstream choice;


>>>>>>> b90141885fcc588c8a060331afe3494afb9357d0
};

#endif