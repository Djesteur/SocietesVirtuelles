#include "Algorithms/ApplyChoices.hpp"

ApplyChoices::ApplyChoices(Gg::GulgEngine &gulgEngine): 
	AbstractAlgorithm{gulgEngine},
	m_randomEngine{std::time(nullptr)},
	m_randomSpeed{-1.f, 1.f}{

	m_signature = gulgEngine.getComponentSignature("Hunger");
	m_signature += gulgEngine.getComponentSignature("Thirst");
	m_signature += gulgEngine.getComponentSignature("Death");
	m_signature += gulgEngine.getComponentSignature("Reproduction");
	m_signature += gulgEngine.getComponentSignature("Position");
	m_signature += gulgEngine.getComponentSignature("CurrentSpeed");
	m_signature += gulgEngine.getComponentSignature("MaxSpeed");
	m_signature += gulgEngine.getComponentSignature("AnimalChoice");
}

ApplyChoices::~ApplyChoices() {}

void ApplyChoices::apply() {

	for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<IAChoice> choice{ 
			std::static_pointer_cast<IAChoice>(m_gulgEngine.getComponent(currentEntity, "AnimalChoice"))
		};

		std::shared_ptr<Gg::Component::Vector2D> position{ 
			std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "Position"))
		};


		if(choice->choice == Choice::Move) {

			std::shared_ptr<Gg::Component::Vector2D> currentSpeed{ 
				std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "CurrentSpeed"))
			};


			if(choice->target == Gg::NoEntity) { currentSpeed->value = sf::Vector2f{-1.f, 0.f}; }
			else {

				std::shared_ptr<Gg::Component::Vector2D> targetPos{ 
					std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(choice->target, "Position"))
				};

				currentSpeed->value = targetPos->value - position->value;
				currentSpeed->value /= currentSpeed->norm();
			}


			std::shared_ptr<Gg::Component::Float> maxSpeed{ 
				std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "MaxSpeed"))
			};

			currentSpeed->value *= maxSpeed->value;
			position->value += currentSpeed->value;

		}

		if(choice->choice == Choice::Eat) {

			std::shared_ptr<Gg::Component::UnsignedInt> targetType{ 
				std::static_pointer_cast<Gg::Component::UnsignedInt>(m_gulgEngine.getComponent(choice->target, "AgentType"))
			};

			std::shared_ptr<Gg::Component::Vector2D> targetPosition{ 
				std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(choice->target, "Position"))
			};

			std::shared_ptr<Gg::Component::Float> maxSpeed{ 
				std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "MaxSpeed"))
			};

				
			if(targetType->value == 1 && Gg::Maths::distance(*position, *targetPosition) < maxSpeed->value) { 

				std::shared_ptr<Gg::Component::Float> hunger{ 
					std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Hunger"))
				};

				hunger->value = 100.f; 
			}

		}

		if(choice->choice == Choice::Drink) {

			std::shared_ptr<Gg::Component::UnsignedInt> targetType{ 
				std::static_pointer_cast<Gg::Component::UnsignedInt>(m_gulgEngine.getComponent(choice->target, "AgentType"))
			};

			std::shared_ptr<Gg::Component::Vector2D> targetPosition{ 
				std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(choice->target, "Position"))
			};

			std::shared_ptr<Gg::Component::Float> maxSpeed{ 
				std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "MaxSpeed"))
			};

			if(targetType->value == 2 && Gg::Maths::distance(*position, *targetPosition) < maxSpeed->value) { 

				std::shared_ptr<Gg::Component::Float> thirst{ 
					std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Thirst"))
				};

				thirst->value = 100.f; 
			}
		}

		if(choice->choice == Choice::RandomMove) {

			std::shared_ptr<Gg::Component::Vector2D> currentSpeed{ 
				std::static_pointer_cast<Gg::Component::Vector2D>(m_gulgEngine.getComponent(currentEntity, "CurrentSpeed"))
			};

			if(currentSpeed->value == sf::Vector2f{0.f, 0.f}) {

				std::shared_ptr<Gg::Component::Float> maxSpeed{ 
					std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "MaxSpeed"))
				};
					
   			 	currentSpeed->value.x = m_randomSpeed(m_randomEngine);
   			 	currentSpeed->value.y = m_randomSpeed(m_randomEngine);
   			 	currentSpeed->value *= maxSpeed->value;
			}

			position->value += currentSpeed->value;
		}
	}
}