#include "AnimalCreation.hpp"

Gg::Entity generateRandomSpecies(Gg::GulgEngine &engine) {

	Gg::Entity newEntity{engine.getNewEntity()};


	std::shared_ptr<Gg::Component::UnsignedInt> agentType{std::make_shared<Gg::Component::UnsignedInt>(0)};
	engine.addComponentToEntity(newEntity, "AgentType", std::static_pointer_cast<Gg::Component::AbstractComponent>(agentType));


	std::shared_ptr<Gg::Component::Float> hunger{std::make_shared<Gg::Component::Float>(50.f)};
	engine.addComponentToEntity(newEntity, "Hunger", std::static_pointer_cast<Gg::Component::AbstractComponent>(hunger));

	std::shared_ptr<Gg::Component::Float> hungerDecrease{std::make_shared<Gg::Component::Float>(1.f)};
	engine.addComponentToEntity(newEntity, "HungerDecrease", std::static_pointer_cast<Gg::Component::AbstractComponent>(hungerDecrease));



	std::shared_ptr<Gg::Component::Float> thirst{std::make_shared<Gg::Component::Float>(50.f)};
	engine.addComponentToEntity(newEntity, "Thirst", std::static_pointer_cast<Gg::Component::AbstractComponent>(thirst));

	std::shared_ptr<Gg::Component::Float> thirstDecrease{std::make_shared<Gg::Component::Float>(1.f)};
	engine.addComponentToEntity(newEntity, "ThirstDecrease", std::static_pointer_cast<Gg::Component::AbstractComponent>(thirstDecrease));



	std::shared_ptr<Gg::Component::Float> death{std::make_shared<Gg::Component::Float>(100.f)};
	engine.addComponentToEntity(newEntity, "Death", std::static_pointer_cast<Gg::Component::AbstractComponent>(death));

	std::shared_ptr<Gg::Component::Float> deathDecrease{std::make_shared<Gg::Component::Float>(0.2f)};
	engine.addComponentToEntity(newEntity, "DeathDecrease", std::static_pointer_cast<Gg::Component::AbstractComponent>(deathDecrease));



	std::shared_ptr<Gg::Component::Float> reproduction{std::make_shared<Gg::Component::Float>(100)};
	engine.addComponentToEntity(newEntity, "Reproduction", std::static_pointer_cast<Gg::Component::AbstractComponent>(reproduction));

	std::shared_ptr<Gg::Component::Float> reproductionDecrease{std::make_shared<Gg::Component::Float>(2.f)};
	engine.addComponentToEntity(newEntity, "ReproductionDecrease", std::static_pointer_cast<Gg::Component::AbstractComponent>(reproductionDecrease));



	std::shared_ptr<Gg::Component::Vector2D> position{std::make_shared<Gg::Component::Vector2D>(0.f, 0.f)};
	engine.addComponentToEntity(newEntity, "Position", std::static_pointer_cast<Gg::Component::AbstractComponent>(position));

	std::shared_ptr<Gg::Component::Float> maxSpeed{std::make_shared<Gg::Component::Float>(1.f)};
	engine.addComponentToEntity(newEntity, "MaxSpeed", std::static_pointer_cast<Gg::Component::AbstractComponent>(hunger));

	std::shared_ptr<Gg::Component::Vector2D> currentSpeed{std::make_shared<Gg::Component::Vector2D>(0.f, 0.f)};
	engine.addComponentToEntity(newEntity, "CurrentSpeed", std::static_pointer_cast<Gg::Component::AbstractComponent>(currentSpeed));


	std::shared_ptr<Gg::Component::Float> viewRadius{std::make_shared<Gg::Component::Float>(100.f)};
	engine.addComponentToEntity(newEntity, "ViewRadius", std::static_pointer_cast<Gg::Component::AbstractComponent>(viewRadius));



	std::shared_ptr<Gg::Component::Sprite> sprite{std::make_shared<Gg::Component::Sprite>()};
	sprite->sprite.setTexture(*engine.getTexture("Animal"));
	sprite->sprite.setScale(0.25, 0.25);
	engine.addComponentToEntity(newEntity, "Sprite", std::static_pointer_cast<Gg::Component::AbstractComponent>(sprite));


	std::shared_ptr<IAChoice> iaChoice{std::make_shared<IAChoice>()};
	engine.addComponentToEntity(newEntity, "AnimalChoice", std::static_pointer_cast<Gg::Component::AbstractComponent>(iaChoice));

	std::shared_ptr<FSM> fsm{std::make_shared<FSM>()};
	engine.addComponentToEntity(newEntity, "FSM", std::static_pointer_cast<Gg::Component::AbstractComponent>(fsm));


	return newEntity;
}

Gg::Entity createGrass(Gg::GulgEngine &engine) {

	Gg::Entity newEntity{engine.getNewEntity()};

	std::shared_ptr<Gg::Component::UnsignedInt> agentType{std::make_shared<Gg::Component::UnsignedInt>(1)};
	engine.addComponentToEntity(newEntity, "AgentType", std::static_pointer_cast<Gg::Component::AbstractComponent>(agentType));


	std::shared_ptr<Gg::Component::Vector2D> position{std::make_shared<Gg::Component::Vector2D>(0.f, 0.f)};
	engine.addComponentToEntity(newEntity, "Position", std::static_pointer_cast<Gg::Component::AbstractComponent>(position));


	std::shared_ptr<Gg::Component::Sprite> sprite{std::make_shared<Gg::Component::Sprite>()};
	sprite->sprite.setTexture(*engine.getTexture("Grass"));
	sprite->sprite.setScale(0.20, 0.20);
	engine.addComponentToEntity(newEntity, "Sprite", std::static_pointer_cast<Gg::Component::AbstractComponent>(sprite));

	return newEntity;
}

Gg::Entity createWater(Gg::GulgEngine &engine) {

	Gg::Entity newEntity{engine.getNewEntity()};

	std::shared_ptr<Gg::Component::UnsignedInt> agentType{std::make_shared<Gg::Component::UnsignedInt>(2)};
	engine.addComponentToEntity(newEntity, "AgentType", std::static_pointer_cast<Gg::Component::AbstractComponent>(agentType));


	std::shared_ptr<Gg::Component::Vector2D> position{std::make_shared<Gg::Component::Vector2D>(0.f, 0.f)};
	engine.addComponentToEntity(newEntity, "Position", std::static_pointer_cast<Gg::Component::AbstractComponent>(position));


	std::shared_ptr<Gg::Component::Sprite> sprite{std::make_shared<Gg::Component::Sprite>()};
	sprite->sprite.setTexture(*engine.getTexture("Water"));
	sprite->sprite.setScale(0.20, 0.20);
	engine.addComponentToEntity(newEntity, "Sprite", std::static_pointer_cast<Gg::Component::AbstractComponent>(sprite));

	return newEntity;
}

void randomPositionForAgents(Gg::GulgEngine &engine, std::vector<Gg::Entity> agents, sf::FloatRect rectangle) {

    std::default_random_engine randomEngine{static_cast<long unsigned int>(std::time(nullptr))};
    std::uniform_real_distribution<float> xPos(0, rectangle.width), yPos(0, rectangle.height);

    for(Gg::Entity currentEntity: agents) {

    	std::shared_ptr<Gg::Component::Vector2D> position{ 
			std::static_pointer_cast<Gg::Component::Vector2D>(engine.getComponent(currentEntity, "Position"))
		};

		position->value = sf::Vector2f{rectangle.left + xPos(randomEngine), rectangle.top + yPos(randomEngine)};

		std::shared_ptr<Gg::Component::Sprite> sprite{ 
			std::static_pointer_cast<Gg::Component::Sprite>(engine.getComponent(currentEntity, "Sprite"))
		};

		sprite->sprite.setPosition(position->value);
    }
}