#ifndef IA_CHOICE_HPP
#define IA_CHOICE_HPP

#include "Components/Component.hpp"

enum class Choice{Unknow, Move, Eat, Drink, Reproduction, RandomMove};

struct IAChoice: public Gg::Component::AbstractComponent {

	public:

		IAChoice(const Choice currentChoice = Choice::Unknow, Gg::Entity currentTarget = Gg::NoEntity):
			choice{currentChoice},
			target{currentTarget} {}

		IAChoice(const IAChoice &iaComponent): 
			choice{iaComponent.choice},
			target{iaComponent.target} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<IAChoice>(*this)); }

		Choice choice;
		Gg::Entity target;            
};

#endif