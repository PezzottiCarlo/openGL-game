#pragma once

#include "lib.h"
#include "node.h"
#include "material.h"
#include "vertex.h"


#include <string>
#include <map>


class LIB_API OvoReader {
public:
	OvoReader();
	~OvoReader();

public:
	Node* readFile(const char* path);

private:
	Node* recursiveLoad(FILE* dat);

private:
	std::map<std::string, Material*> materials;
	std::vector<Vertex*> tempVertices;
};

