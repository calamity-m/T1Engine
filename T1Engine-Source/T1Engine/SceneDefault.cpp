#include "SceneDefault.h"

SceneDefault::SceneDefault() {
	SceneDefault(glutGet(GLUT_INIT_WINDOW_WIDTH), glutGet(GLUT_INIT_WINDOW_HEIGHT));
}

SceneDefault::SceneDefault(int w, int h) {
	// Do Initializations
	windowWidth = w;
	windowHeight = h;
	fovAngle = 60;
	spinAngle = 0;
	wheelAngle = 0;
	viewPoint.x = 44;
	viewPoint.y = 12;
	viewPoint.z = 44;
	lookAtVec.x = 0;
	lookAtVec.y = 0;
	lookAtVec.z = 0;
	upVec.x = 0;
	upVec.y = 1;
	upVec.z = 0;

	glClearColor(0, 0, 0, 0);

	// Setting base colour
	baseColour[0] = 0;
	baseColour[1] = 1;
	baseColour[2] = 0;
	showInstructions = false;

	GlutScene::Initalize();

	ship = new ActorShip(0);
	ship->Initialize();
	ship->lighting = 0;
	ship->transform.position.z -= 35;
	ship2 = new ActorShip(0);
	ship2->Initialize();
	ship2->transform.rotation.x = 90;

	ariShip = new ActorDisplay(1, 5, 1, 2);
	ariShip->Initialize();
	ariShip->lighting = true;
	ariShip->transform.position.z += 35;
	ariShip->transform.position.y -= ariShip->GetModelY();
	ariShip->transform.rotation.y += 180;
	ariShip->transform.scale.x = ariShip->transform.scale.y = ariShip->transform.scale.z = 1.5;


	planet = new ActorPlanet(-0.1, 175, ActorPlanet::Venus);
	planet->Initialize();
	planet->transform.position.x = -145;
	planet->transform.position.y = -145;

	light0 = new Lights(GL_LIGHT0);
	light0->setPos(15.0f, 19.50f, 35.0f, 1.0f);
	light0->baseMaterial.setWhiteRubber();
	light0->enable();

	text2d = new Text2D();

	skyBox = SkyRenderer(SkyRenderer::Box);
	int sky[6] = { ResourceManager::getTexture(13), ResourceManager::getTexture(14), ResourceManager::getTexture(15),
		ResourceManager::getTexture(16), ResourceManager::getTexture(17), ResourceManager::getTexture(18) };
	skyBox.setSkyBoxTexture(sky);

	timeForNextFrame = true;
}

SceneDefault::~SceneDefault() {

}

void SceneDefault::EnterScene() {
	GlutScene::EnterScene();

	light0->enable();
}

void SceneDefault::ExitScene() {
	GlutScene::ExitScene();

	glDisable(GL_FOG);
}

void SceneDefault::RenderWorld() {
	// Draw models and lights
	glPushMatrix();
		glColor3f(0, 1, 0);
		light0->Render();
		glPushMatrix();
			ship->Render();
			//ship2->Render();
			ariShip->Render();
			planet->Render();
		glPopMatrix();
	glPopMatrix();

	// Text
	glPushMatrix();
	if (showInstructions) {
		glColor3f(1, 1, 0);
		glDisable(GL_LIGHTING);
		text2d->set2D(windowWidth, windowHeight);
		text2d->renderText(10, 370, "T or F1 - Show Instructions");
		text2d->renderText(10, 390, "Right Click - Menu");
		text2d->renderText(10, 410, "Q - Rotate Ship, E - Counter Rotate");
		text2d->renderText(10, 430, "1 - Move Light Left, 2 - Move Light Right, 3 - Move Light Forward, 4 - Move Light Back");
		text2d->renderText(10, 450, "Arrow Keys and PGUP/PGDOWN move eyepos");
		text2d->renderText(10, 470, "Light Pos: %8.2f, %8.2f, %8.2f", light0->transform.position.x, light0->transform.position.y,
			light0->transform.position.z);
		text2d->renderText(10, 490, "EyePoint: %8.2f, %8.2f, %8.2f", viewPoint.x, viewPoint.y, viewPoint.z);
		text2d->renderText(10, 500, "INSTRUCTIONS:");
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();

}

void SceneDefault::Render() {
	GlutScene::Clear();

	GlutScene::SetProjection(fovAngle, NEARPLANE, 350);

	// Set ViewPoint/ViewPort
	glLoadIdentity();
	gluLookAt(viewPoint.x, viewPoint.y, viewPoint.z,
		lookAtVec.x, lookAtVec.y, lookAtVec.z,
		upVec.x, upVec.y, upVec.z);

	Transform t;
	t.position.x = viewPoint.x;
	t.position.y = viewPoint.y;
	t.position.z = viewPoint.z;

	skyBox.RenderAt(t, 200);

	//glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_LINEAR); // try GL_EXP
									//glFogi(GL_FOG_MODE, GL_EXP2); // try GL_EXP
	float fogColour[3] = { 0, 0, 0 };
	glFogfv(GL_FOG_COLOR, fogColour);
	glFogf(GL_FOG_DENSITY, 0.4);   // doesn't affect GL_LINEAR fog
	glFogf(GL_FOG_START, 0.1);    // doesn't affect GL_EXP fog
	glFogf(GL_FOG_END, 100); 	   // doesn't affect GL_EXP fog


	// Draw our World
	RenderWorld();

	glDisable(GL_FOG);

	// Redisplay
	glutPostRedisplay();

	CheckAndSwapBuffers();
}

void SceneDefault::Update(void) {
	//printf("fuck\n");

	if (timeForNextFrame) {

		ship->Update();

		//ship2->Update();

		ariShip->Update();

		fps.displayFPSTitle("Scene 2 - World's Longest Stalemate");

		planet->Update();

		light0->Update();

		glutPostRedisplay();
		timeForNextFrame = false;
	}
}

void SceneDefault::ASCII(unsigned char key, int x, int y) {
	if (key == 27) // ESC
		exit(0);

	if (key == '3')
		light0->transform.position.z -= 0.5;

	if (key == '4')
		light0->transform.position.z += 0.5;

	if (key == '1')
		light0->transform.position.x -= 0.5;

	if (key == '2')
		light0->transform.position.x += 0.5;

	if (key == '5')
		light0->transform.position.y += 0.5;

	if (key == '6')
		light0->transform.position.y -= 0.5;

	if (key == 'q' || key == 'Q') {
		ship->transform.rotation.x += 2;
	}

	if (key == 'e' || key == 'E') {
		ship->transform.rotation.x -= 2;
	}

	if (key == 't' || key == 'T') {
		showInstructions = !showInstructions;
	}

	//glutPostRedisplay();
}

void SceneDefault::SpecialKey(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) viewPoint.x += 2;
	if (key == GLUT_KEY_RIGHT) viewPoint.x -= 2;
	if (key == GLUT_KEY_UP) viewPoint.z -= 2;
	if (key == GLUT_KEY_DOWN) viewPoint.z += 2;
	if (key == GLUT_KEY_PAGE_UP) viewPoint.y += 2;
	if (key == GLUT_KEY_PAGE_DOWN) viewPoint.y -= 2;
	if (key == GLUT_KEY_F1) showInstructions = !showInstructions;

	//glutPostRedisplay();
}