#ifndef FSM_HPP
#define FSM_HPP

#include "Components/Component.hpp"
#include "Components/IAChoice.hpp"

struct FSM: public Gg::Component::AbstractComponent {

	public:

		FSM() {}
		FSM(const FSM &fsmComponent) {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<FSM>(*this)); }         

		IAChoice makeChoice() { return IAChoice{}; }
};

#endif