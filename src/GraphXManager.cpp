#include "GraphXManager.hpp"

int GraphXManager::AddMesh(std::string strID, std::unique_ptr<Mesh> mesh)
{
	if (meshIDmap.find(strID) == std::end(meshIDmap)) {
		meshes.push_back(std::move(mesh));
		int id(meshes.size() - 1);
		meshIDmap[strID] = id;
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
	} else {
		throw std::runtime_error("Duplicate texture ID");
	}
}

Mesh& GraphXManager::GetMesh(int meshID)
{
	if (meshID >= meshes.size()) {
		throw std::runtime_error("Mesh ID does not exist");
	} else {
		return *(meshes[meshID]);
	}
}

Program& GraphXManager::GetProgram(int programID)
{
	if (programID >= programs.size()) {
		throw std::runtime_error("Program ID does not exist");
	} else {
		return *(programs[programID]);
	}
}

Texture& GraphXManager::GetTexture(int textureID)
{
	if (textureID >= textures.size()) {
		throw std::runtime_error("Texture ID does not exist");
	} else {
		return *(textures[textureID]);
	}
}

void GraphXManager::AddRenderingInstance(RenderingInstance rendering_instance)
{
	rendering_instances.push(rendering_instance);
}

