#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector2.h"
#include "../Matrix/Matrix3x3.h"

namespace ae
{
	/// \ingroup math
	/// <summary>
	/// Useful to do 2D transformations like translation, rotation and scaling.
	/// </summary>
	/// <seealso cref="Matrix3x3"/>
	/// <seealso cref="Vector2"/>
	/// \par Example :
	/// \snippet Transformations2DSample/Code/main.cpp Transform2D example
	class AERO_CORE_EXPORT Transform2D
	{
	public:
		/// <summary>Initialize a transform with position, rotation and scale.</summary>
		/// <param name="_Position">Translation to apply to the transform.</param>
		/// <param name="_Rotation">Rotation to apply to the transform.</param>
		/// <param name="_Scale">Scale to apply to the transform.</param>
		Transform2D( const Vector2& _Position = Vector2( 0.0f, 0.0f ), float _Rotation = 0.0f, const Vector2& _Scale = Vector2( 1.0f, 1.0f ) );

		/// <summary>Default destructor, we define it to mark it as virtual for subclasses.</summary>
		virtual ~Transform2D() = default;


		/// <summary>Change the position (override the current).</summary>
		/// <param name="_Position">The new 2D position.</param>
		/// <returns>Calling transform with the new position.</returns>
		Transform2D& SetPosition( const Vector2& _Position );

		/// <summary>Change the position (override the current).</summary>
		/// <param name="_X">The new X position.</param>
		/// <param name="_Y">The new Y position.</param>
		/// <returns>Calling transform with the new position.</returns>
		Transform2D& SetPosition( float _X, float _Y );

		/// <summary>Add a 2D offset to the current position.</summary>
		/// <param name="_Offset">The offset to apply.</param>
		/// <returns>Calling transform with the new position.</returns>
		Transform2D& Translate( const Vector2& _Offset );

		/// <summary>Add a 2D offset to the current position.</summary>
		/// <param name="_OffsetX">The offset X to apply.</param>
		/// <param name="_OffsetY">The offset Y to apply.</param>
		/// <returns>Calling transform with the new position.</returns>
		Transform2D& Translate( float _OffsetX, float _OffsetY );

		/// <summary>Get the current 2D position.</summary>
		/// <returns>Transform 2D position.</returns>
		const Vector2& GetPosition() const;

		/// <summary>Set the transform rotaiton (override the current).</summary>
		/// <param name="_Angle">The new angle in radians.</param>
		/// <returns>The calling transform with the new rotation.</returns>
		Transform2D& SetRotation( float _Angle );

		/// <summary>Rotate the transform.</summary>
		/// <param name="_Angle">The angle in radians to add to the current rotation.</param>
		/// <returns>The calling transform with the new rotation.</returns>
		Transform2D& Rotate( float _Angle );

		/// <summary>Get the transform rotation in radians.</summary>
		/// <returns>The current rotation in radians.</returns>
		float GetRotation() const;

		/// <summary>Set the scale of the transform (overide the current).</summary>
		/// <param name="_Scale">The new scale.</param>
		/// <returns>The calling transform with the new scale.</returns>
		Transform2D& SetScale( const Vector2& _Scale );

		/// <summary>Set the scale of the transform (overide the current).</summary>
		/// <param name="_ScaleX">The new scale X.</param>
		/// <param name="_ScaleY">The new scale Y.</param>
		/// <returns>The calling transform with the new scale.</returns>
		Transform2D& SetScale( float _ScaleX, float _ScaleY );

		/// <summary>Scale the transform.</summary>
		/// <param name="_Scale">The scale to add to the current.</param>
		/// <returns>The calling transform with the new scale.</returns>
		Transform2D& Scale( const Vector2& _Scale );

		/// <summary>Scale the transform.</summary>
		/// <param name="_ScaleX">The scale X to add to the current.</param>
		/// <param name="_ScaleY">The scale Y to add to the current.</param>
		/// <returns>The calling transform with the new scale.</returns>
		Transform2D& Scale( float _ScaleX, float _ScaleY );

		/// <summary>Get the transform scale.</summary>
		/// <returns>2D scale of the transform.</returns>
		const Vector2& GetScale() const;

		/// <summary>Set the transformations origin.</summary>
		/// <param name="_Origin">The new origin for the transformations.</param>
		/// <returns>The calling transform with the new origin.</returns>
		Transform2D& SetOrigin( const Vector2& _Origin );

		/// <summary>Set the transformations origin.</summary>
		/// <param name="_OriginX">The new origin X for the transformations.</param>
		/// <param name="_OriginY">The new origin Y for the transformations.</param>
		/// <returns>The calling transform with the new origin.</returns>
		Transform2D& SetOrigin( float _OriginX, float _OriginY );

		/// <summary>Get the current transformations origin.</summary>
		/// <returns>The transformations origin.</returns>
		const Vector2& GetOrigin() const;

		/// <summary>Combine the current transformations with transformations from another transform.</summary>
		/// <remarks>The origin doesn't change.</remarks>
		/// <param name="_Other">The other transform to combine the transformations with.</param>
		void Combine( const Transform2D& _Other );
		
		/// <summary>Combine two transforms and their transformations in a single transform.</summary>
		/// <remarks>The origin is the origin of <paramref name="_TransformA"/>.</remarks>
		/// <param name="_TransformA">The first transform to combine.</param>
		/// <param name="_TransformB">The second transform to combine.</param>
		/// <returns>The combination of the transformations of <paramref name="_TransformA"/> and  <paramref name="_TransformB"/>.</returns>
		static Transform2D Combine( const Transform2D& _TransformA, const Transform2D& _TransformB );
		
		/// <summary>Combine two transforms and their transformations in a single transform.</summary>
		/// <remarks>The origin is the origin of <paramref name="_TransformA"/>.</remarks>
		/// <param name="_Result">The combination of the transformations of <paramref name="_TransformA"/> and  <paramref name="_TransformB"/>.</param>
		/// <param name="_TransformA">The first transform to combine.</param>
		/// <param name="_TransformB">The second transform to combine.</param>
		static void Combine( AE_Out Transform2D& _Result, const Transform2D& _TransformA, const Transform2D& _TransformB );

		/// <summary>Apply the current transformations to a point.</summary>
		/// <param name="_Point">The point to transform.</param>
		/// <returns>The point transformed.</returns>
		Vector2 TransformPoint( const Vector2& _Point );

		/// <summary>Apply the current transformations to a point.</summary>
		/// <param name="_Point">The point to transform and store the result in it.</param>
		void TransformPoint( AE_InOut Vector2& _Point );

		/// <summary>Get the matrix with the transformations</summary>
		/// <returns>3x3 matrix holding the transformations.</returns>
		const Matrix3x3& GetMatrix();

		/// <summary>Get a copy of the matrix with the transformations.</summary>
		/// <returns>Copy of the 3x3 matrix holding the transformations.</returns>
		Matrix3x3 GetUpdatedMatrix();

		/// <summary>Get the inverse of the matrix with the transformations.</summary>
		/// <returns>Inverse of the 3x3 matrix holding the transformations.</returns>
		Matrix3x3 GetInversedMatrix();

		/// <summary>Get the transpose of the matrix with the transformations.</summary>
		/// <returns>Transpose of the 3x3 matrix holding the transformations.</returns>
		Matrix3x3 GetTransposedMatrix();

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor();

	protected:
		/// <summary>Process the tranform's matrix.</summary>
		void UpdateTransform();

		/// <summary>Additionnal process to do in UpdateTransform.</summary>
		virtual void OnTransformUpdated();

		/// <summary>Alert subclasses of changement of transform component.</summary>
		virtual void OnTransformChanged();

	protected:
		/// <summary>2D position (translation).</summary>
		Vector2 m_Position;
		/// <summary>2D scale.</summary>
		Vector2 m_Scale;
		/// <summary>2D rotation (angle in radians).</summary>
		float m_Rotation;
		/// <summary>2D origin (transformation pivot).</summary>
		Vector2 m_Origin;

		/// <summary>Combined transformations as a 3x3 matrix.</summary>
		Matrix3x3 m_Transform;

		/// <summary>Used to know if the matrix must be updated or not.</summary>
		Bool m_UpdateTransform;
	};

} // ae

