#pragma once

struct RenderingInstance {
	glm::mat4 model_matrix;
	int textureID[4];
	int programID;
	int meshID;
};

