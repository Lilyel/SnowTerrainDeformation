#pragma once


#include "../../../Toolbox/Toolbox.h"
#include "Mesh2D.h"
#include "../../../Maths/Primitives/TRect.h"

namespace ae
{
    class Texture;

    /// \ingroup graphics
    /// <summary>
    /// 2D holder for texture. Can be drawn on a Renderer.
    /// </summary>
    /// <seealso cref="Mesh2D"/>
    /// \par Example :
    /// \snippet SpriteSample/Code/main.cpp Sprite example
    class AERO_CORE_EXPORT QuadMesh : public Mesh2D
    {
    public:
        /// <summary>Create a colored cube with a side size.</summary>
        /// <param name="_Width">The width of the cube.</param>
        /// <param name="_Height">The height of the cube.</param>
        QuadMesh( float _Width = 1.0f, float _Height = 1.0f );


        /// <summary>Set the side size of the cube.</summary>
        /// <param name="_Width">The new width to apply.</param>
        /// <param name="_Height">The new height to apply.</param>
        void SetSize( float _Width, float _Height );

        /// <summary>Retrieve the size of the quad.</summary>
        /// <returns>The size  (width, height) of the quad.</returns>
        Vector2 GetSize() const;

        /// <summary>Set the width of the quad.</summary>
        /// <param name="_Width">The new width to apply.</param>
        void SetWidth( float _Width );

        /// <summary>Retrieve the width of the quad.</summary>
        /// <returns>The width of the quad.</returns>
        float GetWidth() const;

        /// <summary>Set the height of the quad.</summary>
        /// <param name="_Height">The new height to apply.</param>
        void SetHeight( float _Height );

        /// <summary>Retrieve the height of the quad.</summary>
        /// <returns>The height of the quad.</returns>
        float GetHeight() const;


        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        void ToEditor() override;

    private:
        /// <summary>Create the quad mesh according to the stored parameters.</summary>
        void GenerateQuadMesh();

        /// <summary>Update the position of the vertices according to the stored width and height.</summary>
        /// <param name="_Vertices">The verties to modify.</param>
        void UpdateVerticesPositions( Vertex2DArray& _Vertices );

    private:
        /// <summary>Width of the quad.</summary>
        float m_Width;

        /// <summary>Height of the quad</summary>
        float m_Height;
    };

} // ae
