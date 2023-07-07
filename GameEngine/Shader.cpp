#include "stdafx.h"
#include "Shader.h"
#include <string>

// Constructors
Shader::Shader()
= default;

Shader::Shader(ShaderResource* sr) : sId(0), vertexShader(0), fragmentShader(0), positionAttribute(0),
colorAttribute(0), uvAttribute(0),
modelmatrixUniform(0),
viewmatrixUniform(0),
projectionmatrixUniform(0), textureUniform()
{
	this->sr = sr;
}

// Destructor
Shader::~Shader()
{
	glDeleteProgram(sId);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Shader Load
int Shader::Load()
{
	std::string vspath;
	vspath = sr->path + sr->vs;
	const auto pvspath = const_cast<char*>(vspath.c_str());

	std::string fspath;
	fspath = sr->path + sr->fs;
	const auto pfspath = const_cast<char*>(fspath.c_str());

	vertexShader = esLoadShader(GL_VERTEX_SHADER, pvspath);
	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, pfspath);
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	sId = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes

	//attributes
	positionAttribute = glGetAttribLocation(sId, "a_posL");
	colorAttribute = glGetAttribLocation(sId, "a_color");
	normAttribute = glGetAttribLocation(sId, "a_norm");
	uvAttribute = glGetAttribLocation(sId, "a_uv");
	uv2Attribute = glGetAttribLocation(sId, "a_uv2");

	//terrain height
	heightUniform = glGetUniformLocation(sId, "u_height");

	//MVP
	modelmatrixUniform = glGetUniformLocation(sId, "u_modelmatrix");
	viewmatrixUniform = glGetUniformLocation(sId, "u_viewmatrix");
	projectionmatrixUniform = glGetUniformLocation(sId, "u_projectionmatrix");

	//textures
	textureUniform[0] = glGetUniformLocation(sId, "u_textureuniform0");
	textureUniform[1] = glGetUniformLocation(sId, "u_textureuniform1");
	textureUniform[2] = glGetUniformLocation(sId, "u_textureuniform2");
	textureUniform[3] = glGetUniformLocation(sId, "u_textureuniform3");
	textureUniform[4] = glGetUniformLocation(sId, "u_textureuniform4");

	textureCubeUniform = glGetUniformLocation(sId, "u_cubetextureuniform");

	//camera pos
	camerapositionUniform = glGetUniformLocation(sId, "u_cameraposuniform");

	// fog
	smallradiusUniform = glGetUniformLocation(sId, "u_sradius");
	bigradiusUniform = glGetUniformLocation(sId, "u_bradius");
	fogcolorUniform = glGetUniformLocation(sId, "u_fogcolor");

	// fire
	timeUniform = glGetUniformLocation(sId, "u_time");
	dispMaxUniform = glGetUniformLocation(sId, "u_dispmax");

	//ambiental light
	ambientalColorUniform = glGetUniformLocation(sId, "u_ambcolor");
	ambientalRatioUniform = glGetUniformLocation(sId, "u_ambratio");

	// light
	specPowerUniform = glGetUniformLocation(sId, "u_specpower");
	diffuseColorUniform = glGetUniformLocation(sId, "u_diffusecolor");
	specularColorUniform = glGetUniformLocation(sId, "u_specularcolor");
	directionUniform = glGetUniformLocation(sId, "u_direction");
	return 0;
}

// Getters
ShaderResource* Shader::GetSr() const
{
	return sr;
}

GLuint Shader::GetSId() const
{
	return sId;
}

GLuint Shader::GetVertexShader() const
{
	return vertexShader;
}

GLuint Shader::GetFragmentShader() const
{
	return fragmentShader;
}

GLint Shader::GetPositionAttribute() const
{
	return positionAttribute;
}

GLint Shader::GetColorAttribute() const
{
	return colorAttribute;
}

GLint Shader::GetNormAttribute() const
{
	return normAttribute;
}

GLint Shader::GetUvAttribute() const
{
	return uvAttribute;
}

GLint Shader::GetModelmatrixUniform() const
{
	return modelmatrixUniform;
}

GLint Shader::GetViewmatrixUniform() const
{
	return viewmatrixUniform;
}

GLint Shader::GetProjectionmatrixUniform() const
{
	return projectionmatrixUniform;
}

GLint Shader::GetUv2Attribute() const
{
	return uv2Attribute;
}

GLint Shader::GetHeightUniform() const
{
	return heightUniform;
}

GLint Shader::GetTextureUniform(int index) const
{
	if (index >= 0 && index < maxTextures)
	{
		return textureUniform[index];
	}
	return -1;
}

GLint Shader::GetTextureCubeUniform() const
{
	return textureCubeUniform;
}

GLint Shader::GetCamerapositionUniform() const
{
	return camerapositionUniform;
}

GLint Shader::GetSmallradiusUniform() const
{
	return smallradiusUniform;
}

GLint Shader::GetBigradiusUniform() const
{
	return bigradiusUniform;
}

GLint Shader::GetFogcolorUniform() const
{
	return fogcolorUniform;
}

GLint Shader::GetTimeUniform() const
{
	return timeUniform;
}

GLint Shader::GetDispMaxUniform() const
{
	return dispMaxUniform;
}

GLint Shader::GetAmbientalColorUniform() const
{
	return ambientalColorUniform;
}

GLint Shader::GetAmbientalRatioUniform() const
{
	return ambientalRatioUniform;
}

GLint Shader::GetSpecPowerUniform() const
{
	return specPowerUniform;
}

GLint Shader::GetDiffuseColorUniform() const
{
	return diffuseColorUniform;
}

GLint Shader::GetSpecularColorUniform() const
{
	return specularColorUniform;
}

GLint Shader::GetDirectionUniform() const
{
	return directionUniform;
}
