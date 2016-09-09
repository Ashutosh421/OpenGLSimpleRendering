#include <iostream>
#include "display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *args[]) {
	std::cout << "This is the Main Class" <<std::endl;	

	Display display(800, 600, "New Display Window");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0), glm::vec2(0.0 , 0.0)),
		                  Vertex(glm::vec3(0,0.5,0), glm::vec2(0.5 , 1.0)),
		                  Vertex(glm::vec3(0.5,-0.5,0), glm::vec2(1.0 , 0.0)) ,
	                    };
	unsigned int indices[] = { 0 , 1 , 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices , sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("monkey3");	
	Shader shader("basicShader");
	Texture texture("brick_wall.jpg");
	Transform transform;
	Camera camera(glm::vec3(0,0,-5), 70.07f, float(WIDTH)/ (float)HEIGHT, 0.01, 1000.0f);

	float counter = 0.0;
	float sinCounter = 0.0;
	float cosCounter = 0.0;

	while (!display.IsClosed()) {
		display.Clear(0.0f, 0.2f, 0.1f, 1);

		sinCounter = sinf(counter);
		cosCounter = cosf(counter);

		transform.GetPos().x = sinCounter;
		transform.GetPos().z = cosCounter;
		//transform.GetRotation().z = counter * 1;
		//transform.GetRotation().x = counter * 1;
		transform.GetRotation().y = counter * 1;
		//transform.SetScale(glm::vec3(cosCounter,cosCounter,cosCounter));

		texture.Bind(0);
		shader.Bind();
		shader.Update(transform, camera);
		mesh.Draw();
		mesh2.Draw();
		display.Update();
		counter += 0.001f;
	}

	return 0;
}