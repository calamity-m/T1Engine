#include "SceneMuseum.h"

SceneMuseum::SceneMuseum() {
	SceneMuseum(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

}

SceneMuseum::SceneMuseum(int w, int h) {
	windowWidth = w;
	windowHeight = h;
	
	glClearColor(0, 0, 0, 0);

	GlutScene::Initalize();

	camera.Initialize();
	camera.transform.position.y = 1;
	//glutSetKeyRepeat(1);

	baseShip = new ActorShip(0);
	baseShip->Initialize();
	baseShip->transform.scale.x = baseShip->transform.scale.y = baseShip->transform.scale.z = 0.08;
	baseShip->transform.position.x += 9;
	baseShip->transform.position.y += 1.3;
	baseShip->transform.position.z += 3.3;
	baseShip->transform.rotation.y -= 135;
	baseShip->collisionRadius = 2;

	displayShip = new ActorDisplay(0, 0, 0, 2);
	displayShip->Initialize();
	displayShip->transform.scale.x = displayShip->transform.scale.y = displayShip->transform.scale.z = 3;
	displayShip->transform.position.x += 290;
	displayShip->transform.position.y += 145;
	displayShip->transform.rotation.y -= 90;

	ariShip = new ActorDisplay(1, 5, 1, 2);
	ariShip->transform.scale.x = ariShip->transform.scale.y = ariShip->transform.scale.z = 0.35;
	ariShip->transform.position.x += 9;
	ariShip->transform.position.y += 0.3;
	ariShip->transform.position.z -= 3.3;
	ariShip->transform.rotation.y += -45;
	ariShip->collisionRadius = 2;
	//ariShip->drawCollision = true;
	//ariShip->rotate = true;

	shuttleShip = new ActorDisplay(3, 4, 1, 2);
	shuttleShip->transform.scale.x = shuttleShip->transform.scale.y = shuttleShip->transform.scale.z = 0.015;
	shuttleShip->transform.position.x += 4;
	shuttleShip->transform.position.y += 0.3;
	shuttleShip->transform.position.z -= 3;
	shuttleShip->transform.rotation.y += 45;
	shuttleShip->collisionRadius = 1.3;
	//shuttleShip->drawCollision = true;

	puddleShip = new ActorDisplay(2, 6, 1, 2);
	puddleShip->transform.scale.x = puddleShip->transform.scale.y = puddleShip->transform.scale.z = 0.09;
	puddleShip->transform.position.x += 4.3;
	puddleShip->transform.position.y += 0.3;
	puddleShip->transform.position.z += 3;
	puddleShip->transform.rotation.y -= 135;
	puddleShip->collisionRadius = 1.3;
	//puddleShip->drawCollision = true;
	//shuttleShip->rotate = true;

	portal = new ActorPortal(4);
	//portal->transform.rotation.x = -90;
	portal->transform.position.y += 5.5;
	portal->transform.position.x += 30;
	portal->transform.rotation.y = 90;

	player = new ActorPlayer(Transform());

	light0 = new Lights(GL_LIGHT0);
	light0->setPos(25.0f, 45.0f, -35.0f, 0.0f);
	light0->enable();

	skyBox = SkyRenderer(SkyRenderer::Box);
	int sky[6] = { ResourceManager::getTexture(7), ResourceManager::getTexture(8), ResourceManager::getTexture(9),
		ResourceManager::getTexture(10), ResourceManager::getTexture(11), ResourceManager::getTexture(12) };
	skyBox.setSkyBoxTexture(sky);

	for (int i = 0; i < 256; i++) {
		keyboard[i] = false;
	}
}

SceneMuseum::~SceneMuseum() {

}

void SceneMuseum::Render() {
	GlutScene::Clear();

	GlutScene::SetProjection(60, 0.1, 350);

	// Update our camera
	camera.Refresh();

	//glDisable(GL_FOG)
	skyBox.RenderAt(camera.transform, 200);

	renderFog();

	// Render our light
	light0->Render();

	glPushMatrix();

	glPushMatrix();

	shuttleShip->Render();
	puddleShip->Render();
	ariShip->Render();
	glPushMatrix();
	if (rotateModels)
		baseShip->transform.rotation.y = ariShip->GetRotation();
	else
		baseShip->transform.rotation.y = -135;
	baseShip->Render();
	glPopMatrix();
	displayShip->Render();
	
	if (showPortal) 
		portal->Render();

	glPopMatrix();
	//baseShip->Render();
	player->Render();

	glPopMatrix();

	renderGround();
	//renderGrid();

	// Redisplay
	glutPostRedisplay();

	CheckAndSwapBuffers();
}

void SceneMuseum::Update() {
	if (timeForNextFrame) {

		fpsCounter.displayFPSTitle("Scene 1 - World's Worst Museum");

		camera.Refresh();

		baseShip->Update();
		ariShip->Update();
		shuttleShip->Update();
		puddleShip->Update();
		if (portal) portal->Update();
		//displayShip->Update();

		player->Update();

		light0->Update();

		glutPostRedisplay();
		timeForNextFrame = false;
	}
}

void SceneMuseum::EnterScene() {
	GlutScene::EnterScene();

	light0->enable();
}

void SceneMuseum::ExitScene() {
	GlutScene::ExitScene();

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	glDisable(GL_FOG);
	fps = false;
}

void SceneMuseum::renderWorld() {

}

void SceneMuseum::renderGrid() {
	glPushMatrix();
	glColor3f(1, 1, 1);

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);
		glEnd();
	}

	glPopMatrix();
}

void SceneMuseum::renderGround() {
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);

	//glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(3));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(-80, 0, 80);

	glTexCoord2f(40, 0);
	glVertex3f(80, 0, 80);

	glTexCoord2f(40, 40);
	glVertex3f(80, 0, -80);

	glTexCoord2f(0, 40);
	glVertex3f(-80, 0, -80);

	glEnd();

	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void SceneMuseum::renderFog() {
	if (fog) {
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR); // try GL_EXP
										//glFogi(GL_FOG_MODE, GL_EXP2); // try GL_EXP
		float fogColour[3] = { 0.1, 0.5, 0.25 };
		glFogfv(GL_FOG_COLOR, fogColour);
		glFogf(GL_FOG_DENSITY, 0.4);   // doesn't affect GL_LINEAR fog
		glFogf(GL_FOG_START, 0.1);    // doesn't affect GL_EXP fog
		glFogf(GL_FOG_END, 15); 	   // doesn't affect GL_EXP fog
	}
	else {
		glDisable(GL_FOG);
	}
}

void SceneMuseum::ASCII(unsigned char key, int x, int y) {
	
	if (key == 27) {
		exit(0);
	}

	if (key == ' ') {
		fps = !fps;

		if (fps) {
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(windowWidth / 2, windowHeight / 2);
		}
		else {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}

	if (key == 'b' || key == 'B') {
		ariShip->drawCollision = !ariShip->drawCollision;
		shuttleShip->drawCollision = !shuttleShip->drawCollision;
		puddleShip->drawCollision = !puddleShip->drawCollision;
		player->drawCollision = !player->drawCollision;
		baseShip->drawCollision = !baseShip->drawCollision;
		//ariShip->drawCollision = !ariShip->drawCollision;

	}

	if (key == '5') {
		fog = !fog;
	}

	if (key == '[') {
		player->drawShip = !player->drawShip;
	}

	if (key == 'p' || key == 'P') {
		showPortal = !showPortal;
	}

	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
		shiftmodifier = true;
	}
	else {
		shiftmodifier = false;
	}

	keyboard[key] = true;
}

void SceneMuseum::ASCIIUp(unsigned char key, int x, int y) {
	keyboard[key] = false;
}

void SceneMuseum::SpecialKey(int key, int x, int y) {
	if (key == GLUT_KEY_F3) {
		fps = !fps;

		if (fps) {
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(windowWidth / 2, windowHeight / 2);
		}
		else {
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}

	if (key == GLUT_KEY_F2) {
		//displayShip->rotate = !displayShip->rotate;
		ariShip->rotate = !ariShip->rotate;
		shuttleShip->rotate = !shuttleShip->rotate;
		puddleShip->rotate = !puddleShip->rotate;
		rotateModels = !rotateModels;
	}
}

void SceneMuseum::Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			leftdown = true;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			rightdown = true;
		}
	}
	else if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON) {
			leftdown = false;
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			rightdown = false;
		}
	}
}

void SceneMuseum::Motion(int x, int y) {
	// This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
	// This avoids it being called recursively and hanging up the event loop
	static bool just_warped = false;

	if (just_warped) {
		just_warped = false;
		return;
	}

	if (fps) {
		int dx = x - windowWidth / 2;
		int dy = y - windowHeight / 2;

		if (dx) {
			camera.RotateCameraYaw(sensitivity*dx);
		}

		if (dy) {
			camera.RotateCameraPitch(-sensitivity*dy);
		}

		glutWarpPointer(windowWidth / 2, windowHeight / 2);

		just_warped = true;

		player->transform = camera.worldPlacement;
	}
}

void SceneMuseum::PassiveMotion(int x, int y) {
	Motion(x, y);
}

void SceneMuseum::Timer(int v) {
	if (fps) {
		//printf("hey\n");

		camera.prevTransform = camera.transform;
		player->prevTransform = player->transform;

		if (keyboard['w'] || keyboard['W']) {
			camera.MoveCamera(speed);
			handlePlayerCollision();
		}
		if (keyboard['s'] || keyboard['S']) {
			camera.MoveCamera(-speed);
			handlePlayerCollision();
		}
		if (keyboard['a'] || keyboard['A']) {
			camera.StrafeCamera(speed);
			handlePlayerCollision();
		}
		if (keyboard['d'] || keyboard['D']) {
			camera.StrafeCamera(-speed);
			handlePlayerCollision();
		}
		if (leftdown) {
			camera.FlyCamera(speed);
			handlePlayerCollision();
		}
		if (keyboard['q'] || keyboard['Q']) {
			camera.FlyCamera(-speed);
			handlePlayerCollision();
		}

		player->transform = camera.worldPlacement;
	}

	timeForNextFrame = true;
}

void SceneMuseum::handlePlayerCollision() {
	if (player->transform.position.y <= 1) {
		camera.transform.position.y = 1;
		//player->transform.position.y = 1;
	}

	if (Collision::checkCollisionVec3(camera.transform.position, ariShip->transform.position, player->collisionRadius, ariShip->collisionRadius)) {
		camera.transform = camera.prevTransform;
		player->transform = player->prevTransform;
	}
	if (Collision::checkCollisionVec3(camera.transform.position, shuttleShip->transform.position, player->collisionRadius, shuttleShip->collisionRadius)) {
		camera.transform = camera.prevTransform;
		player->transform = player->prevTransform;
		//glutGet(G)
	}
	if (Collision::checkCollisionVec3(camera.transform.position, puddleShip->transform.position, player->collisionRadius, puddleShip->collisionRadius)) {
		camera.transform = camera.prevTransform;
		player->transform = player->prevTransform;
	}
	if (Collision::checkCollisionVec3(camera.transform.position, baseShip->transform.position, player->collisionRadius, baseShip->collisionRadius)) {
		camera.transform = camera.prevTransform;
		player->transform = player->prevTransform;
	}
}

