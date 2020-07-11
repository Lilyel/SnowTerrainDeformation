#pragma once

#include "../../Toolbox/Toolbox.h"
#include "../Vector/Vector3.h"
#include "../Rotator/Rotator.h"

namespace ae
{
    /// \ingroup math
     /// <summary>
     /// Useful to do 3D transformations like translation, rotation and scaling.
     /// </summary>
     /// <seealso cref="Matrix4x4"/>
     /// <seealso cref="Vector3"/>
    class AERO_CORE_EXPORT Transform
    {
    public:
        /// <summary>
        /// Default constructor. <para/>
        /// Set transform to identity : position and rotation to 0 and scale to 1.
        /// </summary>
        Transform();

        /// <summary>
        /// Default constructor. <para/>
        /// Rotation set to 0 and scale to 1.
        /// </summary>
        /// <param name="_Position">Translation to apply to the transform.</param>
        Transform( const Vector3& _Position );

        /// <summary>Constructor with all component of the transform.</summary>
        /// <param name="_Position">Translation to apply to the transform.</param>
        /// <param name="_Rotation">Rotation to apply to the transform.</param>
        /// <param name="_Scale">Scale to apply to the transform.</param>
        Transform( const Vector3& _Position, const Rotator& _Rotation, const Vector3& _Scale );

        /// <summary>Default destructor, we define it to mark it as virtual for subclasses.</summary>
        virtual ~Transform() = default;


        /// <summary>Set the position of the transform.</summary>
        /// <param name="_X">New position x.</param>
        /// <param name="_Y">New position y.</param>
        /// <param name="_Z">New position z.</param>
        void SetPosition( float _X, float _Y, float _Z );

        /// <summary>Set the position of the transform.</summary>
        /// <param name="_Position">New position.</param>
        void SetPosition( const ae::Vector3& _Position );

        /// <summary>Translate the position of the transform.</summary>
        /// <param name="_Offset">Offset to add to the position.</param>
        void Translate( const Vector3& _Offset );

        /// <summary>Translate the position of the transform.</summary>
        /// <param name="_X">Offset to add to the x position.</param>
        /// <param name="_Y">Offset to add to the y position.</param>
        /// <param name="_Z">Offset to add to the z position.</param>
        void Translate( float _X, float _Y, float _Z );


        /// <summary>Get the transform position.</summary>
        /// <returns>Transform position.</returns>
        const Vector3& GetPosition() const;

        /// <summary>Set the rotation of the transform.</summary>
        /// <param name="_Pitch">Rotation around the right axis.</param>
        /// <param name="_Yaw">Rotation around the up axis.</param>
        /// <param name="_Roll">Rotation around the look axis.</param>
        void SetRotation( float _Pitch, float _Yaw, float _Roll );


        /// <summary>Set the rotation of the transform.</summary>
        /// <param name="_Angles">Angles to apply to the transform ( x = Pitch, y = Yaw, z = Roll ).</param>
        void SetRotation( const Vector3& _Angles );

        /// <summary>Set the rotation of the transform.</summary>
        /// <param name="_Rotation">The new rotation to apply.</param>
        void SetRotation( const Rotator& _Rotation );

        /// <summary>Add a rotation to the current rotation of the transform.</summary>
        /// <param name="_Pitch">Rotation around the right axis.</param>
        /// <param name="_Yaw">Rotation around the up axis.</param>
        /// <param name="_Roll">Rotation around the look axis.</param>
        void Rotate( float _Pitch, float _Yaw, float _Roll );

        /// <summary>Add a rotation to the current rotation of the transform.</summary>
        /// <param name="_Angles">Angles to apply to the transform ( x = Pitch, y = Yaw, z = Roll ).</param>
        void Rotate( const Vector3& _Angles );

        /// <summary>Add a rotation to the current rotation of the transform.</summary>
        /// <param name="_Rotation">The new rotation to add to the current one.</param>
        void Rotate( const Rotator& _Rotation );

        /// <summary>Get the transform rotation as euler angle.</summary>
        /// <returns>Transform rotation ( x = Pitch, y = Yaw, z = Roll ).</returns>
        const Vector3& GetRotationAngles() const;

        /// <summary>Get the transform rotation as a rotator.</summary>
        /// <returns>Transform rotation.</returns>
        const Rotator& GetRotation() const;


        /// <summary>Set the scale of the transform.</summary>
        /// <param name="_X">New scale x.</param>
        /// <param name="_Y">New scale y.</param>
        /// <param name="_Z">New scale z.</param>
        void SetScale( float _X, float _Y, float _Z );

        /// <summary>Set the scale of the transform.</summary>
        /// <param name="_Scale">New scale .</param>
        void SetScale( const Vector3& _Scale );

        /// <summary>Combine a new scale the current one.</summary>
        /// <param name="_X">Scale to add to the x scale.</param>
        /// <param name="_Y">Scale to add to the y scale.</param>
        /// <param name="_Z">Scale to add to the z scale.</param>
        void Scale( float _X, float _Y, float _Z );

        /// <summary>Scale the scale of the transform.</summary>
        /// <param name="_Scale">Scale to add to the scale.</param>
        void Scale( const Vector3& _Scale );

        /// <summary>Get the transform scale.</summary>
        /// <returns>Transform scale.</returns>
        const Vector3& GetScale() const;


        /// <summary>Combine the calling transform with another one.</summary>
        /// <param name="_Other">Other transform to combine transformations with.</param>
        void Combine( const Transform& _Other );


        /// <summary>Combine two transforms.</summary>
        /// <param name="_Transform1">First transform from which take transformations.</param>
        /// <param name="_Transform2">Second transform from which take transformations.</param>
        /// <returns>Transform containing the transformations from both transforms.</returns>
        static Transform Combine( const Transform& _Transform1, const Transform& _Transform2 );

        /// <summary>
        /// Combine two transforms and put the result in the third one. <para/>
        /// This function do the same thing as "Transform Combine( Transform, Transform )". <para/>
        /// But it will not create a new transform and copy it for the return, so this function is recommended for optimizations.
        /// </summary>
        /// <param name="_Transform1">First transform from which take transformations.</param>
        /// <param name="_Transform2">Second transform from which take transformations.</param>
        /// <param name="_Result">Transform to fill with the transformations from both transforms.</param>
        static void Combine( const Transform& _Transform1, const Transform& _Transform2, Transform& _Result );


        /// <summary>Get the transform as a matrix4x4.</summary>
        /// <returns>Matrix4x4 representing the transform.</returns>
        const Matrix4x4& GetMatrix();

        /// <summary>
        /// Get a copy of updated transform as a matrix4x4. <para/>
        /// Used for internal rendering functions.
        /// </summary>
        /// <returns>Matrix4x4 representing the transform.</returns>
        Matrix4x4 GetUpdatedMatrix();

        /// <summary>Get the transform as a matrix4x4 inversed.</summary>
        /// <returns>Matrix4x4 inversed representing the transform.</returns>
        Matrix4x4 GetInversedMatrix();


        /// <summary>Get the transform as a matrix 4x4 transposed.</summary>
        /// <returns>Matrix4x4 transposed representing the transform.</returns>
        Matrix4x4 GetTransposedMatrix();


        /// <summary>Get the forward vector of the transform.</summary>
        /// <returns>Forward vector of the transform.</returns>
        Vector3 GetForward();

        /// <summary>Get the left vector of the transform.</summary>
        /// <returns>Left vector of the transform.</returns>
        Vector3 GetLeft();


        /// <summary>Get the Up vector of the transform.</summary>
        /// <returns>Up vector of the transform.</returns>
        Vector3 GetUp();


        /// <summary>Set the pivot of the transformation.</summary>
        /// <param name="_Pivot">The new pivot to apply.</param>
        void SetPivot( const Vector3& _Pivot );

        /// <summary>Retrieve the current transformation pivot.</summary>
        /// <returns>The current transformation pivot.</returns>
        const Vector3& GetPivot();

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
        /// <summary>3D position.</summary>
        Vector3 m_Position;

        /// <summary>3D rotation.</summary>
        Rotator m_Rotation;

        /// <summary>3D Scale.</summary>
        Vector3 m_Scale;

        /// <summary>Transformation pivot.</summary>
        Vector3 m_Pivot;

        /// <summary>Transform as matrix 4x4.</summary>
        Matrix4x4 m_Transform;

    private:
        /// <summary>Used to know if the matrix must be updated or not.</summary>
        Bool m_UpdateTransform;
    };

} // ae
