#ifndef APPLY_CHOICES_HPP
#define APPLY_CHOICES_HPP

#include <random>

#include "Algorithms/Algorithm.hpp"

#include "Components/BasicComponents.hpp"
#include "Components/IAChoice.hpp"

#include "Mathematics/Basics.hpp"

class ApplyChoices: public Gg::Algorithm::AbstractAlgorithm {

	public:

		ApplyChoices(Gg::GulgEngine &gulgEngine, std::vector<std::pair<Gg::Entity, Gg::Entity>> &animalsToReproduce);
		
		virtual ~ApplyChoices(); 

		void apply(); 

	protected:

		std::default_random_engine m_randomEngine;
		std::uniform_real_distribution<float> m_randomSpeed;

		std::vector<std::pair<Gg::Entity, Gg::Entity>> &m_animalsToReproduce;

};

#endif