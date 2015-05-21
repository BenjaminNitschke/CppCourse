#include "stdafx.h"
#include "FpsGame.h"
#define _USE_MATH_DEFINES
#include <Math.h>

using namespace Fps;

FpsGame::FpsGame()
	: Game("Fps")
{
	glClearColor(49 / 255.0f, 90 / 255.0f, 137 / 255.0f, 1.0f);
	groundTexture = std::make_shared<Texture>("Ground.png");
	wallTexture = std::make_shared<Texture>("Wall.png");
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);
}

void FpsGame::PlayGame()
{
	SetupWorld();
	Run([=]()
	{
		HandleInput();
		DrawWorld();
	});
}

void readstr(FILE *f, char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
}

void FpsGame::SetupWorld()
{
	float x, y, z, u, v;
	int numtriangles;
	FILE *filein;
	char oneline[255];
	fopen_s(&filein, "world.txt", "rt");
	readstr(filein, oneline);
	sscanf_s(oneline, "NUMPOLLIES %d\n", &numtriangles);
	for (int loop = 0; loop < numtriangles; loop++)
		for (int vert = 0; vert < 3; vert++)
		{
			readstr(filein, oneline);
			sscanf_s(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			vertices.push_back(VertexPositionUV(x, y, z, u, v));
		}
	fclose(filein);
}

void FpsGame::HandleInput()
{
	const float DegreeToRadians = (float)M_PI / 180.0f;
	const float MoveSpeed = 2.0f;
	const float RotationSpeed = 90.0f;
	if (upPressed || downPressed)
	{
		auto movement = Vector2D(
			(float)sin(headingInDegree*DegreeToRadians) * MoveSpeed * GetTimeDelta(),
			(float)cos(headingInDegree*DegreeToRadians) * MoveSpeed * GetTimeDelta());
		playerPosition = playerPosition + movement * (upPressed ? -1.0f : 1.0f);
	}
	if (leftPressed || rightPressed)
		headingInDegree += (leftPressed ? 1.0f : -1.0f) * RotationSpeed * GetTimeDelta();
}

void FpsGame::DrawWorld()
{
	SetupProjectionMatrix();
	SetupCameraViewMatrix();
	DrawGround();
	DrawWalls();
}

void FpsGame::SetupProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat zNear = 0.1f;
	GLfloat zFar = 100.0f;
	GLfloat aspect = viewportWidth / (float)viewportHeight;
	GLfloat fH = tan(float(45.0 / 360.0f * 3.14159f)) * zNear;
	GLfloat fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void FpsGame::SetupCameraViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(360.0f - headingInDegree, 0, 1.0f, 0);
	glTranslatef(-playerPosition.x, -0.5f, -playerPosition.y);
}

void FpsGame::DrawGround()
{
	glBindTexture(GL_TEXTURE_2D, groundTexture->GetHandle());
	glBegin(GL_TRIANGLES);
	for (int v = 0; v < 6; v++) // Ground for first 6 vertices
		vertices[v].Draw();
	glEnd();
}

void FpsGame::DrawWalls()
{
	glBindTexture(GL_TEXTURE_2D, wallTexture->GetHandle());
	glBegin(GL_TRIANGLES);
	for (int v = 6; v < (int)vertices.size(); v++) // Rest is walls
		vertices[v].Draw();
	glEnd();
}