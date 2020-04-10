#include "HighlightMesh.hpp"

#define v0 glm::vec3{-0.01f, -0.01f, -0.01f}
#define v1 glm::vec3{-0.01f, -0.01f, +1.01f}
#define v2 glm::vec3{-0.01f, +1.01f, -0.01f}
#define v3 glm::vec3{-0.01f, +1.01f, +1.01f}
#define v4 glm::vec3{+1.01f, -0.01f, -0.01f}
#define v5 glm::vec3{+1.01f, -0.01f, +1.01f}
#define v6 glm::vec3{+1.01f, +1.01f, -0.01f}
#define v7 glm::vec3{+1.01f, +1.01f, +1.01f}

#define Xm v0, v2, v3, v0, v1, v3
#define Xp v4, v6, v7, v4, v5, v7

#define Ym v0, v1, v5, v0, v4, v5
#define Yp v2, v3, v7, v2, v6, v7

#define Zm v0, v2, v6, v0, v4, v6
#define Zp v1, v3, v7, v1, v5, v7

#define nXm {-1, 0, 0}
#define nXp {+1, 0, 0}
#define nYm { 0,-1, 0}
#define nYp { 0,+1, 0}
#define nZm { 0, 0,-1}
#define nZp { 0, 0,+1}

/*   3----7
    /|   /|
   2 +- 6 |
   | 1--+-5
   |/   |/
   0----4
*/

#define vertices std::vector<glm::vec3>{Xm, Xp, Ym, Yp, Zm, Zp}
#define normals std::vector<glm::vec3>{nXm, nXm, nXm, nXm, nXm, nXm,	\
					 nXp, nXp, nXp, nXp, nXp, nXp,	\
					 nYm, nYm, nYm, nYm, nYm, nYm,	\
					 nYp, nYp, nYp, nYp, nYp, nYp,	\
					 nZm, nZm, nZm, nZm, nZm, nZm,	\
					 nZp, nZp, nZp, nZp, nZp, nZp}
#define uvs std::vector<glm::vec2>{}
#define indices std::vector<GLuint> {0, 1, 2, 3, 4, 5,		\
				       6, 7, 8, 9, 10, 11,	\
				       12, 13, 14, 15, 16, 17,	\
				       18, 19, 20, 21, 22, 23,	\
				       24, 25, 26, 27, 28, 29,	\
				       30, 31, 32, 33, 34, 35}

HighlightMesh::HighlightMesh() :
	Mesh::Mesh(vertices, normals, uvs, indices)
{

}
