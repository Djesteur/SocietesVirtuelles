#ifndef FSM_HPP
#define FSM_HPP

#include <functional>

#include "Components/Component.hpp"
#include "Components/IAChoice.hpp"

#include "EngineRequest.hpp"


struct Node {

	public:

		Node() {}

		std::function<unsigned int(Gg::Entity, EngineRequest&)> nextState;
		std::function<IAChoice(Gg::Entity, EngineRequest&)> getAction;
};


struct Mode {

	public:

		Mode(const unsigned int begin): 
			m_beginNode{begin},
			m_currentNode{begin} {}


		void addNode(const Node newNode) { m_nodes.emplace_back(newNode); }

		void reset() { m_currentNode = m_beginNode; }

		IAChoice moveForward(Gg::Entity myself, EngineRequest &request) {

			m_currentNode = m_nodes[m_currentNode].nextState(myself, request);
			return m_nodes[m_currentNode].getAction(myself, request);
		}

		std::function<void(Gg::Entity, Gg::GulgEngine &engine)> simulate;

	private:

		const unsigned int m_beginNode;
		unsigned int m_currentNode;

		std::vector<Node> m_nodes;
};

struct FSM: public Gg::Component::AbstractComponent {

	public:

		FSM() {}
		FSM(const FSM &fsmComponent):
			m_currentMode{fsmComponent.m_currentMode},
			m_oldMode{fsmComponent.m_oldMode},
			m_modes{fsmComponent.m_modes},
			selectMode{fsmComponent.selectMode} {}

		virtual std::shared_ptr<AbstractComponent> clone() const { return std::static_pointer_cast<AbstractComponent>(std::make_shared<FSM>(*this)); }         

		void addMode(Mode newMode) { m_modes.emplace_back(newMode); }

		IAChoice makeChoice(Gg::Entity myself, EngineRequest &request) { 

			m_currentMode = selectMode(myself,request);
			if(m_currentMode != m_oldMode) { m_modes[m_currentMode].reset(); }
			m_oldMode = m_currentMode;
			return m_modes[m_currentMode].moveForward(myself, request);
		}

		std::function<void(Gg::Entity, Gg::GulgEngine &engine)> getModeSimulate(const unsigned int i) { return m_modes[i].simulate; }


		std::function<unsigned int(Gg::Entity, EngineRequest&)> selectMode;

	private:

		unsigned int m_currentMode, m_oldMode;


		std::vector<Mode> m_modes;
};

#endif