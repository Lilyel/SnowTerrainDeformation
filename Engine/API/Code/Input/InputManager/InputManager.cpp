#include "InputManager.h"


namespace ae
{
	namespace Input
	{

		InputManager::InputManager()
		{
			Reset();
		}

		State InputManager::GetKeyState( const Key& _Key ) const
		{
			if( _Key < Cast( Key, 0 ) || _Key >= Key::KeyCount )
				return State::StateInvalid;

			return m_Keys[Cast( Int16, _Key )];
		}

		const Vector2& InputManager::GetMousePosition() const
		{
			return m_MousePosition;
		}

		const Vector2& InputManager::GetMouseDeltaMove() const
		{
			return m_MouseDeltaMove;
		}

		const Int16& InputManager::GetMouseDeltaWheel() const
		{
			return m_MouseDeltaWheel;
		}

		const Bool& InputManager::IsCaps() const
		{
			return m_IsCaps;
		}

		const Bool& InputManager::IsKeyboardHit() const
		{
			return m_IsKeyboardHit;
		}

		const Bool& InputManager::IsMouseHit() const
		{
			return m_IsMouseHit;
		}

		const Bool& InputManager::IsGamepadHit() const
		{
			return m_IsGamepadHit;
		}

		void InputManager::HandleKeyEvent( const Key& _Key, const State& _NewState )
		{
			if( !IsKeyValid( _Key ) )
				return;

			if( _NewState == State::Pressed )
			{
				if( m_Keys[Cast( Int16, _Key )] != State::Down )
					m_Keys[Cast( Int16, _Key )] = _NewState;

				HitKey( _Key );
			}

			else if( _NewState == State::Released )
			{
				if( m_Keys[Cast( Int16, _Key )] != State::Up )
					m_Keys[Cast( Int16, _Key )] = _NewState;
			}
		}

		void InputManager::Update()
		{
			m_IsKeyboardHit = False;
			m_IsMouseHit = False;
			m_IsGamepadHit = False;

			for( Int16 CurrentKey = 0; CurrentKey < Cast( Int16, Key::KeyCount ); CurrentKey++ )
			{
				if( m_Keys[CurrentKey] == State::Pressed )
					m_Keys[CurrentKey] = State::Down;

				else if( m_Keys[CurrentKey] == State::Released )
					m_Keys[CurrentKey] = State::Up;
			}

			m_MousePositionPreviousFrame = m_MousePosition;
			m_MouseDeltaMove = Vector2::Zero;
			m_MouseDeltaWheel = 0;

			priv::Input::UpdatePlatformLockKeys( *this );
		}

		void InputManager::UpdateMousePosition( const Vector2& _MousePosition )
		{
			UpdateMouseDeltaMove( _MousePosition - m_MousePositionPreviousFrame );

			m_MousePosition = _MousePosition;
		}

		void InputManager::UpdateMouseDeltaMove( const Vector2& _DeltaMove )
		{
			m_MouseDeltaMove = _DeltaMove;
		}

		void InputManager::UpdateMouseDeltaWheel( const Int16 _Delta )
		{
			m_IsMouseHit = True;
			m_MouseDeltaWheel = _Delta;
		}

		void InputManager::Reset()
		{
			for( Int16 CurrentKey = 0; CurrentKey < Cast( Int16, Key::KeyCount ); CurrentKey++ )
				m_Keys[CurrentKey] = State::Up;

			m_IsCaps = False;
			m_IsKeyboardHit = False;
			m_IsMouseHit = False;
			m_IsGamepadHit = False;

			m_MouseDeltaWheel = 0;
		}

		void InputManager::UpdateLockKeys( const Key& _Key, const Bool _IsLock )
		{
			const Int8& NewLockState = _IsLock ? Cast( Int8, State::Lock ) : 0;
			const Int8& OldState = Cast( Int8, m_Keys[Cast( Int16, _Key )] ) & ( Cast( Int8, State::Pressed )
																				 | Cast( Int8, State::Down )
																				 | Cast( Int8, State::Released )
																				 | Cast( Int8, State::Up ) );
			m_Keys[Cast( Int16, _Key )] = Cast( State, NewLockState | OldState );
		}

		void InputManager::HitKey( const Key& _Key )
		{
			if( IsKeyboardKey( _Key ) )
				m_IsKeyboardHit = True;
			else if( IsMouseKey( _Key ) )
				m_IsMouseHit = True;
			else if( IsGamepadKey( _Key ) )
				m_IsGamepadHit = True;
		}

		void InputManager::CheckCaps()
		{
			Int8 CapsFilter = Cast( Int8, State::Down ) | Cast( Int8, State::Pressed ) | Cast( Int8, State::Lock );

			m_IsCaps = ( Cast( Int8, m_Keys[Cast( Int16, Key::Keyboard_CapsLock )] ) & CapsFilter ) != 0;


			if( ( Cast( Int8, m_Keys[Cast( Int16, Key::Keyboard_LeftShift )] ) & CapsFilter ) != 0 )
				m_IsCaps = !m_IsCaps;

			if( ( Cast( Int8, m_Keys[Cast( Int16, Key::Keyboard_RightShift )] ) & CapsFilter ) != 0 )
				m_IsCaps = !m_IsCaps;
		}

	} // priv
} // ae