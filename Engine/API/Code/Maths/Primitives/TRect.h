#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Functions/MathsFunctions.h"

namespace ae
{
	/// \ingroup math
	/// <summary>
	/// 2D Rectangle with float coordinates. <para/>
	/// |( Left, Top )----------| <para/>
	/// |------( Right, Bottom )| <para/>
	/// </summary>
	template<typename T>
	class TRect
	{
	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		TRect();

		/// <summary>
		/// Build rectangle from four coordinates.
		/// </summary>
		/// <param name="_Left">The top left X coordinates.</param>
		/// <param name="_Top">The top left Y coordinates.</param>
		/// <param name="_Right">The bottom right X coordinates.</param>
		/// <param name="_Bottom">The bottom right Y coordinates.</param>
		TRect( T _Left, T _Top, T _Right, T _Bottom );

        /// <summary>
        /// Test if two rectangle intersect each other.
        /// </summary>
        /// <param name="_Other">Other rectangle to do the intersection test with.</param>
        /// <param name="_WithBoundaries">
        /// If True, edges of the rectangle are considered.
        /// That means, if the <paramref name="_Other"/> touch the calling rectangle on an edge
        /// the function will return True.
        /// If this parameter is set to false, then the function will return False
        /// if the intersection is on an edge.
        /// </param>
        /// <returns>True if the rectangles intersect themselves, false otherwise.</returns>
        Bool Intersects( const TRect<T>& _Other, Bool _WithBoundaries = True ) const;

        /// <summary>
        /// Test if a rectangle contains another one.
        /// </summary>
        /// <param name="_Other">Other rectangle to do the contain test with.</param>
        /// <param name="_WithBoundaries">
        /// If True, edges of the rectangle are considered.
        /// That means, if <paramref name="_Other"/> touch the calling rectangle on an edge
        /// but it still inside, the function will return True.
        /// If this parameter is set to false, then the function will return False
        /// if the contained rectangle touches an edge.
        /// </param>
        /// <returns>True if the calling rectangle contains <paramref name="_Other"/>, false otherwise.</returns>
        Bool Contains( const TRect<T>& _Other, Bool _WithBoundaries = True ) const;

        /// <summary>Retrieve the width of the rectangle.</summary>
        /// <returns>Width of the rectangle.</returns>
        float GetWidth() const;

        /// <summary>Retrieve the height of the rectangle.</summary>
        /// <returns>height of the rectangle.</returns>
        float GetHeight() const;

	public:
		/// <summary>X coordinate of the top left corner.</summary>
		T Left;

		/// <summary>Y coordinate of the top left corner.</summary>
		T Top;

		/// <summary>X coordinate of the bottom right corner.</summary>
		T Right;

		/// <summary>Y coordinate of the bottom right corner.</summary>
		T Bottom;
	};

#include "TRect.inl"


	/// \ingroup math
	/// <summary>Rectangle with floating point precision coordinates.</summary>
	using FloatRect = TRect<float>;

	/// \ingroup math
	/// <summary>Rectangle with integer precision coordinates.</summary>
	using IntRect = TRect<Int32>;

} // ae

