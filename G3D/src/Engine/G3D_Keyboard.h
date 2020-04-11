#pragma once
#include <queue>
#include <bitset>
#include <optional>

namespace G3D
{
	class Keyboard
	{
		friend class Window;
	public:
		class Event
		{
		public:
			enum class Type
			{
				Press,
				Release,
			};
		private:
			Type type;
			unsigned char code;
		public:
			Event(Type type, u8 code) noexcept
				:
				type(type),
				code(code)
			{}
			bool IsPress() const noexcept
			{
				return type == Type::Press;
			}
			bool IsRelease() const noexcept
			{
				return type == Type::Release;
			}
			unsigned char GetCode() const noexcept
			{
				return code;
			}
		};
	public:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		// key event stuff
		bool KeyIsPressed(u8 keycode) const noexcept;
		std::optional<Event> ReadKey() noexcept;
		bool KeyIsEmpty() const noexcept;
		void FlushKey() noexcept;
		// char event stuff
		std::optional<char> ReadChar() noexcept;
		bool CharIsEmpty() const noexcept;
		void FlushChar() noexcept;
		void Flush() noexcept;
		// autorepeat control
		void EnableAutorepeat() noexcept;
		void DisableAutorepeat() noexcept;
		bool AutorepeatIsEnabled() const noexcept;
		void OnKeyPressed(u16 keycode) noexcept;
		void OnKeyReleased(u16 keycode) noexcept;
		void OnChar(i8 character) noexcept;
	private:
		void ClearState() noexcept;
		template<typename T>
		static void TrimBuffer(std::queue<T>& buffer) noexcept;
	private:
		static constexpr u16 nKeys = 256u;
		static constexpr u16 bufferSize = 16u;
		bool autorepeatEnabled = false;
		std::bitset<nKeys> keystates;
		std::queue<Event> keybuffer;
		std::queue<char> charbuffer;
	};
}