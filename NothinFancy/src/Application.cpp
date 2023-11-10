#include "pch.h"
#include "nf/Application.h"

#include "version.h"
#include "nf/Utility/util.h"
#include "Window.h"

namespace nf {
	Application::Application(Config config)
		: m_config(config)
		, m_running(false)
	{}

	void Application::run() {
#ifdef _DEBUG
		SetThreadDescription(GetCurrentThread(), L"Main Thread");
		std::string consoleTitle = std::format("Nothin' Fancy Debug Console (" NFVERSION ") - {} {}", m_config.appName, m_config.appVersion);
		SetConsoleTitle(util::toWideStr(consoleTitle).c_str());
#endif
		NFLog(std::format("Nothin' Fancy {}", NFVERSION));
		NFLog(std::format("Starting {} {}", m_config.appName, m_config.appVersion));

		m_running = true;

		{
			Window window(m_config.appName);
			window.show();

			while (m_running) {
				window.update();
				handleWindowEvents(window);
			}
		}

		NFLog("Shutdown");
	}

	void Application::quit() {
		m_running = false;
	}

	void Application::handleWindowEvents(Window& window) {
		Window::EventQueue& queue = window.getQueue();

		while (!queue.empty()) {
			Event* curr = queue.front();
			switch (curr->getType()) {
				case Event::Type::KeyPress: {
					input::Key key = dynamic_cast<KeyEvent*>(curr)->key;
					NFLog(std::format("Event - KeyPress (Code = {})", static_cast<unsigned char>(key)));
					break;
				}

				case Event::Type::KeyRelease: {
					input::Key key = dynamic_cast<KeyEvent*>(curr)->key;
					NFLog(std::format("Event - KeyRelease (Code = {})", static_cast<unsigned char>(key)));
					break;
				}

				case Event::Type::WindowClose:
					NFLog("Event - WindowClose");
					quit();
					break;
			}

			queue.pop();
		}

	}

	Application::~Application() {

	}
}