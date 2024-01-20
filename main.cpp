#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

const GLchar* vertexShaderSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec3 position;
    void main()
    {
        gl_Position = vec4(position, 1.0);
    }
)glsl";

const GLchar* fragmentShaderSource = R"glsl(
    #version 330 core
    out vec4 color;
    void main()
    {
        color = vec4(1.0, 0.5, 0.2, 1.0);
    }
)glsl";

int main() {
    // Initialisation de GLFW
    if (!glfwInit()) {
        cerr << "Échec de l'initialisation de GLFW" << endl;
        return -1;
    }

    // Configuration de GLFW pour utiliser le profil OpenGL Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Création d'une fenêtre GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Bibibop engine", nullptr, nullptr);
    if (!window) {
        cerr << "Échec de la création de la fenêtre GLFW" << endl;
        glfwTerminate();
        return -1;
    }

    // Définition de la fenêtre comme le contexte OpenGL courant
    glfwMakeContextCurrent(window);

    // Initialisation de GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cerr << "Échec de l'initialisation de GLEW" << endl;
        glfwTerminate();
        return -1;
    }

    // Définition de la fonction de rappel de redimensionnement de la fenêtre
    glViewport(0, 0, 800, 600);

    // Compilation et liaison des shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Définition des vertices du triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // Vertex inférieur gauche
         0.5f, -0.5f, 0.0f, // Vertex inférieur droit
         0.0f,  0.5f, 0.0f  // Vertex supérieur central
    };

    // Création et configuration d'un tampon de vertex (VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Liaison du VAO
    glBindVertexArray(VAO);

    // Liaison du VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configuration de l'attribut de position du vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Liaison du VAO 0 à 0
    glBindVertexArray(0);

    // Boucle principale
    while (!glfwWindowShouldClose(window)) {
        // Vérification des événements et gestion des entrées
        glfwPollEvents();

        // Effacement du tampon de couleur à chaque itération de la boucle
        glClear(GL_COLOR_BUFFER_BIT);

        // Utilisation du shader program
        glUseProgram(shaderProgram);

        // Liaison du VAO
        glBindVertexArray(VAO);

        // Dessin du triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Déliaison du VAO
        glBindVertexArray(0);

        // Échange des tampons de la fenêtre
        glfwSwapBuffers(window);
    }

    // Libération des ressources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // Fermeture de la fenêtre GLFW et libération des ressources associées
    glfwTerminate();

    return 0;
}