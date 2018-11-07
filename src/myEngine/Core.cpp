#include <MYENGINE/Core.h>
#include <myEngine/Entity.h>

#include <GL/glew.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

namespace myengine
{

	std::shared_ptr<Core> Core::initialise()
	{
		//creates useable pointer to self, sets a bool to false, sets weakptr to self
		std::shared_ptr<Core> toSelf = std::make_shared<Core>();
		toSelf->running = false;
		toSelf->self = toSelf;

		//initialise sdl, throws exception if issue
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		//create SDL window ( "| SDL_WINDOW_OPENGL" makes it suitable for an OpenGL rendering context)
		toSelf->window = SDL_CreateWindow("Game Engine",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		//creates an OPENGL rendering context within the sdl window we made earlier
		if (!SDL_GL_CreateContext(toSelf->window))
		{
			throw std::exception();
		}

		//initialises glew, throws exceptions if issue
		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		return toSelf;
	}

	Core::~Core()
	{
	
	}

	void Core::run()
	{
		//set running bool to true
		running = true;

		//loop while running bool is true
		while (running)
		{
			//handles quitting
			SDL_Event event = { 0 };
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) //if the red x is hit
				{
					running = false;
				}
			}

			//iterate through and call update on all entities






			//
			//
			//a bunch of points to draw triangle
			const GLfloat positions[] = {
				0.0f, 0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				0.5f, -0.5f, 0.0f
			};

			GLuint positionsVboId = 0;
			// Create a new VBO on the GPU and bind it
			glGenBuffers(1, &positionsVboId);

			if (!positionsVboId)
			{
				throw std::exception();
			}

			glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

			// Upload a copy of the data from memory into the new VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

			// Reset the state
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint vaoId = 0;

			// Create a new VAO on the GPU and bind it
			glGenVertexArrays(1, &vaoId);

			if (!vaoId)
			{
				throw std::exception();
			}

			glBindVertexArray(vaoId);

			// Bind the position VBO, assign it to position 0 on the bound VAO
			// and flag it to be used
			glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
				3 * sizeof(GLfloat), (void *)0);

			glEnableVertexAttribArray(0);

			// Reset the state
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			const GLchar *vertexShaderSrc =
				"attribute vec3 in_Position;             " \
				"                                        " \
				"void main()                             " \
				"{                                       " \
				"  gl_Position = vec4(in_Position, 1.0); " \
				"}                                       ";

			// Create a new vertex shader, attach source code, compile it and
			// check for errors.
			GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
			glCompileShader(vertexShaderId);
			GLint success = 0;
			glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				throw std::exception();
			}

			const GLchar *fragmentShaderSrc =
				"void main()                        " \
				"{                                  " \
				"  gl_FragColor = vec4(0, 0, 1, 1); " \
				"}                                  ";

			// Create a new fragment shader, attach source code, compile it and
			// check for errors.
			GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShaderId, 1, &fragmentShaderSrc, NULL);
			glCompileShader(fragmentShaderId);
			glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				throw std::exception();
			}

			//
			// Create new shader program and attach our shader objects
			GLuint programId = glCreateProgram();
			glAttachShader(programId, vertexShaderId);
			glAttachShader(programId, fragmentShaderId);

			// Ensure the VAO "position" attribute stream gets set as the first position
			// during the link.
			glBindAttribLocation(programId, 0, "in_Position");

			// Perform the link and check for failure
			glLinkProgram(programId);
			glGetProgramiv(programId, GL_LINK_STATUS, &success);

			if (!success)
			{
				throw std::exception();
			}

			// Detach and destroy the shader objects. These are no longer needed
			// because we now have a complete shader program.
			glDetachShader(programId, vertexShaderId);
			glDeleteShader(vertexShaderId);
			glDetachShader(programId, fragmentShaderId);
			glDeleteShader(fragmentShaderId);
			//
			//
			



			//clear screen
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//call draw on all entities




			//
			// Instruct OpenGL to use our shader program and our VAO
			glUseProgram(programId);
			glBindVertexArray(vaoId);
			// Draw 3 vertices (a triangle)
			glDrawArrays(GL_TRIANGLES, 0, 3);
			// Reset the state
			glBindVertexArray(0);
			glUseProgram(0);
			//
			//





			//swap the memory buffer with the screen buffer
			SDL_GL_SwapWindow(window);
		}

	}


}