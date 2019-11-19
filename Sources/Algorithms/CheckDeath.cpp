#include "Algorithms/CheckDeath.hpp"

CheckDeath::CheckDeath(Gg::GulgEngine &gulgEngine, std::vector<Gg::Entity> &entitiesToKill): 

	AbstractAlgorithm{gulgEngine},
	m_entitiesToKill{entitiesToKill} {

	m_signature = gulgEngine.getComponentSignature("Hunger");
	m_signature += gulgEngine.getComponentSignature("Thirst");
	m_signature += gulgEngine.getComponentSignature("Death");
}

CheckDeath::~CheckDeath() {}



void CheckDeath::apply() {

	if(!opened) {
		std::string const nomFichier("./Stats/nombre.txt");
	    std::ofstream monFlux(nomFichier.c_str());	
	    opened = true;
	}

    //fichier = fopen("./Stats/nombre.txt", "a");

	//monFlux.open("./Stats/nombre.txt", std::ios::trunc);
		for(Gg::Entity currentEntity: m_entitiesToApply) {

		std::shared_ptr<Gg::Component::Float> hunger{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Hunger"))
		};

		std::shared_ptr<Gg::Component::Float> thirst{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Thirst"))
		};

		std::shared_ptr<Gg::Component::Float> death{ 
			std::static_pointer_cast<Gg::Component::Float>(m_gulgEngine.getComponent(currentEntity, "Death"))
		};

		//if (fichier != NULL)
    	//{
    		monFlux << hunger->value << " " << thirst->value << " " << death->value << std::endl;
    		/*const char* chaine = (std::to_string(hunger->value) + " " + std::to_string(thirst->value) + " " + std::to_string(death->value) + "\n").c_str();
    		std::cout << chaine << std::endl;
    		fputs(chaine,fichier);*/
    	//} 
    	//fclose(fichier);

		if(hunger->value <= 0.f || thirst->value <= 0.f || death->value <= 0.f) { m_entitiesToKill.emplace_back(currentEntity); }

	}
}