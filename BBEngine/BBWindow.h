#pragma once
#include <Windows.h>
#include "Core.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "BBException.h"

namespace BB
{
	class BBWindow
	{
	private:
		// singleton manages registration/cleanup of window class
		class WindowClass
		{
		public:
			static const char* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* wndClassName = "BBEngineWindow";
			static WindowClass wndClass;
			HINSTANCE hInst;
		};
	public:
		BBWindow(int width, int height, const char* name);
		~BBWindow();
		BBWindow(const BBWindow&) = delete;
		BBWindow& operator=(const BBWindow&) = delete;
		void SetTitle(const std::string& title);
		void EnableCursor() noexcept;
		void DisableCursor() noexcept;
		bool CursorEnabled() const noexcept;
		static std::optional<int> ProcessMessages() noexcept;
	private:
		void ConfineCursor() noexcept;
		void FreeCursor() noexcept;
		void ShowCursor() noexcept;
		void HideCursor() noexcept;
		void EnableImGuiMouse() noexcept;
		void DisableImGuiMouse() noexcept;
		static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMsgRedirect(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	public:
		Keyboard kbd;
		Mouse mouse;
	private:
		bool cursorEnabled = true;
		int width;
		int height;
		HWND hWnd;
		std::vector<BYTE> rawBuffer;
		std::string commandLine;
	};
}


