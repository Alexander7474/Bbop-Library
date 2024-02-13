#include "../../../include/BBOP/Performance/benchmark.h"
#include <GLFW/glfw3.h>

vector<Sprite> spriteList;
double lastTime;
bool bbopBenchMark(Scene& sceneToUse)
{
  spriteList.push_back(Sprite("nope"));
  sceneToUse.Use();
  lastTime = glfwGetTime();
  for(unsigned int i = 0; i< spriteList.size(); i ++)
    sceneToUse.Draw(spriteList[i]);
  cout << "BENCHMARK RUNNING" << endl << "Number of sprite: " << spriteList.size() << " delta time: " << glfwGetTime()-lastTime << endl;
  if (glfwGetTime() - lastTime > 1.0){
    cout << "BENCHMARK FINISHED" << endl << "Total of sprite: " << spriteList.size() << endl;
    return true;
  }
  return false;
}
