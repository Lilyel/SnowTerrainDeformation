#pragma once

#include "../../../Toolbox/Toolbox.h"
#include "Mesh3D.h"

namespace ae
{
	/// \ingroup graphics
	/// <summary>
	/// Simple 3D colored plane.<para/>
	/// The normal of the plane by default is the Y axis.
	/// </summary>
	/// <seealso cref="Mesh3D" />
	/// <seealso cref="Drawable" />
	class AERO_CORE_EXPORT PlaneMesh : public Mesh3D
	{
	public:
		/// <summary>Create a colored plane with a side size.</summary>
		/// <param name="_Size">The size of cube side size.</param>
		/// <param name="_SubdivisionWidth">Number of face along the width of the plane.</param>
		/// <param name="_SubdivisionHeight">Number of face along the height of the plane.</param>
		PlaneMesh( const float _Size = 1.0f, Uint32 _SubdivisionWidth = 1, Uint32 _SubdivisionHeight = 1 );


		/// <summary>Set the side size of the plane.</summary>
		/// <param name="_Size">The new size to apply.</param>
		void SetSize( const float _Size );

		/// <summary>Retrieve the size of the plane.</summary>
		/// <returns>The size of the plane.</returns>
		float GetSize() const;

		
		/// <summary>Retrieve the number of the face along the width of the plane.</summary>
		/// <returns>The number of face along the width of the plane.</returns>
		Uint32 GetSubdivisionWidth() const;

		/// <summary>Set the number of the face along the width of the plane.</summary>
		/// <param name="_Subdvision">The new number of face along the width of the plane.</param>
		void SetSubdivisionWidth( Uint32 _Subdvision );

		/// <summary>Retrieve the number of the face along the height of the plane.</summary>
		/// <returns>The number of face along the height of the plane.</returns>
		Uint32 GetSubdivisionHeight() const;

		/// <summary>Set the number of the face along the height of the plane.</summary>
		/// <param name="_Subdvision">The new number of face along the height of the plane.</param>
		void SetSubdivisionHeight( Uint32 _Subdvision );


		/// <summary>
		/// Function called by the editor.
		/// It allows the class to expose some attributes for user editing.
		/// Think to call all inherited class function too when overloading.
		/// </summary>
		virtual void ToEditor() override;

	private:
		/// <summary>Create the plane mesh according to the stored parameters.</summary>
		void GeneratePlaneMesh();

	private:
		/// <summary>Size of the plane.</summary>
		float m_Size;

		/// <summary>Number of face along the width of the plane.</summary>
		Uint32 m_SubdivisionWidth;

		/// <summary>Number of face along the height of the plane.</summary>
		Uint32 m_SubdivisionHeight;
	};
} // ae
