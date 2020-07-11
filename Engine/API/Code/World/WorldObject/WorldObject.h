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

        /// <summary>
        /// Function called by the editor.
        /// It allows the class to expose some attributes for user editing.
        /// Think to call all inherited class function too when overloading.
        /// </summary>
        virtual void ToEditor();

	private:
		/// <summary>Unique ID of the object in the world.</summary>
		World::ObjectID m_ObjectID;

        /// <summary>Is this object active in the world ?</summary>
        Bool m_IsEnabled;

        /// <summary>Name of the object.</summary>
        std::string m_Name;
	};

} // ae

#endif // _WORLDOBJECT_AERO_H_
