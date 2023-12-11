#include "Node.h"
#include "Material.h"
#include "Vertex.h"
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

