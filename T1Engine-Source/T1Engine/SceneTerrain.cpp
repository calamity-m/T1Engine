#include "SceneTerrain.h"

SceneTerrain::SceneTerrain() {
	SceneTerrain(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

SceneTerrain::SceneTerrain(int w, int h) {
	// Do Initializations
	windowWidth = w;
	windowHeight = h;
	fovAngle = 60;
	spinAngle = 0;
	wheelAngle = 0;
	viewPoint.x = 12;
	viewPoint.y = 12;
	viewPoint.z = 26;
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
	showTexturing = false;
	showWireframe = false;

	GlutScene::Initalize();

	ter = Terrain(ResourceManager::getTerrain(0));
	ter.transform.position.x = -59;
	ter.transform.position.z = -59;
	skyBox = SkyRenderer(SkyRenderer::Box);
	int b = ResourceManager::getTexture(5);
	int sky[6] = { ResourceManager::getTexture(7), ResourceManager::getTexture(8), ResourceManager::getTexture(9),
		ResourceManager::getTexture(10), ResourceManager::getTexture(11), ResourceManager::getTexture(12) };
	skyBox.setSkyBoxTexture(sky);

	/**********************************
	*
	* NOTE: Needs to be added to enter/exit level
	* Enable on enter
	* Disable on exit
	*
	*
	**********************************/
	light0 = new Lights(GL_LIGHT0);
	light0->setPos(15.0f, 5.0f, 35.0f, 1.0f);
	light0->baseMaterial.setWhiteRubber();
	light0->enable();
	//light0->setAttenuation(0.1);
	text2d = new Text2D();

	timeForNextFrame = true;
}

SceneTerrain::~SceneTerrain() {

}

void SceneTerrain::RenderWorld() {
	// Draw models and lights
	glPushMatrix();
		glColor3f(0, 1, 0);
		glPushMatrix();
		glEnable(GL_LIGHTING);
			//glDisable(GL_LIGHTING);
		if (showTexturing)
			glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture(4));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		ter.Render();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		light0->Render();
	glPopMatrix();

	ResourceManager::getMaterial(0).setGlMaterial();

	// Text
	glPushMatrix();
	if (showInstructions) {
		glColor3f(1, 1, 0);
		glDisable(GL_LIGHTING);
		text2d->set2D(windowWidth, windowHeight);
		text2d->renderText(10, 350, "F3 - Show Wireframe Mode");
		text2d->renderText(10, 370, "F2 - Show Terrain Texturing");
		text2d->renderText(10, 390, "T or F1 - Show Instructions");
		text2d->renderText(10, 410, "Right Click - Menu");
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

void SceneTerrain::Render() {
	GlutScene::Clear();

	GlutScene::SetProjection(fovAngle, NEARPLANE, 350);

	// Set ViewPoint/ViewPort
	glLoadIdentity();
	gluLookAt(viewPoint.x, viewPoint.y, viewPoint.z,
		lookAtVec.x, lookAtVec.y, lookAtVec.z,
		upVec.x, upVec.y, upVec.z);

	// Skybox
	Transform t;
	t.position.x = viewPoint.x;
	t.position.y = viewPoint.y;
	t.position.z = viewPoint.z;

	glDisable(GL_FOG);
	skyBox.RenderAt(t, 200);
	glEnable(GL_FOG);
	if (showWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Draw our World
	RenderWorld();

	// Redisplay
	glutPostRedisplay();

	CheckAndSwapBuffers();
}

void SceneTerrain::Update(void) {
	//printf("fuck\n");

	if (timeForNextFrame) {

		fps.displayFPSTitle("Scene 2 - Terrain");

		ter.Update();

		light0->Update();

		glutPostRedisplay();
		timeForNextFrame = false;
	}
}

void SceneTerrain::EnterScene() {
	GlutScene::EnterScene();

	light0->enable();
}

void SceneTerrain::ExitScene() {
	GlutScene::ExitScene();

	glDisable(GL_FOG);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void SceneTerrain::ASCII(unsigned char key, int x, int y) {
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

	if (key == 't' || key == 'T') {
		showInstructions = !showInstructions;
	}

	//glutPostRedisplay();
}

void SceneTerrain::SpecialKey(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) viewPoint.x += 2;
	if (key == GLUT_KEY_RIGHT) viewPoint.x -= 2;
	if (key == GLUT_KEY_UP) viewPoint.z -= 2;
	if (key == GLUT_KEY_DOWN) viewPoint.z += 2;
	if (key == GLUT_KEY_PAGE_UP) viewPoint.y += 2;
	if (key == GLUT_KEY_PAGE_DOWN) viewPoint.y -= 2;
	if (key == GLUT_KEY_F1) showInstructions = !showInstructions;
	if (key == GLUT_KEY_F2) showTexturing = !showTexturing;
	if (key == GLUT_KEY_F3) showWireframe = !showWireframe;
	//glutPostRedisplay();
}