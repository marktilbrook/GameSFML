#include "EventManager.h"



EventManager::EventManager() : m_hasFocus(true)
{
	LoadBindings();
}


EventManager::~EventManager()
{
	for(auto& iter : m_bindings)
	{
		delete iter.second;
		iter.second = nullptr;
	}
}

bool EventManager::AddBinding(Binding* a_binding)
{
	if (m_bindings.find(a_binding->m_name) != m_bindings.end())
	{
		return false;
		
	}
	return m_bindings.emplace(a_binding->m_name, a_binding).second;
}

bool EventManager::RemoveBinding(std::string a_name)
{
	auto itr = m_bindings.find(a_name);
	if (itr == m_bindings.end())
	{
		return false;
	}
	delete itr->second;
	m_bindings.erase(itr);
	return true;
}

void EventManager::SetFocus(const bool & a_focus)
{
	m_hasFocus = a_focus;
}

void EventManager::HandleEvent(sf::Event & a_event)
{
	// Handling SFML events.
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->m_events) {
			EventType sfmlEvent = (EventType)a_event.type;
			if (e_itr.first != sfmlEvent) { continue; }
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) {
				if (e_itr.second.m_code == a_event.key.code) {
					// Matching event/keystroke.
					// Increase count.
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) {
				if (e_itr.second.m_code == a_event.mouseButton.button) {
					// Matching event/keystroke.
					// Increase count.
					bind->m_details.m_mouse.x = a_event.mouseButton.x;
					bind->m_details.m_mouse.y = a_event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
					break;
				}
			}
			else {
				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel) {
					bind->m_details.m_mouseWheelDelta = a_event.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind->m_details.m_size.x = a_event.size.width;
					bind->m_details.m_size.y = a_event.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind->m_details.m_textEntered = a_event.text.unicode;
				}
				++(bind->c);
			}
		}
	}


}

void EventManager::Update()
{
	if (!m_hasFocus) { return; }
	for (auto &b_itr : m_bindings) {
		Binding* bind = b_itr.second;
		for (auto &e_itr : bind->m_events) {
			switch (e_itr.first) {
			case(EventType::Keyboard):
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code))) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Mouse):
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code))) {
					if (bind->m_details.m_keyCode != -1) {
						bind->m_details.m_keyCode = e_itr.second.m_code;
					}
					++(bind->c);
				}
				break;
			case(EventType::Joystick):
				// Up for expansion.
				break;
			}
		}

		if (bind->m_events.size() == bind->c) {
			auto callItr = m_callbacks.find(bind->m_name);
			if (callItr != m_callbacks.end()) {
				callItr->second(&bind->m_details);
			}
		}
		bind->c = 0;
		bind->m_details.Clear();
	}
}

void EventManager::LoadBindings()
{
	std::string delimiter = ":";

	std::ifstream bindings;
	bindings.open("res/keys.cfg.txt");
	if (!bindings.is_open()) { std::cout << "! Failed loading keys.cfg." << std::endl; return; }
	std::string line;
	while (std::getline(bindings, line)) {
		std::stringstream keystream(line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof()) {
			std::string keyval;
			keystream >> keyval;
			int start = 0;
			int end = keyval.find(delimiter);
			if (end == std::string::npos) { delete bind; bind = nullptr; break; }
			EventType type = EventType(stoi(keyval.substr(start, end - start)));
			int code = stoi(keyval.substr(end + delimiter.length(),
				keyval.find(delimiter, end + delimiter.length())));
			EventInfo eventInfo;
			eventInfo.m_code = code;

			bind->BindEvent(type, eventInfo);
		}

		if (!AddBinding(bind)) { delete bind; }
		bind = nullptr;
	}
	bindings.close();
}
