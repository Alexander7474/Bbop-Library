#ifndef BBOP_FUNCTION_H
#define BBOP_FUNCTION_H

#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "collisionBoxClass.h"
#include "sceneClass.h"
#include "shapeClass.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
* @brief Fonction d'initialisation de Bbop Library
*
* @param[in] windowX Taille x de la fenêtre
* @param[in] windowY Taille y de la fenêtre
* @param[in] windowName Nom de la fenêtre
* @param[in,out] window Fenêtre glfw à utiliser
*
* @see Dans bbopFunc.cpp 
*
* @note window dois-être un pointeur
*/
int bbopInit(int windowX, int windowY, const char* windowName, GLFWwindow*& window);

/**
* @brief Fonction de nettoyage de la fenêtre
*
* @param[in] window Fenêtre à nettoyer
* @param[in] rgb Couleur de fond de la fenêtre
* @param[in] alpha Transaprence du nettoyage
*
* @see Dans bbopFunc.cpp 
*
* @note window dois-être un pointeur
*/
void bbopCleanWindow(GLFWwindow*& window,Vector3i rgb, float alpha);

/**
* @brief Fonction de verification d'erreur d'opengl
*
* @see Dans bbopFunc.cpp 
*/
void bbopErrorCheck();

/**
* @brief Fonction d'initialisation de Bbop Library
*
* @param[in] wWinSize Nouvelle taille de la fenêtre 
*
* @see Dans bbopFunc.cpp 
*/
void bbopChangeWindowSize(Vector2i nWinSize);

/**
* @brief Debug de collision en affichant une box
* 
* @param[in] box Boîte de collision à afficher
* @param[in] scene Scene a utiliser pour afficher la box
*
* @see Dans bbopFunc.cpp
*/
void bbopDebugCollisionBox(CollisionBox* box, Scene& scene);

#endif // !BBOP_FUNCTION_H
