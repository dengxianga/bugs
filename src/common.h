#include <cmath>
#include <cstdio>
#include <cuda.h>
#include <cuda_runtime.h>
#include <thrust/random.h>
#include <util/checkCUDAError.h>
#include <util/tiny_gltf_loader.h>
#include "rasterizeTools.h" 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "util/utilityCore.hpp"
namespace {

	typedef unsigned short VertexIndex;
	typedef glm::vec3 VertexAttributePosition;
	typedef glm::vec3 VertexAttributeNormal;
	typedef glm::vec2 VertexAttributeTexcoord;
	typedef unsigned char TextureData;

	typedef unsigned char BufferByte;

	enum PrimitiveType{
		Point = 1,
		Line = 2,
		Triangle = 3
	};

	struct VertexOut {
		glm::vec4 pos;

		// TODO: add new attributes to your VertexOut
		// The attributes listed below might be useful, 
		// but always feel free to modify on your own

		glm::vec3 eyePos;	// eye space position used for shading
		glm::vec3 eyeNor;	// eye space normal used for shading, cuz normal will go wrong after perspective transformation
		glm::vec3 col;
		glm::vec2 texcoord0;
		TextureData* dev_diffuseTex = NULL;
		int texWidth, texHeight;
		int texture;
		// ...
	};

	struct Primitive {
		PrimitiveType primitiveType = Triangle;	// C++ 11 init
		VertexOut v[3];

		TextureData* dev_diffuseTex;
		int texWidth, texHeight;
		int texture;
	};

	struct Fragment {
		glm::vec3 color;

		// TODO: add new attributes to your Fragment
		// The attributes listed below might be useful, 
		// but always feel free to modify on your own

		glm::vec3 eyePos;	// eye space position used for shading
		glm::vec3 eyeNor;
		VertexAttributeTexcoord texcoord0;
		TextureData* dev_diffuseTex;
		int texWidth, texHeight;
		int texture;
		// ...
	};

	struct PrimitiveDevBufPointers {
		int primitiveMode;	//from tinygltfloader macro
		PrimitiveType primitiveType;
		int numPrimitives;
		int numIndices;
		int numVertices;

		// Vertex In, const after loaded
		VertexIndex* dev_indices;
		VertexAttributePosition* dev_position;
		VertexAttributeNormal* dev_normal;
		VertexAttributeTexcoord* dev_texcoord0;

		// Materials, add more attributes when needed
 
		// TODO: add more attributes when needed
		TextureData* dev_diffuseTex;
		int texWidth, texHeight;
		int texture;

		// Vertex Out, vertex used for rasterization, this is changing every frame
		VertexOut* dev_verticesOut;
	};

}

static std::map<std::string, std::vector<PrimitiveDevBufPointers>> mesh2PrimitivesMap;


static int width = 0;
static int height = 0;

static int totalNumPrimitives = 0;
static Primitive *dev_primitives = NULL;
static Fragment *dev_fragmentBuffer = NULL;
static glm::vec3 *dev_framebuffer = NULL;

static int * dev_depth = NULL;	// you might need this buffer when doing depth test
#define blockSize 256

//TILEs::::::::::::::::::::::
 
#define tileSizeR2 256
static int tileWidth;
static int tileHeight;
static int numTilesV;
static int numTilesH;

struct Tile{
	float maxx;
	float maxy;
	float minx;
	float miny;
	int numPrims = 0;
};
//TILEs______________________
static Tile * dev_tiles;
