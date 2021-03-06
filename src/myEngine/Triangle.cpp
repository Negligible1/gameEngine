#include "Triangle.h"

namespace myengine
{

	void Triangle::SetPositions()
	{
		//Set position vecs to draw triangle
		positions.push_back(0.0f);
		positions.push_back(0.5f);
		positions.push_back(0.0f);

		positions.push_back(-0.5f);
		positions.push_back(-0.5f);
		positions.push_back(0.0f);

		positions.push_back(0.5f);
		positions.push_back(-0.5f);
		positions.push_back(0.0f);		
	}

	void Triangle::VAOShit()
	{
		GLuint positionsVboId = 0;

		// Create a new VBO on the GPU and bind it
		glGenBuffers(1, &positionsVboId);

		if (!positionsVboId)
		{
			throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, positionsVboId);

		// Upload a copy of the data from memory into the new VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), &positions.at(0), GL_STATIC_DRAW);

		// Reset the state
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		vaoId = 0;

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
	}

	void Triangle::Shader()
	{
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
			"void main()                          " \
			"{                                    " \
			"  gl_FragColor = vec4(1, 0, 1, 1);   " \
			"}                                    ";

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
		programId = glCreateProgram();
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		// Ensure the VAO "position" attribute stream gets set as the first position
		// during the link.
		glBindAttribLocation(programId, 0, "in_Position");
		glBindAttribLocation(programId, 1, "in_Colour");

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
	}

	void Triangle::Initialise()
	{
		SetPositions();

		VAOShit();

		Shader();
	}

	void Triangle::Draw()
	{
		// Instruct OpenGL to use our shader program and our VAO
		glUseProgram(programId);
		glBindVertexArray(vaoId);

		// Draw 3 vertices (a triangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Reset the state
		glBindVertexArray(0);
		glUseProgram(0);
	}
}