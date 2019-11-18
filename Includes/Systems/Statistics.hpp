#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "Systems/AbstractSystem.hpp"

#include "Algorithms/NeedsUpdates.hpp"
#include "Algorithms/CheckDeath.hpp"

#include "Algorithms/StatsAlgo.hpp"

#include "Components/BasicComponents.hpp"

class Statistics: public Gg::Systems::AbstractSystem {

	public:

		Statistics(Gg::GulgEngine &gulgEngine);
		
		virtual ~Statistics();

		void applyAlgorithms();


		std::vector<Gg::Entity> getEntities();

	protected:
		std::vector<Gg::Entity> m_entities;
};


#endif