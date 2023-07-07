#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "ShaderResource.h"

class Shader {

	static const int maxTextures = 5;
	// Pointer to Shader Resource
	ShaderResource* sr;

	// Shader attributes
	GLuint sId, vertexShader, fragmentShader;

	GLint positionAttribute;
	GLint colorAttribute;
	GLint normAttribute;
	GLint uvAttribute;
	GLint uv2Attribute;

	GLint heightUniform;

	GLint modelmatrixUniform;
	GLint viewmatrixUniform;
	GLint projectionmatrixUniform;

	GLint camerapositionUniform;
	GLint textureUniform[maxTextures];
	GLint textureCubeUniform;

	GLint smallradiusUniform;
	GLint bigradiusUniform;
	GLint fogcolorUniform;

	GLint timeUniform;
	GLint dispMaxUniform;

	GLint ambientalColorUniform;
	GLint ambientalRatioUniform;

	GLint specPowerUniform;
	GLint diffuseColorUniform;
	GLint specularColorUniform;
	GLint directionUniform;

public:

	// Constructors
	Shader();
	explicit Shader(ShaderResource* sr);

	// Shader Load
	int Load();

	// Getters
	ShaderResource* GetSr() const;
	GLuint GetSId() const;
	GLuint GetVertexShader() const;
	GLuint GetFragmentShader() const;
	GLint GetPositionAttribute() const;
	GLint GetColorAttribute() const;
	GLint GetNormAttribute() const;
	GLint GetUvAttribute() const;
	GLint GetModelmatrixUniform() const;
	GLint GetViewmatrixUniform() const;
	GLint GetProjectionmatrixUniform() const;
	GLint GetUv2Attribute() const;
	GLint GetHeightUniform() const;
	GLint GetTextureUniform(int index) const;
	GLint GetTextureCubeUniform() const;
	GLint GetCamerapositionUniform() const;
	GLint GetSmallradiusUniform() const;
	GLint GetBigradiusUniform() const;
	GLint GetFogcolorUniform() const;
	GLint GetTimeUniform() const;
	GLint GetDispMaxUniform() const;
	GLint GetAmbientalColorUniform() const;
	GLint GetAmbientalRatioUniform() const;
	GLint GetSpecPowerUniform() const;
	GLint GetDiffuseColorUniform() const;
	GLint GetSpecularColorUniform() const;
	GLint GetDirectionUniform() const;
	// Destructor
	~Shader();
};