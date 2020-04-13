#include "GraphXManager.hpp"

#include "Log.hpp"

void GraphXManager::GetBillBoardScale(std::string textureID, glm::vec3& scale)
{
	auto& tex = GetTexture(GetTextureID(textureID));
	float h = (float) tex.GetPixelHeight() / PIXELS_PER_CUBE;
	float w = (float) tex.GetPixelWidth() / PIXELS_PER_CUBE;
	scale.x = scale.z = w;
	scale.y = h;
}

int GraphXManager::AddMesh(std::string strID, std::unique_ptr<Mesh> mesh)
{
	if (meshIDmap.find(strID) == std::end(meshIDmap)) {
		meshes.push_back(std::move(mesh));
		int id(meshes.size() - 1);
		meshIDmap[strID] = id;
		LOG("Loaded mesh %s with ID %d.", strID.c_str(), id);
		return id;
	} else {
		throw std::runtime_error("Duplicate mesh ID");
	}
}

int GraphXManager::AddProgram(std::string strID, std::unique_ptr<Program> program)
{
	if (programIDmap.find(strID) == std::end(programIDmap)) {
		programs.push_back(std::move(program));
		int id(programs.size() - 1);
		programIDmap[strID] = id;
		LOG("Loaded program %s with ID %d.", strID.c_str(), id);
		return id;
	} else {
		throw std::runtime_error("Duplicate program ID");
	}
}

int GraphXManager::AddTexture(std::string strID, std::unique_ptr<Texture> texture)
{
	if (textureIDmap.find(strID) == std::end(textureIDmap)) {
		textures.push_back(std::move(texture));
		int id(textures.size() - 1);
		textureIDmap[strID] = id;
		LOG("Loaded texture %s with ID %d.", strID.c_str(), id);
		return id;
	} else {
		throw std::runtime_error("Duplicate texture ID");
	}
}

Mesh& GraphXManager::GetMesh(int meshID)
{
	return *(meshes.at(meshID));
}

Program& GraphXManager::GetProgram(int programID)
{
	return *(programs.at(programID));
}

Texture& GraphXManager::GetTexture(int textureID)
{
	return *(textures.at(textureID));
}

