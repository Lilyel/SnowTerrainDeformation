#pragma once

#include "../../Toolbox/Toolbox.h"

#include "../Keys/Keys.h"
#include "../Keys/KeyState.h"

#include "../../Maths/Vector/Vector2.h"

#include "../InputFunctionalities/InputFunctionalities.h"



namespace ae
{
	class Window;
	class AeroCore;

	namespace Input
	{
		/// \ingroup input
		/// <summary>
		/// Process the inputs received from the system.<para/>
		/// Inputs a relayed by Window.<para/>
		/// This class store informations about each keys and mouse.<para/>
		/// The access to this data must be done via InputFunctionalities.
		/// </summary>
		class AERO_CORE_EXPORT InputManager
		{
			friend class Window;
			friend class AeroCore;

			friend void ae::priv::Input::UpdatePlatformLockKeys( InputManager& );

		public:
			/// <summary>
			/// Default constructor.<para/>
			/// Initialize each keys to State::Up.
			/// </summary>
			InputManager();

			/// <summary>Retrieve the state of a key (Up, Reeased, Down, Pressed).</summary>
			/// <param name="_Key">Key to retrieve the state of.</param>
			/// <returns>The state of the key.</returns>
			State GetKeyState( const Key& _Key ) const;

			/// <summary>Retrieve the position of the mouse in the application area.</summary>
			/// <returns>Mouse position in the application space.</returns>
			const Vector2& GetMousePosition() const;

			/// <summary>Retrieve the movement of the mouse between this frame and the previous.</summary>
			/// <returns>Mouse move delta.</returns>
			const Vector2& GetMouseDeltaMove() const;

			/// <summary>
			/// Gets the mouse delta scroll from the last frame.
			/// </summary>
			/// <returns>The mouse delta scroll from the last frame.</returns>
			const Int16& GetMouseDeltaWheel() const;

			/// <summary>Determine if according to the possible combinaisons, caps are active.</summary>
			/// <returns>True if the caps are active, False otherwise.</returns>
			const Bool& IsCaps() const;

			/// <summary>Determine if a keyboard key was hit this frame.</summary>
			/// <returns>True if the a key was hit, False otherwise.</returns>
			const Bool& IsKeyboardHit() const;
			
			/// <summary>Determine if a mouse button was hit this frame.</summary>
			/// <returns>True if the a button was hit, False otherwise.</returns>
			const Bool& IsMouseHit() const;

			/// <summary>Determine if a gamepad button was hit this frame.</summary>
			/// <returns>True if the a button was hit, False otherwise.</returns>
			const Bool& IsGamepadHit() const;

		private:
			/// <summary>Process a low level input event.</summary>
			/// <param name="_Key">Key to up to date.</param>
			/// <param name="_NewState">New state of the key to apply.</param>
			void HandleKeyEvent( const Key& _Key, const State& _NewState );
			
			/// <summary>
			/// Update each key state.<para/>
			/// Must be called before handling low level events.
			/// </summary>
			void Update();

			/// <summary>Update the mouse position stored. Called from window.</summary>
			/// <param name="_MousePosition">The new mouse position</param>
			void UpdateMousePosition( const Vector2& _MousePosition );
			
			/// /// <summary>Update the mouse delta move stored. Called from window.</summary>
			/// <param name="_DeltaMove">The new mouse position.</param>
			void UpdateMouseDeltaMove( const Vector2& _DeltaMove );

			/// <summary>Sets the mouse delta scroll.</summary>
			/// <param name="_Delta">The scroll delta from the last frame.</param>
			void UpdateMouseDeltaWheel( const Int16 _Delta );


			/// <summary>Reset each key to up.</summary>
			void Reset();

			
			/// <summary>Update locking bit of a key state according to the given Bool.</summary>
			/// <param name="_Key">Key to update.</param>
			/// <param name="_IsLock">New lock state to apply.</param>
			void UpdateLockKeys( const Key& _Key, const Bool _IsLock );

			
			/// <summary>If the key given is valid, set the boolean stored to true.</summary>
			/// <param name="_Key">Key hit to check.</param>
			void HitKey( const Key& _Key );

			
			/// <summary>
			/// Process if with all combinaisons of caps
			/// possibilities, the caps is active or not.
			/// </summary>
			void CheckCaps();

		private:
			/// <summary>Determine if the caps are active or not.</summary>
			Bool m_IsCaps;

			/// <summary>Determine if a key of the keyboard was hit in this frame.</summary>
			Bool m_IsKeyboardHit;
			
			/// <summary>Determine if a mouse button was hit in this frame.</summary>
			Bool m_IsMouseHit;
			
			/// <summary>Determine if a gamepad button was hit in this frame.</summary>
			Bool m_IsGamepadHit;

			
			/// <summary>
			/// Mouse position in the application area.<para/>
			/// (0, 0) at top left corner of the application.
			/// </summary>
			Vector2 m_MousePosition;
			
			/// <summary>Movement of the mouse between this frame and the previous.</summary>
			Vector2 m_MouseDeltaMove;
			
			/// <summary>Mouse position during the previous frame.</summary>
			Vector2 m_MousePositionPreviousFrame;

			/// <summary>The delta scroll from last frame of the wheel.</summary>
			Int16 m_MouseDeltaWheel;


			/// <summary>State of each key.</summary>
			State m_Keys[Cast( Int16, Key::KeyCount )];
		};

	} // Input

} // ae
