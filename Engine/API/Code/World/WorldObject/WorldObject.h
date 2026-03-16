#ifndef _WORLDOBJECT_AERO_H_
#define _WORLDOBJECT_AERO_H_

#include "../../Toolbox/Toolbox.h"
#include "../../Idioms/NotCopiable/NotCopiable.h"

#include "../World.h"

namespace ae
{
    /// \ingroup scene
    /// <summary>
    /// Class that represent an object in the world. <para/>
    /// Identified by an unique ID.
    /// </summary>
    class AERO_CORE_EXPORT WorldObject : public NotCopiable
    {
    public:
        /// <summary>Initialize the object and add it to the world hierarchy.</summary>
        WorldObject();

        /// <summary>Destroy an object and remove it from the world.</summary>
        virtual ~WorldObject();

        /// <summary>Retrieve the ID that identify this object in the world.</summary>
        /// <returns>ID in the world of the object.</returns>
        const World::ObjectID& GetObjectID() const;

        /// <summary>Make this object active or not in the world.</summary>
        /// <param name="_IsEnabled">The new object active state.</param>
        virtual void SetEnabled( Bool _IsEnabled );

        /// <summary>Retrieve the active state of the object.</summary>
        /// <returns>True if the object is active in the world, false otherwise.</returns>
        virtual Bool IsEnabled() const;

        /// <summary>Retrieve the name of the object.</summary>
        /// <returns>Name of the object.</returns>
        virtual const std::string& GetName() const;


        /// <summary>Set the name of the object.</summary>
        /// <param name="_NewName">The new name to apply to the object.</param>
        virtual void SetName( const std::string& _NewName );



        /// <summary>Retrieve the parent of the object. Can be nullptr.</summary>
        /// <returns>The parent of the object. Can be nullptr.</returns>
        const WorldObject* GetParent() const;

        /// <summary>
        /// Set the parent of the object. <para/>
        /// The object will be added as child of the <paramref name="_Parent"/>.<para/>
        /// If there was already a parent set, the object will be removed from its children.
        /// </summary>
        /// <param name="_Parent">The new parent of the object.</param>
        void SetParent( WorldObject* _Parent );

        /// <summary>
        /// Detach the parent from the object.<para/>
        /// The object will be removed from its children.
        /// </summary>
        void Unparent();

        /// <summary>Does the object have a parent ?</summary>
        /// <returns>True if the object has a parent, False otherwise.</returns>
        Bool HasParent() const;

        /// <summary>Retrieve the children at the provided index.</summary>
        /// <param name="_Index">Index of the child.</param>
        /// <returns>The child at the given index.</returns>
        const WorldObject* GetChild( Uint32 _Index ) const;

        /// <summary>Retrieve the child having the provided ID.</summary>
        /// <param name="_ID">ID of the child to retrieve.</param>
        /// <returns>The child with the given ID. Nullptr if not found.</returns>
        const WorldObject* GetChild( const World::ObjectID& _ID ) const;

        /// <summary>Retrieve the object children array.</summary>
        /// <returns>The object children array.</returns>
        const std::vector<WorldObject*>& GetChildren() const;


        /// <summary>Add a child to the object.</summary>
        /// <param name="_Child">The child to add.</param>
        void AddChild( WorldObject* _Child );

        /// <summary>Remove the child at the given index from the children array.</summary>
        /// <param name="_Index">Index of the child to remove.</param>
        void RemoveChild( Uint32 _Index );

        /// <summary>Remove the child with the given ID from the children array.</summary>
        /// <param name="_ID">ID of the child to remove.</param>
        void RemoveChild( const World::ObjectID& _ID );

        /// <summary>Remove the child from the children array.</summary>
        /// <param name="_Child">IChild to remove.</param>
        void RemoveChild( WorldObject* _Child );

        /// <summary>Does the object has children ?</summary>
        /// <returns>True if the object has at least one child, False otherwise.</returns>
        Bool HasChildren() const;

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor();

    private:

        /// <summary>
        /// Parent (or unparent if nullptr is provided as <paramref name="_Parent"/>) the two provided object.<para/>
        /// The <paramref name="_Parent"/> will become the parent of the <paramref name="_Child"/>.<para/>
        /// The <paramref name="_Child"/> will be added to the children of the <paramref name="_Parent"/>.
        /// </summary>
        /// <param name="_Parent">The parent of the two object.</param>
        /// <param name="_Child">The new child of the <paramref name="_Parent"/></param>
        static void MakeRelation( WorldObject* _Parent, WorldObject* _Child );

        /// <summary>Retrieve a child in the children array from its object ID.</summary>
        /// <param name="_ID">The object ID of the child to find.</param>
        /// <returns>The child if found, nullptr otherwise.</returns>
        WorldObject* GetChildFromObjectID( const World::ObjectID& _ID ) const;

        /// <summary>Remove the child with the given ID from the children array.</summary>
        /// <param name="_ID">The ID of the child to remove from the array.</param>
        void RemoveChildFromArray( const World::ObjectID& _ID );

    private:
        /// <summary>Unique ID of the object in the world.</summary>
        World::ObjectID m_ObjectID;

        /// <summary>Is this object active in the world ?</summary>
        Bool m_IsEnabled;

        /// <summary>Name of the object.</summary>
        std::string m_Name;

        /// <summary>Parent of the object.</summary>
        WorldObject* m_Parent;

        /// <summary>Children of the object.</summary>
        std::vector<WorldObject*> m_Children;
    };

} // ae

#endif // _WORLDOBJECT_AERO_H_
