#version 330 core

layout (lines) in;
layout (line_strip, max_vertices = 2) out;

in ShaderData
{
	bool IsControlCurve;
} GeomIn[];

out vec4 GeomColor;
uniform vec4 ControlCurveColor;
uniform vec4 CurveColor;

void main()
{
	// Skip line that link curve and control curve.
	if( GeomIn[0].IsControlCurve != GeomIn[1].IsControlCurve )
		return;

	// If we are drawing a control line.
	if( GeomIn[0].IsControlCurve )
	{
		gl_Position = gl_in[0].gl_Position;
		GeomColor = ControlCurveColor;
		EmitVertex();

		gl_Position = gl_in[1].gl_Position;
		GeomColor = ControlCurveColor;
		EmitVertex();

		EndPrimitive();
	}
	// If we are drawing a interpolated line.
	else
	{
		gl_Position = gl_in[0].gl_Position;
		GeomColor = CurveColor;
		EmitVertex();

		gl_Position = gl_in[1].gl_Position;
		GeomColor = CurveColor;
		EmitVertex();

		EndPrimitive();
	}
}	