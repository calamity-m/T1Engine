#include "Terrain.h"

Terrain::Terrain() {

}

Terrain::Terrain(ResourceManager::TerrainDEM d) {
	dem = d;
}

void Terrain::Update() {

}

void Terrain::Render() {
	glPushMatrix();

	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1, 0, 0);
	glRotatef(transform.rotation.y, 0, 1, 0);
	glRotatef(transform.rotation.z, 0, 0, 1);

	dem.Render();

	glPopMatrix();
}
