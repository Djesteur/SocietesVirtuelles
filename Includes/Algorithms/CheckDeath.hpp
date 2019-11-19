#ifndef CHECK_DEATH_HPP
#define CHECK_DEATH_HPP

#include <SFML/Graphics.hpp>

#include "Algorithms/Algorithm.hpp"
#include <iostream>
#include <fstream>

#include "Components/BasicComponents.hpp"

class CheckDeath: public Gg::Algorithm::AbstractAlgorithm {

	public:

		CheckDeath(Gg::GulgEngine &gulgEngine, std::vector<Gg::Entity> &entitiesToKill);
		
		virtual ~CheckDeath(); 

		void apply(); 

	protected:
		bool opened = false;
		std::vector<Gg::Entity> &m_entitiesToKill;
		std::ofstream monFlux;
		//std::ofstream monFlux{ "./Stats/nombre.txt" };
		//FILE* fichier;  = fopen("./Stats/nombre.txt", "w+");

};

#endif