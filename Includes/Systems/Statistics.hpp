#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "Systems/AbstractSystem.hpp"

#include "Algorithms/NeedsUpdates.hpp"
#include "Algorithms/CheckDeath.hpp"

#include "Algorithms/StatsAlgo.hpp"

class Statistics: public Gg::Systems::AbstractSystem {

	public:

		Statistics(Gg::GulgEngine &gulgEngine);
		
		virtual ~Statistics();

	protected:
};


#endif