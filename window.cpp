#include "window.h"

/**
 * @brief Ventana del juego.
 * * @param width Ancho de la ventana. Tipo GLuint
 * * @param height Alto de la ventana. Tipo GLuint
 */
Window :: Window(const GLuint width, const GLuint height) : window(nullptr), projection(glm::mat4(1.0f)) {
	if (!glfwInit()) return;

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "Overlay", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	#ifdef _WIN32
		HWND hwnd = glfwGetWin32Window(window);
		LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
		SetWindowLong(hwnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED | WS_EX_TRANSPARENT);
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	#endif

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	projection = glm::ortho(0.0f, float(width), float(height), 0.0f, -1.0f, 1.0f);
}