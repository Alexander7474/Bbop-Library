#include "../../../include/BBOP/Performance/benchmark.h"
#include <GLFW/glfw3.h>
#include <random>

vector<Sprite> spriteList;
double lastTime;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> distribx(0, BIBIBOP_WINDOW_SIZE.x);
uniform_int_distribution<int> distriby(0, BIBIBOP_WINDOW_SIZE.y);
uniform_int_distribution<int> distribs(10,100);

bool bbopBenchMark(Scene& sceneToUse)
{
  spriteList.push_back(Sprite("nope"));
  sceneToUse.Use();
  lastTime = glfwGetTime();
  for(unsigned int i = 0; i< spriteList.size(); i ++){
    spriteList[i].setPosition(Vector2f(distribx(gen),distriby(gen)));
    spriteList[i].setSize(Vector2f(distribs(gen),distribs(gen)));
    sceneToUse.Draw(spriteList[i]);
  }
  cout << "BENCHMARK RUNNING" << endl << "Number of sprite: " << spriteList.size() << " delta time: " << glfwGetTime()-lastTime << endl;
  if (glfwGetTime() - lastTime > 1.0){
    cout << "BENCHMARK FINISHED" << endl << "Total of sprite: " << spriteList.size() << endl;
    return true;
  }
  return false;
}
