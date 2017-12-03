#include "SceneFly.h"

SceneFly::SceneFly() {
	SceneFly(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

SceneFly::SceneFly(int w, int h) {
	windowWidth = w;
	windowHeight = h;

	glClearColor(0, 0, 0, 0);

	GlutScene::Initalize();

	camera.Initialize();
	camera.fly = true;
	camera.transform.position.y = 1;

	player = new ActorPlayer(Transform());
	player->Initialize();
	player->drawShip = true;

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

SceneFly::~SceneFly() {

}

void SceneFly::Render() {
	GlutScene::Clear();

	GlutScene::SetProjection(60, 0.1, 350);

	camera.Refresh();

	skyBox.RenderAt(camera.transform, 200);

	// Render our light
	light0->Render();

	glPushMatrix();

	glPushMatrix();

	player->Render();
	// very bad code
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->active)
			bullets[i]->Render();
		
	}

	glPopMatrix();



	glTranslatef(0, -50, 0);
	renderGround();

	glPopMatrix();

	glutPostRedisplay();

	CheckAndSwapBuffers();

}

void SceneFly::Update(void) {
	if (timeForNextFrame) {	

		camera.Refresh();

		player->Update();

		fpsCounter.displayFPSTitle("Scene 4 - World's Strangest Plane");

		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->transform.position += (camera.transform.rotation * 0.1);
			if (bullets[i]->transform.position.y <= -50) {
				//printf("making false\n");
				bullets[i]->active = false;
			}
		}

		light0->Update();

		glutPostRedisplay();
		timeForNextFrame = false;
	}
}

void SceneFly::EnterScene() {
	GlutScene::EnterScene();

	light0->enable();
}

void SceneFly::ExitScene() {
	GlutScene::ExitScene();

	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	glDisable(GL_FOG);
	fps = false;
}

void SceneFly::renderWorld() {

}

void SceneFly::renderGround() {
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

void SceneFly::ASCII(unsigned char key, int x, int y) {
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
		player->drawCollision = !player->drawCollision;
		

	}

	keyboard[key] = true;
}

void SceneFly::ASCIIUp(unsigned char key, int x, int y) {
	keyboard[key] = false;
}

void SceneFly::SpecialKey(int key, int x, int y) {
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
}

void SceneFly::Mouse(int button, int state, int x, int y) {
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

void SceneFly::Motion(int x, int y) {
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

void SceneFly::PassiveMotion(int x, int y) {
	Motion(x, y);
}

void SceneFly::Timer(int v) {
	if (fps) {
		//printf("hey\n");

		camera.prevTransform = camera.transform;
		player->prevTransform = player->transform;

		if (keyboard['w'] || keyboard['W']) {
			camera.MoveCamera(speed);
			handlePlayerCollision();
		}
		if (keyboard['s'] || keyboard['S']) {
			
		}
		if (keyboard['a'] || keyboard['A']) {
			
		}
		if (keyboard['d'] || keyboard['D']) {
			
		}
		if (leftdown) {
			fireBullet();
		}
		if (keyboard['q'] || keyboard['Q']) {
			
		}

		player->transform = camera.worldPlacement;
	}

	timeForNextFrame = true;
}

void SceneFly::fireBullet() {

	if (bullets.size() < 150) {
		ActorDisplay *b = new ActorDisplay(2, 4, 0, 0.5);
		b->transform.scale.x = b->transform.scale.y = b->transform.scale.z = 0.009;
		b->transform.rotation = player->transform.rotation;
		b->transform.position = player->transform.position;
		b->transform.rotation.y += 90;
		b->transform.rotation.x += 90;
		bullets.push_back(b);
	}
	else {
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i]->active = false) {
				printf("ok");
				bullets[i]->transform.rotation = player->transform.rotation;
				bullets[i]->transform.position = player->transform.position;
			}
		}
	}

}

void SceneFly::handlePlayerCollision() {
	
}

void SceneFly::handleBulletCollision() {

}