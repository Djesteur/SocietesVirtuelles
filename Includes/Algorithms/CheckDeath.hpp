#ifndef CHECK_DEATH_HPP
#define CHECK_DEATH_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"

class CheckDeath: public Gg::Algorithm::AbstractAlgorithm {

	public:

		CheckDeath(Gg::GulgEngine &gulgEngine, std::vector<Gg::Entity> &entitiesToKill);
		
		virtual ~CheckDeath(); 

		void apply(); 

	protected:

		std::vector<Gg::Entity> &m_entitiesToKill;
		//std::ofstream monFlux{ "./Stats/nombre.txt" };

};

#endif