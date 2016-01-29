#ifndef GAME_HPP
#define GAME_HPP

#include <list>
#include <random>
#include "BasicHeader.hpp"
#include "GPUManager.hpp"
#include "Renderer.hpp"
#include "PhysicsManager.hpp"
#include "Scene.hpp"
#include "PhongShader.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "CameraSwitcher.hpp"
#include "PointLight.hpp"
#include "Border.hpp"
#include "TargetBorder.hpp"
#include "TopBorder.hpp"
#include "Bubble.hpp"
#include "ShinyBubble.hpp"
#include "IObserver.hpp"

class Game : public IObserver {
public:	
	virtual void Loop() {
		static Time_t logicalTime = glfwGetTime();
		static Time_t lastPrint = logicalTime;
		static int frames = 0;

		Time_t currentTime = glfwGetTime();
		if(currentTime - lastPrint >= 1.0) {
			std::cerr << 1000.0/(Time_t)frames << " ms/frame\n";
			lastPrint = currentTime;
			frames = 0;
		}
		frames++;
	
		for( ; logicalTime < currentTime ; logicalTime += logicalStep)
		 	physics.Frame(logicalStep);
		renderer.Draw(scene);
	}

	virtual void Setup() {
		//setup opengl
		GPU.SetClearColour(Colour_t(0.85,0.85,0.0));
		GPU.SetDepthTest(true);
		GPU.SetBackFaceCulling(true);

		//player
		std::vector<Vertex_t> vertices;
		std::vector<TrIndex_t> triangles;
		
		player.Drawable.GenVertices(vertices,triangles);
		std::tie(	player.Drawable.VertexBufferID,
					player.Drawable.IndexBufferID,
					player.Drawable.IndexBufferOffset) = GPU.StoreVertices(vertices,triangles);
		player.Drawable.Shader = &shader;
		physics.RegisterBody(&player);
		scene.RegisterActor(&player.Drawable);
		scene.RegisterActor(&player.Light);

		//additional camera
		outside_camera.Position = Position_t(150.0,100.0,-180.0);
		outside_camera.Direction = glm::normalize(Position_t(-5.0,-2.0,2.3));
		outside_camera.UpVector = Position_t(0.0,1.0,0.0);

		//camera switcher
		switcher.RegisterCamera(&player.FPCamera);
		switcher.RegisterCamera(&outside_camera);
		physics.RegisterBody(&switcher);
		scene.Camera = &switcher.Camera;

		//lights
		sunshine.Position = Position_t(500.0,1000.0,3000.0);
		sunshine.Intensity = Colour_t(2000.0,2000.0,2000.0);
		//scene.RegisterActor(&sunshine);

		lamp.Position = Position_t(10.0,box_y-10.0,-0.5*box_z);
		lamp.Intensity = Colour_t(80.0,80.0,80.0);
		scene.RegisterActor(&lamp);

		//left border
		vertices.clear();
		triangles.clear();

		border_left.Drawable.GenVertices(vertices,triangles);
		std::tie(	border_left.Drawable.VertexBufferID,
					border_left.Drawable.IndexBufferID,
					border_left.Drawable.IndexBufferOffset) = GPU.StoreVertices(vertices,triangles);
		border_left.Drawable.Shader = &underwater_shader;
		physics.RegisterBody(&border_left);
		scene.RegisterActor(&border_left.Drawable);

		//right border
		border_right.Drawable.VertexBufferID = border_left.Drawable.VertexBufferID;
		border_right.Drawable.IndexBufferID = border_left.Drawable.IndexBufferID;
		border_right.Drawable.IndexBufferOffset = border_left.Drawable.IndexBufferOffset;
		border_right.Drawable.Shader = &underwater_shader;
		physics.RegisterBody(&border_right);
		scene.RegisterActor(&border_right.Drawable);

		//ceiling
		border_top.Drawable.VertexBufferID = border_left.Drawable.VertexBufferID;
		border_top.Drawable.IndexBufferID = border_left.Drawable.IndexBufferID;
		border_top.Drawable.IndexBufferOffset = border_left.Drawable.IndexBufferOffset;
		border_top.Drawable.Shader = &underwater_shader;
		physics.RegisterBody(&border_top);
		scene.RegisterActor(&border_top.Drawable);

		//floor
		border_down.Drawable.VertexBufferID = border_left.Drawable.VertexBufferID;
		border_down.Drawable.IndexBufferID = border_left.Drawable.IndexBufferID;
		border_down.Drawable.IndexBufferOffset = border_left.Drawable.IndexBufferOffset;
		border_down.Drawable.Shader = &underwater_shader;
		physics.RegisterBody(&border_down);
		scene.RegisterActor(&border_down.Drawable);

		//back border
		border_back.Drawable.VertexBufferID = border_left.Drawable.VertexBufferID;
		border_back.Drawable.IndexBufferID = border_left.Drawable.IndexBufferID;
		border_back.Drawable.IndexBufferOffset = border_left.Drawable.IndexBufferOffset;
		border_back.Drawable.Shader = &underwater_shader;
		physics.RegisterBody(&border_back);
		scene.RegisterActor(&border_back.Drawable);
		border_back.RegisterObserver(this);

		//front border
		border_front.Drawable.VertexBufferID = border_left.Drawable.VertexBufferID;
		border_front.Drawable.IndexBufferID = border_left.Drawable.IndexBufferID;
		border_front.Drawable.IndexBufferOffset = border_left.Drawable.IndexBufferOffset;
		border_front.Drawable.Shader = &underwater_shader;
		physics.RegisterBody(&border_front);
		scene.RegisterActor(&border_front.Drawable);

		//prototype bubble
		vertices.clear();
		triangles.clear();

		bubble.Drawable.GenVertices(vertices,triangles);
		std::tie(	bubble.Drawable.VertexBufferID,
					bubble.Drawable.IndexBufferID,
					bubble.Drawable.IndexBufferOffset) = GPU.StoreVertices(vertices,triangles);
		bubble.Drawable.Shader = &underwater_shader;

		//random bubbles
		std::mt19937 eng;	//generator
  		std::uniform_real_distribution<float> dist_x(0.0,box_x); //rozklad
  		std::uniform_real_distribution<float> dist_y(0.0,box_y);
  		std::uniform_real_distribution<float> dist_z(-box_z,-20.0);
  		std::uniform_real_distribution<float> dist_vel(3.0,6.0);
  		std::uniform_real_distribution<float> dist_r(2.0,5.0);

		for(unsigned short int i=0 ; i < bubbles_number ; i++) {
			bubbles.emplace_back(
				Position_t(dist_x(eng),dist_y(eng),dist_z(eng)),
				dist_r(eng),
				Position_t(0.0,dist_vel(eng),0.0),
				Colour_t(0.8,0.8,0.8)
			);
			
			bubbles.back().Drawable.VertexBufferID = bubble.Drawable.VertexBufferID;
			bubbles.back().Drawable.IndexBufferID = bubble.Drawable.IndexBufferID;
			bubbles.back().Drawable.IndexBufferOffset = bubble.Drawable.IndexBufferOffset;
			bubbles.back().Drawable.Shader = &underwater_shader;
			physics.RegisterBody(&bubbles.back());
			scene.RegisterActor(&bubbles.back().Drawable);
			bubbles.back().RegisterObserver(this);
		}

		Colour_t colours[] = {
			Colour_t(1.0,0.00,0.00),
			Colour_t(1.0,0.00,1.0),
			Colour_t(1.0,1.0,0.00),
			Colour_t(0.00,1.0,1.0),
			Colour_t(1.0,1.0,1.0),
			Colour_t(1.0,0.00,0.00),
			Colour_t(1.0,0.00,1.0),
			Colour_t(1.0,1.0,0.00),
			Colour_t(0.00,1.0,1.0),
			Colour_t(1.0,1.0,1.0),
			Colour_t(1.0,0.00,0.00),
			Colour_t(1.0,0.00,1.0),
			Colour_t(1.0,1.0,0.00),
			Colour_t(0.00,1.0,1.0),
			Colour_t(1.0,1.0,1.0),
		};

		//shiny bubbles
		for(unsigned short int i=0 ; i < shiny_bubbles_number ; i++) {
			shiny_bubbles.emplace_back(
				Position_t(dist_x(eng),dist_y(eng),dist_z(eng)),
				1.0,
				Position_t(0.0,5.0,0.0),
				Colour_t(1,0.7,0.7)
			);
			
			vertices.clear();
			triangles.clear();
			
			shiny_bubbles.back().Drawable.GenVertices(vertices,triangles);
			std::tie(	shiny_bubbles.back().Drawable.VertexBufferID,
						shiny_bubbles.back().Drawable.IndexBufferID,
						shiny_bubbles.back().Drawable.IndexBufferOffset) = GPU.StoreVertices(vertices,triangles);
			shiny_bubbles.back().Drawable.Shader = &underwater_shader;
			physics.RegisterBody(&shiny_bubbles.back());
			scene.RegisterActor(&shiny_bubbles.back().Drawable);
			scene.RegisterActor(&shiny_bubbles.back().Light);
			shiny_bubbles.back().RegisterObserver(this);
		}
	}

	virtual void Notify(Notification n) {
		switch(n.type) {
			case Notification::BUBBLE_HIT:
				std::cerr << "You were killed!\n";
				glfwSetWindowShouldClose(window,true);
				break;
			case Notification::TARGET_HIT:
				std::cerr << "You won!\n";
				glfwSetWindowShouldClose(window,true);
				break;
			default:
				break;
 		}
	}
protected:
	const unsigned short int bubbles_number = 100;
	const unsigned short int shiny_bubbles_number = 3;
	const Time_t logicalStep = 0.02;

	//box
	const Coord_t box_x = 50.0;
	const Coord_t box_y = 80.0;
	const Coord_t box_z = 200.0;
	const Colour_t borders_colour = Colour_t(0.5,0.5,0.7);

	GPUManager GPU;
	Renderer renderer = Renderer(&GPU);
	PhysicsManager physics;
	Scene scene;
	PhongShader shader = PhongShader("VertexShader.glsl","PixelShader.glsl");
	PhongShader underwater_shader = PhongShader("VertexShader.glsl","WaterPixelShader.glsl");
	Player player = Player(Position_t(0.5*box_x,0.5*box_y,-10.0));
	Camera outside_camera;
	CameraSwitcher switcher;
	PointLight sunshine,lamp;

	Border border_left = Border(
		glm::rotate(
					Transformation_t(1.0),
					(float)(M_PI*0.5),
					Position_t(0,1,0)),
		box_z,box_y,borders_colour);
	
	Border border_right = Border(
		glm::rotate(
					glm::translate(
									Transformation_t(1.0),
									Position_t(box_x,0,-box_z)),
					(float)(-M_PI*0.5),
					Position_t(0,1,0)),
		box_z,box_y,borders_colour);
	
	TopBorder border_top = TopBorder(
		glm::rotate(
					glm::rotate(
								glm::translate(
												Transformation_t(1.0),
												Position_t(0,box_y,0)),
								(float)(-M_PI*0.5),
								Position_t(0,0,1)),
					(float)(M_PI*0.5),
					Position_t(0,1,0)),
		box_z,box_x,borders_colour);
	
	Border border_down = Border(
		glm::rotate(
					glm::rotate(
								glm::translate(
												Transformation_t(1.0),
												Position_t(box_x,0,0)),
								(float)(M_PI*0.5),
								Position_t(0,0,1)),
					(float)(M_PI*0.5),
					Position_t(0,1,0)),
		box_z,box_x,borders_colour);
	
	TargetBorder border_back = TargetBorder(
		glm::translate(
						Transformation_t(1.0),
						Position_t(0,0,-box_z)),
		box_x,box_y,borders_colour);
	
	Border border_front = Border(
		glm::rotate(
					glm::translate(
									Transformation_t(1.0),
									Position_t(box_x,0,0)),
					(float)M_PI,
					Position_t(0,1,0)),
		box_x,box_y,borders_colour);
		
	Bubble bubble = Bubble(Position_t(0.0,0.0,0.0),4,Position_t(0.0,0.0,0.0),Colour_t(0.8,0.8,0.8));
	std::list<Bubble> bubbles;
	std::list<ShinyBubble> shiny_bubbles;
};

#endif