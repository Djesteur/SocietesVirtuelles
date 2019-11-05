#ifndef ANIMALS_UPDATE_HPP
#define ANIMALS_UPDATE_HPP

#include "Systems/AbstractSystem.hpp"

#include "Algorithms/NeedsUpdates.hpp"
#include "Algorithms/CheckDeath.hpp"

class AnimalsUpdate: public Gg::Systems::AbstractSystem {

	public:

		AnimalsUpdate(Gg::GulgEngine &gulgEngine);
		
		virtual ~AnimalsUpdate();

		void applyAlgorithms();

		std::vector<Gg::Entity> getEntitiesToKill();

	protected:

		std::vector<Gg::Entity> m_entitiesToKill;
};


#endif