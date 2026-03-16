#include "Light.h"

#include "../../Aero/Aero.h"
#include "../../Maths/Functions/MathsFunctions.h"
#include "../../Editor/TypesToEditor/LightToEditor.h"


namespace ae
{
    Light::Light() :
        m_Type( LightType::Unknown )
    {
        World& worldRef = Aero.GetWorld();
        worldRef.AddLightToList( this );

        SetIntensity( 1.0f );

        SetName( std::string( "Light_" ) + std::to_string( GetObjectID() ) );
    }
    Light::~Light()
    {
        World& worldRef = Aero.GetWorld();
        worldRef.RemoveLightFromList( this );
    }

    void Light::SetColor( const Color& _Color )
    {
        m_Color = _Color;
    }

    const Color& Light::GetColor() const
    {
        return m_Color;
    }

    void Light::SetIntensity( float _Intensity )
    {
        m_Intensity = Math::Max( _Intensity, 0.0f );
    }

    float Light::GetIntensity() const
    {
        return m_Intensity;
    }

    Light::LightType Light::GetLightType() const
    {
        return m_Type;
    }

    void Light::ToEditor()
    {
        WorldObject::ToEditor();
        Transform::ToEditor();
        priv::ui::LightToEditor( *this );
    }

} // ae