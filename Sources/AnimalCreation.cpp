#include "AnimalCreation.hpp"

Gg::Entity generateRandomSpecies(Gg::GulgEngine &engine) {

	Gg::Entity newEntity{engine.getNewEntity()};


	std::shared_ptr<Gg::Component::UnsignedInt> agentType{std::make_shared<Gg::Component::UnsignedInt>(0)};
	engine.addComponentToEntity(newEntity, "AgentType", std::static_pointer_cast<Gg::Component::AbstractComponent>(agentType));


	std::shared_ptr<Gg::Component::Float> hunger{std::make_shared<Gg::Component::Float>(80.f)};
	engine.addComponentToEntity(newEntity, "Hunger", std::static_pointer_cast<Gg::Component::AbstractComponent>(hunger));

	std::shared_ptr<Gg::Component::Float> hungerDecrease{std::make_shared<Gg::Component::Float>(0.5f)};
	engine.addComponentToEntity(newEntity, "HungerDecrease", std::static_pointer_cast<Gg::Component::AbstractComponent>(hungerDecrease));



	std::shared_ptr<Gg::Component::Float> thirst{std::make_shared<Gg::Component::Float>(50.f)};
	engine.addComponentToEntity(newEntity, "Thirst", std::static_pointer_cast<Gg::Component::AbstractComponent>(thirst));

	std::shared_ptr<Gg::Component::Float> thirstDecrease{std::make_shared<Gg::Component::Float>(0.5f)};
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

	std::shared_ptr<Gg::Component::Float> maxSpeed{std::make_shared<Gg::Component::Float>(5.f)};
	engine.addComponentToEntity(newEntity, "MaxSpeed", std::static_pointer_cast<Gg::Component::AbstractComponent>(maxSpeed));

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






	std::shared_ptr<Gg::Component::Float> hungerFitness{std::make_shared<Gg::Component::Float>(1)};
	engine.addComponentToEntity(newEntity, "HungerFitness", std::static_pointer_cast<Gg::Component::AbstractComponent>(hungerFitness));


	std::shared_ptr<Gg::Component::Float> thirstFitness{std::make_shared<Gg::Component::Float>(1)};
	engine.addComponentToEntity(newEntity, "ThirstFitness", std::static_pointer_cast<Gg::Component::AbstractComponent>(thirstFitness));


	std::shared_ptr<Gg::Component::Float> reproductionFitness{std::make_shared<Gg::Component::Float>(1)};
	engine.addComponentToEntity(newEntity, "ReproductionFitness", std::static_pointer_cast<Gg::Component::AbstractComponent>(reproductionFitness));



	Node eatBegin{};
	eatBegin.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> food{request.getNeareastAgentType(myself, 1)};
		if(food.empty()) { return 1; }

		if(request.distanceBetweenAgent(myself, food[0]) > 1.f) { return 2; }

		return 3;
	};

	Node searchForFood{};
	searchForFood.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> food{request.getNeareastAgentType(myself, 1)};
		if(food.empty()) { return 1; }

		return 2;
	};

	searchForFood.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::RandomMove;
		currentChoice.target = Gg::NoEntity;

		return currentChoice;
	};

	Node goToFood{};
	goToFood.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> food{request.getNeareastAgentType(myself, 1)};
		if(food.empty()) { return 1;}
		else if(request.distanceBetweenAgent(myself, food[0]) > 5.f) { return 2; }

		return 3;
	};

	goToFood.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::Move;
		currentChoice.target = request.getNeareastAgentType(myself, 1)[0];

		return currentChoice;
	};

	Node eating{};
	eating.nextState = [](Gg::Entity myself, EngineRequest &request) { return 3; };
	eating.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::Eat;
		currentChoice.target = request.getNeareastAgentType(myself, 1)[0];

		return currentChoice;
	};

	Mode eatMode{0};
	eatMode.addNode(eatBegin);
	eatMode.addNode(searchForFood);
	eatMode.addNode(goToFood);
	eatMode.addNode(eating);
	eatMode.simulate = [](Gg::Entity agent, Gg::GulgEngine &engine) {

		std::shared_ptr<Gg::Component::Float> hunger{ 
			std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(agent, "Hunger"))
		};

		hunger->value = 100.f;
	};




	Node drinkBegin{};
	drinkBegin.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> water{request.getNeareastAgentType(myself, 2)};
		if(water.empty()) { return 1; }
		else if(request.distanceBetweenAgent(myself, water[0]) > 1.f) { return 2; }

		return 3;
	};

	Node searchForWater{};
	searchForWater.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> water{request.getNeareastAgentType(myself, 2)};
		if(water.empty()) { return 1; }

		return 2;
	};

	searchForWater.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::RandomMove;
		currentChoice.target = Gg::NoEntity;

		return currentChoice;
	};

	Node goToWater{};
	goToWater.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> water{request.getNeareastAgentType(myself, 2)};
		if(water.empty()) { return 1; }
		else if(request.distanceBetweenAgent(myself, water[0]) > request.entityHitboxSize(myself)) { return 2; }

		return 3;
	};

	goToWater.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::Move;
		currentChoice.target = request.getNeareastAgentType(myself, 2)[0];

		return currentChoice;
	};

	Node drinking{};
	drinking.nextState = [](Gg::Entity myself, EngineRequest &request) { return 3; };
	drinking.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::Drink;
		currentChoice.target = request.getNeareastAgentType(myself, 2)[0];

		return currentChoice;
	};

	Mode drinkMode{0};
	drinkMode.addNode(drinkBegin);
	drinkMode.addNode(searchForWater);
	drinkMode.addNode(goToWater);
	drinkMode.addNode(drinking);
	drinkMode.simulate = [](Gg::Entity agent, Gg::GulgEngine &engine) {

		std::shared_ptr<Gg::Component::Float> thirst{ 
			std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(agent, "Thirst"))
		};

		thirst->value = 100.f;
	};




	Node randomMoveNode{};
	randomMoveNode.nextState = [](Gg::Entity myself, EngineRequest &request) { return 0; };

	randomMoveNode.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::RandomMove;
		currentChoice.target = Gg::NoEntity;

		return currentChoice;
	};


	Node beginReproduction{};
	beginReproduction.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> partners{request.getPartners(myself)};
		if(partners.empty()) { return 1; }

		if(request.distanceBetweenAgent(myself, partners[0]) > request.entityHitboxSize(myself)) { return 2; }

		return 3;
	};

	Node searchForPartner{};
	searchForPartner.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> partners{request.getPartners(myself)};
		if(partners.empty()) { return 1; }

		return 2;
	};

	searchForPartner.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::RandomMove;
		currentChoice.target = Gg::NoEntity;

		return currentChoice;
	};

	Node goToPartner{};
	goToPartner.nextState = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<Gg::Entity> partners{request.getPartners(myself)};
		if(partners.empty()) { return 1; }
		else if(request.distanceBetweenAgent(myself, partners[0]) > request.entityHitboxSize(myself)) { return 2; }

		return 3;
	};

	goToPartner.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::Move;

		std::vector<Gg::Entity> partners{request.getPartners(myself)};
		if(!partners.empty()) { currentChoice.target = partners[0]; }
		else { currentChoice.target = myself; }

		return currentChoice;
	};

	Node reproduce{};
	reproduce.nextState = [](Gg::Entity myself, EngineRequest &request) { 

		std::vector<Gg::Entity> partners{request.getPartners(myself)};
		if(!partners.empty() && request.distanceBetweenAgent(myself, partners[0]) < 5.f) { return 3; }

		return 2; 
	};

	reproduce.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::Reproduction;
		std::vector<Gg::Entity> partners{request.getPartners(myself)};
		if(!partners.empty()) { currentChoice.target = request.getPartners(myself)[0]; }
		else { currentChoice.target = Gg::NoEntity; }
		

		return currentChoice;
	};

	Mode reproductionMode{0};
	reproductionMode.addNode(beginReproduction);
	reproductionMode.addNode(searchForPartner);
	reproductionMode.addNode(goToPartner);
	reproductionMode.addNode(reproduce);
	reproductionMode.simulate = [](Gg::Entity agent, Gg::GulgEngine &engine) {

		std::shared_ptr<Gg::Component::Float> reproduce{ 
			std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(agent, "Reproduction"))
		};

		reproduce->value = 100.f;
	};


	Node randomMove{};
	randomMove.nextState = [](Gg::Entity myself, EngineRequest &request) { return 0; };
	randomMove.getAction = [](Gg::Entity myself, EngineRequest &request) {

		IAChoice currentChoice;
		currentChoice.choice = Choice::RandomMove;
		currentChoice.target = Gg::NoEntity;

		return currentChoice;
	};



	Mode randomMoveMode{0};
	randomMoveMode.addNode(randomMoveNode);
	randomMoveMode.simulate = [](Gg::Entity agent, Gg::GulgEngine &engine) {};


	std::shared_ptr<FSM> fsm{std::make_shared<FSM>()};
	fsm->addMode(eatMode);
	fsm->addMode(drinkMode);
	fsm->addMode(reproductionMode);
	fsm->addMode(randomMoveMode);

	fsm->selectMode = [](Gg::Entity myself, EngineRequest &request) {

		std::vector<float> fitnessResult;
		fitnessResult.resize(4);
		for(unsigned int i{0}; i < 4; i++) { fitnessResult[i] = request.getFitnessWithChoice(myself, i); }

		float bestFitness{0.f};
		unsigned int selectedMode{0};

		for(unsigned int i{0}; i < 4; i++) {

			if(fitnessResult[i] > bestFitness) {

				bestFitness = fitnessResult[i];
				selectedMode = i;
			}

		}


		return selectedMode;
	};


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

Gg::Entity reproduction(Gg::GulgEngine &engine, const Gg::Entity animal1, const Gg::Entity animal2) {

	Gg::Entity newAnimal{engine.cloneEntity(animal1)};

	std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "Hunger"))->value = 100.f;
	std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "Thirst"))->value = 100.f;
	std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "Death"))->value = 100.f;
	std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "Reproduction"))->value = 100.f;

    std::default_random_engine randomEngine { static_cast<long unsigned int>(std::time(nullptr)) };
    std::uniform_int_distribution<unsigned int> chooseLegacy{1, 2};
    std::uniform_real_distribution<float> spontaneousMutationChance{0, 1}, spontaneousMutationRatio{-0.2f, 0.2f};

    std::shared_ptr<Gg::Component::Float> hungerDecreaseNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "HungerDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> hungerDecrease1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "HungerDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> hungerDecrease2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "HungerDecrease"))
	};

	if(chooseLegacy(randomEngine) == 1) { hungerDecreaseNew->value = hungerDecrease1->value; }
	else { hungerDecreaseNew->value = hungerDecrease2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { hungerDecreaseNew->value *= spontaneousMutationRatio(randomEngine); }







	std::shared_ptr<Gg::Component::Float> thirstDecreaseNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "ThirstDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> thirstDecrease1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "ThirstDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> thirstDecrease2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "ThirstDecrease"))
	};

	if(chooseLegacy(randomEngine) == 1) { thirstDecreaseNew->value = thirstDecrease1->value; }
	else { thirstDecreaseNew->value = thirstDecrease2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { thirstDecreaseNew->value *= spontaneousMutationRatio(randomEngine); }










	std::shared_ptr<Gg::Component::Float> deathDecreaseNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "DeathDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> deathDecrease1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "DeathDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> deathDecrease2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "DeathDecrease"))
	};

	if(chooseLegacy(randomEngine) == 1) { deathDecreaseNew->value = deathDecrease1->value; }
	else { deathDecreaseNew->value = deathDecrease2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { deathDecreaseNew->value *= spontaneousMutationRatio(randomEngine); }








	std::shared_ptr<Gg::Component::Float> reproductionDecreaseNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "ReproductionDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> reproductionDecrease1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "ReproductionDecrease"))
	};

	std::shared_ptr<Gg::Component::Float> reproductionDecrease2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "ReproductionDecrease"))
	};

	if(chooseLegacy(randomEngine) == 1) { reproductionDecreaseNew->value = reproductionDecrease1->value; }
	else { reproductionDecreaseNew->value = reproductionDecrease2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { reproductionDecreaseNew->value *= spontaneousMutationRatio(randomEngine); }






	std::shared_ptr<Gg::Component::Float> speedNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "MaxSpeed"))
	};

	std::shared_ptr<Gg::Component::Float> speed1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "MaxSpeed"))
	};

	std::shared_ptr<Gg::Component::Float> speed2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "MaxSpeed"))
	};

	if(chooseLegacy(randomEngine) == 1) { speedNew->value = speed1->value; }
	else { speedNew->value = speed2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { speedNew->value *= spontaneousMutationRatio(randomEngine); }






	std::shared_ptr<Gg::Component::Float> viewNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "ViewRadius"))
	};

	std::shared_ptr<Gg::Component::Float> view1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "ViewRadius"))
	};

	std::shared_ptr<Gg::Component::Float> view2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "ViewRadius"))
	};

	if(chooseLegacy(randomEngine) == 1) { viewNew->value = view1->value; }
	else { viewNew->value = view2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { viewNew->value *= spontaneousMutationRatio(randomEngine); }













	std::shared_ptr<Gg::Component::Float> hungerFitnessNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "HungerFitness"))
	};

	std::shared_ptr<Gg::Component::Float> hungerFitness1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "HungerFitness"))
	};

	std::shared_ptr<Gg::Component::Float> hungerFitness2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "HungerFitness"))
	};

	if(chooseLegacy(randomEngine) == 1) { hungerFitnessNew->value = hungerFitness1->value; }
	else { hungerFitnessNew->value = hungerFitness2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { hungerFitnessNew->value *= spontaneousMutationRatio(randomEngine); }



	std::shared_ptr<Gg::Component::Float> thirstFitnessNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "ThirstFitness"))
	};

	std::shared_ptr<Gg::Component::Float> thirstFitness1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "ThirstFitness"))
	};

	std::shared_ptr<Gg::Component::Float> thirstFitness2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "ThirstFitness"))
	};

	if(chooseLegacy(randomEngine) == 1) { thirstFitnessNew->value = thirstFitness1->value; }
	else { thirstFitnessNew->value = thirstFitness2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { thirstFitnessNew->value *= spontaneousMutationRatio(randomEngine); }












	std::shared_ptr<Gg::Component::Float> reproductionFitnessNew{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(newAnimal, "ReproductionFitness"))
	};

	std::shared_ptr<Gg::Component::Float> reproductionFitness1{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal1, "ReproductionFitness"))
	};

	std::shared_ptr<Gg::Component::Float> reproductionFitness2{ 
		std::static_pointer_cast<Gg::Component::Float>(engine.getComponent(animal2, "ReproductionFitness"))
	};

	if(chooseLegacy(randomEngine) == 1) { reproductionFitnessNew->value = reproductionFitness1->value; }
	else { reproductionFitnessNew->value = reproductionFitness2->value; }

	if(spontaneousMutationChance(randomEngine) <= 0.15f) { reproductionFitnessNew->value *= spontaneousMutationRatio(randomEngine); }







	




	return newAnimal;
}