#include "WorldObject.h"

#include "../../Aero/Aero.h"
#include "../../Debugging/Debugging.h"
#include "../../Editor/TypesToEditor/WorldObjectToEditor.h"

#include <exception>

namespace ae
{
    WorldObject::WorldObject() :
        m_IsEnabled( True ),
        m_Parent( nullptr )
    {
        World& WorldRef = Aero.GetWorld();


        m_ObjectID = WorldRef.AddObjectToWorld( this );
        if( m_ObjectID == World::InvalidObjectID )
        {
            AE_LogError( "Invalid object ID returned by World." );
            return;
        }

        SetName( std::string( "Object_" ) + std::to_string( m_ObjectID ) );
    }

    WorldObject::~WorldObject()
    {
        World& WorldRef = Aero.GetWorld();

        WorldRef.RemoveObjectFromWorld( this );
    }


    const World::ObjectID& WorldObject::GetObjectID() const
    {
        return m_ObjectID;
    }

    void WorldObject::SetEnabled( Bool _IsEnable )
    {
        m_IsEnabled = _IsEnable;
    }

    Bool WorldObject::IsEnabled() const
    {
        return m_IsEnabled;
    }

    const std::string& WorldObject::GetName() const
    {
        return m_Name;
    }
    void WorldObject::SetName( const std::string& _NewName )
    {
        m_Name = _NewName;
    }

    const WorldObject* WorldObject::GetParent() const
    {
        return m_Parent;
    }

    void WorldObject::SetParent( WorldObject* _Parent )
    {
        MakeRelation( _Parent, this );
    }

    void WorldObject::Unparent()
    {
        MakeRelation( nullptr, this );
    }

    Bool WorldObject::HasParent() const
    {
        return m_Parent != nullptr;
    }

    const WorldObject* WorldObject::GetChild( Uint32 _Index ) const
    {
        if( _Index >= Cast( Uint32, m_Children.size() ) )
            throw std::out_of_range( "Invalid child index." );


        return m_Children[_Index];
    }

    const WorldObject* WorldObject::GetChild( const World::ObjectID& _ID ) const
    {
        return GetChildFromObjectID( _ID );
    }

    const std::vector<WorldObject*>& WorldObject::GetChildren() const
    {
        return m_Children;
    }

    void WorldObject::AddChild( WorldObject* _Child )
    {
        MakeRelation( this, _Child );
    }

    void WorldObject::RemoveChild( Uint32 _Index )
    {
        if( _Index >= Cast( Uint32, m_Children.size() ) )
            throw std::out_of_range( "Invalid child index." );

        MakeRelation( nullptr, m_Children[_Index] );
    }

    void WorldObject::RemoveChild( const World::ObjectID& _ID )
    {
        WorldObject* Child = GetChildFromObjectID( _ID );
        if( Child == nullptr )
            return;

        MakeRelation( nullptr, Child );
    }

    void WorldObject::RemoveChild( WorldObject* _Child )
    {
        MakeRelation( nullptr, _Child );
    }

    Bool WorldObject::HasChildren() const
    {
        return !m_Children.empty();
    }

   
    void WorldObject::MakeRelation( WorldObject* _Parent, WorldObject* _Child )
    {
        // Adding invalid children is forbiden.
        if( _Child == nullptr )
            return;

        // Case : Unparent
        if( _Parent == nullptr )
        {
            if( _Child->HasParent() )
            {
                _Child->m_Parent->RemoveChildFromArray( _Child->GetObjectID() );
                _Child->m_Parent = nullptr;
            }

            // Try to unparent an object without parent, leave and do nothing.
            else
                return;
        }

        // Case : New relation
        else
        {
            if( _Child->HasParent() )
            {
                // The parent and child relation is already done. Leave and do nothing.
                if( _Child->m_Parent->GetObjectID() == _Parent->GetObjectID() )
                    return;

                // Remove child from its previous parent if there is.
                else
                    _Child->m_Parent->RemoveChildFromArray( _Child->GetObjectID() );
            }

            // Make the parent-child relation.
            _Child->m_Parent = _Parent;
            _Parent->m_Children.push_back( _Child );
        }
    }


    WorldObject* WorldObject::GetChildFromObjectID( const World::ObjectID& _ID ) const
    {
        std::vector<WorldObject*>::const_iterator ChildIt = std::find_if( m_Children.begin(), m_Children.end(), [&_ID]( const WorldObject* _Child ) -> Bool
        {
            return _Child->GetObjectID() == _ID;
        } );

        return ChildIt == m_Children.end() ? nullptr : *ChildIt;
    }

    void WorldObject::RemoveChildFromArray( const World::ObjectID& _ID )
    {
        m_Children.erase( std::remove_if( m_Children.begin(), m_Children.end(), [&_ID]( const WorldObject* _Child ) -> Bool
        {
            return _Child->GetObjectID() == _ID;
        } ) );
    }



    void WorldObject::ToEditor()
    {
        priv::ui::WorldObjectToEditor( *this );
    }

} // ae