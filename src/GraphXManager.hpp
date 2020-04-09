#pragma once

#include <map>
#include <vector>
#include <string>

#include "Program.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Log.hpp"

#include "RenderingInstance.hpp"

class GraphXManager
{
private:
	std::vector<std::unique_ptr<Mesh>> meshes;
	std::vector<std::unique_ptr<Program>> programs;
	std::vector<std::unique_ptr<Texture>> textures;

	std::map<std::string, int> meshIDmap;
	std::map<std::string, int> programIDmap;
	std::map<std::string, int> textureIDmap;

	std::map<int, std::vector<RenderingInstance>> rendering_instances;
	int ri_index;
	static const int PIXELS_PER_CUBE = 32;
public:
	/*!
	 \param textureID name of the billboard texture
	 \param scale proper scale will be stored there
	 */
	void GetBillBoardScale(std::string textureID, glm::vec3& scale);

	/*!
	 \param strID a unique string id, used by outsiders
	 \param mesh a mesh corresponding to the above id
	 \return the integer id of the stored mesh
	 */
	int AddMesh(std::string strID, std::unique_ptr<Mesh> mesh);

	/*!
	 \param strID a unique string id, used by outsiders
	 \param program a program corresponding to the above id
	 \return the integer id of the stored program
	 */
	int AddProgram(std::string strID, std::unique_ptr<Program> program);

	/*!
	 \param strID a unique string id, used by outsiders
	 \param texture a texture corresponding to the above id
	 \return the integer id of the stored texture
	 */
	int AddTexture(std::string strID, std::unique_ptr<Texture> texture);

	Mesh& GetMesh(int meshID);
	Program& GetProgram(int programID);
	Texture& GetTexture(int textureID);

	int GetMeshID(std::string meshID)
	{
		return meshIDmap.at(meshID);
	}
	int GetProgramID(std::string programID)
	{
		return programIDmap.at(programID);
	}
	int GetTextureID(std::string textureID)
	{
		return textureIDmap.at(textureID);
	}

	void AddRenderingInstance(RenderingInstance ri)
	{
		rendering_instances[ri.programID].push_back(ri);
	}
	void ResetRenderingInstances()
	{
		rendering_instances.clear();
	}
	std::vector<RenderingInstance>& GetRenderingInstances(int programID)
	{
		return rendering_instances[programID];
	}
	std::vector<std::unique_ptr<Program>>& GetPrograms()
	{
		return programs;
	}
};

