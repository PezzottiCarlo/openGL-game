#include <string>
#include <GL/freeglut.h>
#include <iostream>
#include <memory>

#include "ovoReader.h"
#include "mesh.h"
#include "light.h"
#include "ovLight.h"
#include "ovObject.h"
#include <glm/gtc/packing.hpp>
#include "shadow.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#pragma warning(disable : 4996)

std::string getSeparator() {
#ifdef _WIN32
	return "\\";
#else
	return "/";
#endif
}

LIB_API OvoReader::OvoReader() {}

OvoReader::~OvoReader() {
	materials.clear();
	tempVertices.clear();
}

std::string _path;
Node* OvoReader::readFile(const char* path) {

	// Open file:
	FILE* dat = fopen(path, "rb");
	if (dat == nullptr)
	{
		std::cout << "ERROR: unable to open file '" << path << "'" << std::endl;
		return nullptr;
	}

	_path = path;

	Node* root = recursiveLoad(dat);
	fclose(dat);

	return root;
}

// Recursive loading function
Node* OvoReader::recursiveLoad(FILE* dat)
{
	// Parse the chunk starting at buffer + position:
	unsigned int chunkId, chunkSize, position = 0;

	fread(&chunkId, sizeof(unsigned int), 1, dat);
	fread(&chunkSize, sizeof(unsigned int), 1, dat);

	// Load whole chunk into memory:
	char* data = new char[chunkSize];
	if (fread(data, sizeof(char), chunkSize, dat) != chunkSize)
	{
		std::cout << "ERROR: unable to read from file" << std::endl;
		fclose(dat);
		delete[] data;
	}

	//First Object
	if ((OvObject::Type)chunkId == OvObject::Type::O_OBJECT) {
		unsigned int versionId;
		memcpy(&versionId, data + position, sizeof(unsigned int));
		position += sizeof(unsigned int);

		return recursiveLoad(dat);
	}

	//Material
	if ((OvObject::Type)chunkId == OvObject::Type::O_MATERIAL) {
		// Material name:
		char materialName[FILENAME_MAX];
		strcpy(materialName, data + position);
		position += (unsigned int)strlen(materialName) + 1;
		std::string materialName_str(materialName);

		// Material term colors, starting with emissive:
		glm::vec3 emission, albedo;
		memcpy(&emission, data + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Albedo:
		memcpy(&albedo, data + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Roughness factor:
		float roughness;
		memcpy(&roughness, data + position, sizeof(float));
		position += sizeof(float);

		//Skipped values:
		// Metalness factor:
		position += sizeof(float);
		// Transparency factor:
		position += sizeof(float);

		// Albedo texture filename, or [none] if not used:
		char textureName[FILENAME_MAX];
		strcpy(textureName, data + position);
		position += (unsigned int)strlen(textureName) + 1;
		std::string textureName_str = std::string(textureName);

		//Save material on data structure
		Material* material = new Material(materialName_str, glm::vec4(emission, 1.0f), glm::vec4(albedo * 0.2f, 1.0f), glm::vec4(albedo * 0.6f, 1.0f), glm::vec4(albedo * 0.4f, 1.0f), (1 - sqrt(roughness)) * 128);
		materials.insert(std::pair<std::string, Material*>(material->getName(), material));

		Texture* texture = new Texture(textureName_str);

		material->setTexture(texture);

		if (textureName_str != "[none]") {
			texture->setTextureId(_path.substr(0, _path.find_last_of(getSeparator())) + getSeparator() + textureName_str);
		}

		return recursiveLoad(dat);
	}

	// Node name:
	char nodeName[FILENAME_MAX];
	strcpy(nodeName, data + position);
	position += (unsigned int)strlen(nodeName) + 1;
	std::string nodeName_str(nodeName);

	// Node matrix:
	glm::mat4 matrix;
	memcpy(&matrix, data + position, sizeof(glm::mat4));
	position += sizeof(glm::mat4);

	// Nr. of children nodes:
	unsigned int nrOfChildren = 0;
	memcpy(&nrOfChildren, data + position, sizeof(unsigned int));
	position += sizeof(unsigned int);

	// Parse chunk information according to its type:
	switch ((OvObject::Type)chunkId)
	{
	case OvObject::Type::O_NODE:
	{
		Node* thisNode = new Node(nodeName_str);
		thisNode->setTransform(matrix);

		// Go recursive when child nodes are avaialble:
		if (nrOfChildren)
			while (thisNode->getNumberOfChildren() < nrOfChildren)
			{
				Node* childNode = recursiveLoad(dat);
				thisNode->addChild(childNode);
			}

		// Done:
		return thisNode;
	}

	case OvObject::Type::O_MESH:
	{
		// Optional target node, or [none] if not used:
		char targetName[FILENAME_MAX];
		strcpy(targetName, data + position);

		position += (unsigned int)strlen(targetName) + 1;
		std::cout << "Target name: " << nodeName_str << std::endl;

		// Mesh subtype (see OvMesh SUBTYPE enum):
		position += sizeof(unsigned char);

		// Material name, or [none] if not used:
		char materialName[FILENAME_MAX];
		strcpy(materialName, data + position);
		std::cout << "\tMaterial name: " << materialName << std::endl;

		position += (unsigned int)strlen(materialName) + 1;
		std::string materialName_str(materialName);

		Mesh* thisMesh;
		if (materialName_str != "[none]") {
			Material material = *(materials.find(materialName_str)->second);
			thisMesh = new Mesh(nodeName_str, material);
			thisMesh->setTransform(matrix);
		}
		else {
			thisMesh = new Mesh(nodeName_str, Material());
			thisMesh->setTransform(matrix);
		}

		// Mesh bounding sphere radius:
		float radius;
		memcpy(&radius, data + position, sizeof(float));
		position += sizeof(float);
		// Mesh bounding box minimum corner:
		glm::vec3 bBoxMin;
		memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);
		// Mesh bounding box maximum corner:
		position += sizeof(glm::vec3);
		// Optional physics properties:
		unsigned char hasPhysics;
		memcpy(&hasPhysics, data + position, sizeof(unsigned char));
		position += sizeof(unsigned char);
		if (hasPhysics)
		{
			/**
			 * Mesh physics properties.
			 */
			struct PhysProps
			{
				// Pay attention to 16 byte alignement (use padding):
				unsigned char type;
				unsigned char contCollisionDetection;
				unsigned char collideWithRBodies;
				unsigned char hullType;

				// Vector data:
				glm::vec3 massCenter;

				// Mesh properties:
				float mass;
				float staticFriction;
				float dynamicFriction;
				float bounciness;
				float linearDamping;
				float angularDamping;
				unsigned int nrOfHulls;
				unsigned int _pad;

				// Pointers:
				void* physObj;
				void* hull;
			};

			PhysProps mp;
			memcpy(&mp, data + position, sizeof(PhysProps));
			position += sizeof(PhysProps);
			// Custom hull(s) used?
			if (mp.nrOfHulls)
			{
				for (unsigned int c = 0; c < mp.nrOfHulls; c++)
				{
					// Hull number of vertices:
					unsigned int nrOfVertices;
					memcpy(&nrOfVertices, data + position, sizeof(unsigned int));
					position += sizeof(unsigned int);
					// Hull number of faces:
					unsigned int nrOfFaces;
					memcpy(&nrOfFaces, data + position, sizeof(unsigned int));
					position += sizeof(unsigned int);
					// Hull centroid:
					position += sizeof(glm::vec3);
					// Iterate through hull vertices:
					for (unsigned int c = 0; c < nrOfVertices; c++)
					{
						position += sizeof(glm::vec3);
					}
					// Iterate through hull faces:
					for (unsigned int c = 0; c < nrOfFaces; c++)
					{
						position += sizeof(unsigned int) * 3;
					}
				}
			}
		}


		// Nr. of LODs:
		unsigned int LODs;
		memcpy(&LODs, data + position, sizeof(unsigned int));
		position += sizeof(unsigned int);

		std::cout << "\tLODs: " << LODs << std::endl;

		for (unsigned int l = 0; l < LODs; l++)
		{

			// Nr. of vertices:
			unsigned int vertices, faces;

			memcpy(&vertices, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			std::cout << "\tNr. of vertices: " << vertices << std::endl;


			// ...and faces:
			memcpy(&faces, data + position, sizeof(unsigned int));
			position += sizeof(unsigned int);

			std::cout << "\tNr. of faces: " << faces << std::endl;

			// Interleaved and compressed vertex/normal/UV/tangent data:
			for (unsigned int c = 0; c < vertices; c++)
			{
				// Vertex coords:
				glm::vec3 vertex;
				memcpy(&vertex, data + position, sizeof(glm::vec3));
				position += sizeof(glm::vec3);

				// Vertex normal:
				unsigned int normalData;
				memcpy(&normalData, data + position, sizeof(unsigned int));
				position += sizeof(unsigned int);

				// Texture coordinates:
				unsigned int textureData;
				memcpy(&textureData, data + position, sizeof(unsigned int));
				position += sizeof(unsigned int);

				// Tangent vector:
				unsigned int tangentData;
				memcpy(&tangentData, data + position, sizeof(unsigned int));
				position += sizeof(unsigned int);



				glm::vec4 normal = glm::unpackSnorm3x10_1x2(normalData);
				Vertex* newVertex = new Vertex(vertex, glm::vec3(normal.x, normal.y, normal.z));
				glm::vec2 uv = glm::unpackHalf2x16(textureData);
				newVertex->setTextureCoordinates(glm::vec2(uv));
				tempVertices.push_back(newVertex);
			}

			// Faces:
			for (unsigned int c = 0; c < faces; c++)
			{
				// Face indexes:
				unsigned int face[3];
				memcpy(face, data + position, sizeof(unsigned int) * 3);
				position += sizeof(unsigned int) * 3;


				for (int i = 0; i < 3; i++)
				{
					thisMesh->addVertex(tempVertices.at(face[i]), l);
				}
			}

			//if the first 4 char are Tree cast a shadow or "streetlamp_body"
			if (thisMesh->getName().substr(0, 4) == "Tree") {
				std::cout << "Shadow of tree" << std::endl;
				Shadow* shadow = new Shadow(thisMesh);
				thisMesh->addChild(shadow);
			}

			tempVertices.clear();
		}

		// Go recursive when child nodes are avaialble:
		if (nrOfChildren) {
			while (thisMesh->getNumberOfChildren() < nrOfChildren)
			{
				Node* childNode = recursiveLoad(dat);
				thisMesh->addChild(childNode);
			}
		}

		// Done:
		return thisMesh;
	}

	case OvObject::Type::O_LIGHT:
	{
		// Optional target node name, or [none] if not used:
		char targetName[FILENAME_MAX];
		strcpy(targetName, data + position);
		position += (unsigned int)strlen(targetName) + 1;

		// Light subtype (see OvLight SUBTYPE enum):
		unsigned char subtype;
		memcpy(&subtype, data + position, sizeof(unsigned char));
		char subtypeName[FILENAME_MAX];
		switch ((OvLight::Subtype)subtype)
		{
		case OvLight::Subtype::DIRECTIONAL: strcpy(subtypeName, "directional"); break;
		case OvLight::Subtype::OMNI: strcpy(subtypeName, "omni"); break;
		case OvLight::Subtype::SPOT: strcpy(subtypeName, "spot"); break;
		default: strcpy(subtypeName, "UNDEFINED");
		}
		position += sizeof(unsigned char);

		// Light color:
		glm::vec3 color;
		memcpy(&color, data + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Influence radius:
		float radius;
		memcpy(&radius, data + position, sizeof(float));
		position += sizeof(float);

		// Direction:
		glm::vec3 direction;
		memcpy(&direction, data + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Cutoff:
		float cutoff;
		memcpy(&cutoff, data + position, sizeof(float));
		position += sizeof(float);

		// Exponent:
		float spotExponent;
		memcpy(&spotExponent, data + position, sizeof(float));
		position += sizeof(float);

		// Cast shadow flag:
		unsigned char castShadows;
		memcpy(&castShadows, data + position, sizeof(unsigned char));
		position += sizeof(unsigned char);

		// Volumetric lighting flag:
		unsigned char isVolumetric;
		memcpy(&isVolumetric, data + position, sizeof(unsigned char));
		position += sizeof(unsigned char);

		Light* thisLight = nullptr;
		int nextLightPointer = Light::getNextLightNumber();
		switch ((OvLight::Subtype)subtype)
		{
		case OvLight::Subtype::DIRECTIONAL:
		{
			thisLight = new DirectionalLight(nodeName_str, nextLightPointer, glm::vec4(glm::vec3(color.x), 1.0f), glm::vec4(glm::vec3(color.y), 1.0f), glm::vec4(glm::vec3(color.z), 1.0f));
		}break;
		case OvLight::Subtype::OMNI:
		{
			thisLight = new PointLight(nodeName_str, nextLightPointer, glm::vec4(glm::vec3(color.x), 1.0f), glm::vec4(glm::vec3(color.y), 1.0f), glm::vec4(glm::vec3(color.z), 1.0f), cutoff);
		}break;
		case OvLight::Subtype::SPOT:
		{
			thisLight = new SpotLight(nodeName_str, nextLightPointer, glm::vec4(glm::vec3(color.x), 1.0f), glm::vec4(glm::vec3(color.y), 1.0f), glm::vec4(glm::vec3(color.z), 1.0f), cutoff, direction);
		}break;
		default:
			thisLight = new Light(nodeName_str, nextLightPointer, glm::vec4(glm::vec3(color.x), 1.0f), glm::vec4(glm::vec3(color.y), 1.0f), glm::vec4(glm::vec3(color.z), 1.0f));
		}


		thisLight->setTransform(matrix);

		// Go recursive when child nodes are avaialble:
		if (nrOfChildren)
			while (thisLight->getNumberOfChildren() < nrOfChildren)
			{
				Node* childNode = recursiveLoad(dat);
				thisLight->addChild(childNode);
			}
		// Done:
		return thisLight;
	}
	}
	delete[] data;
}
