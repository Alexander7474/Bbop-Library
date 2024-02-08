#include "../include/bbopfunc.h"
#include <GLFW/glfw3.h>

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
  
}
// Lecture du fichier text et sortie en string
string getFileData(const char* filename)
{
	ifstream in(filename, ios::binary);
	if (in)
	{
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}
