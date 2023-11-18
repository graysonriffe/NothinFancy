#pragma once
#include <Windows.h>

#include "Input/Event.h"
#include "nf/Config.h"

namespace nf {
	class Window {
	public:
		using EventQueue = std::queue<input::Event*>;

		Window(const char* title);

		RECT getMonitor();
		void show(bool show = true);
		void update();
		EventQueue& getQueue();
		HWND getHandle() const;
		void setType(DisplayConfig::Mode mode);
		void hideCursor(bool hide);

		~Window();
	private:
		void registerClass() const;
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void handleMouseButtons(input::Code button, bool pressed);

		HWND m_handle;
		const HINSTANCE m_hInst;
		const PCWSTR m_wndClassName;

		const DWORD m_windowedStyle;
		const DWORD m_bFullscreenStyle;

		bool m_hideCursor;

		EventQueue m_events;
	};
}