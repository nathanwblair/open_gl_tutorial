#include "Assets/AnimatedMeshShader.h"

AnimatedMeshShader::AnimatedMeshShader(string _path) : MeshShader(_path) {
}

void AnimatedMeshShader::UpdateBones(glm::mat4 * bones, int numBones) {
	SetArrayUniform<glm::mat4>("Bones", bones, numBones);
}