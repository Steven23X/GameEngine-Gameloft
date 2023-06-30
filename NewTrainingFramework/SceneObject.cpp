#include "stdafx.h"
#include "SceneObject.h"

#include <iostream>

#include "SceneManager.h"
#include "Vertex.h"

SceneObject::SceneObject(unsigned idSo, const Vector3& position, const Vector3& rotation, const Vector3& scale,
	Model* model, Shader* shader, const std::vector<Texture*>& textures, const bool depthTest, bool isWired)
	: idSo(idSo),
	position(position),
	rotation(rotation),
	scale(scale),
	model(model),
	shader(shader),
	textures(textures),
	depthTest(depthTest),
	isWired(isWired)
{}

Matrix SceneObject::GetModelMatrix() const
{
	Matrix rotX, rotY, rotZ, scaleMatrix, transMatrix;

	rotX.SetRotationX(rotation.x);
	rotY.SetRotationY(rotation.y);
	rotZ.SetRotationZ(rotation.z);
	transMatrix.SetTranslation(position.x, position.y, position.z);
	scaleMatrix.SetScale(scale.x, scale.y, scale.z);


	Matrix modelMatrix = scaleMatrix * rotX * rotY * rotZ * transMatrix;

	return modelMatrix;
}

void SceneObject::Draw() const
{
	glUseProgram(shader->GetSId());

	glBindBuffer(GL_ARRAY_BUFFER, model->GetVboId());
	if (isWired)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->GetWiredIboId());
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->GetIboId());


	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		if (textures[i]->GetTr()->type == "2d")
		{
			glBindTexture(GL_TEXTURE_2D, textures[i]->GetTId());
		}


		if (shader->GetTextureUniform() != -1)
		{
			glUniform1i(shader->GetTextureUniform(), i);
		}
	}


	if (shader->GetPositionAttribute() != -1)
	{
		glEnableVertexAttribArray(shader->GetPositionAttribute());
		glVertexAttribPointer(shader->GetPositionAttribute(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->GetColorAttribute() != -1)
	{
		glEnableVertexAttribArray(shader->GetColorAttribute());
		glVertexAttribPointer(shader->GetColorAttribute(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (shader->GetUvAttribute() != -1)
	{
		glEnableVertexAttribArray(shader->GetUvAttribute());
		glVertexAttribPointer(shader->GetUvAttribute(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(5 * sizeof(Vector3)));
	}


	if (SceneManager::GetInstance()->GetActiveCamera() != nullptr)
	{
		const Matrix modelMatrix = GetModelMatrix();

		const Matrix viewMatrix = SceneManager::GetInstance()->GetActiveCamera()->GetViewMatrix();

		const Matrix projectionMatrix = SceneManager::GetInstance()->GetActiveCamera()->GetProjectionMatrix();

		if (shader->GetModelmatrixUniform() != -1)
		{
			glUniformMatrix4fv(shader->GetModelmatrixUniform(), 1, GL_FALSE, (GLfloat*)modelMatrix.m);
		}


		if (shader->GetViewmatrixUniform() != -1)
		{
			glUniformMatrix4fv(shader->GetViewmatrixUniform(), 1, GL_FALSE, (GLfloat*)viewMatrix.m);
		}

		if (shader->GetProjectionmatrixUniform() != -1)
		{
			glUniformMatrix4fv(shader->GetProjectionmatrixUniform(), 1, GL_FALSE, (GLfloat*)projectionMatrix.m);
		}

		if (shader->GetTextureUniform() != -1)
		{
			glUniform1i(shader->GetTextureUniform(), 0);
		}

	}

	if (isWired)
		glDrawElements(GL_LINES, model->GetNrIndiciWired(), GL_UNSIGNED_SHORT, 0);
	else
		glDrawElements(GL_TRIANGLES, model->GetNrIndex(), GL_UNSIGNED_SHORT, 0);

	if (textures.empty() == false)
		glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}