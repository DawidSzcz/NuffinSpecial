#include "BasicHeader.hpp"
#include "IDrawable.hpp"
#include "MonochromaticSphere.hpp"

void MonochromaticSphere::GenVertices(std::vector<Vertex_t>& vertices,std::vector<TrIndex_t>& triangles) const {
	// 1 front pole
	unsigned long int front_pole = vertices.size();
	vertices.push_back(Vertex_t(Position_t(0.0,0.0,1.0),Colour,Position_t(0.0,0.0,1.0)));

	// longitudes(latitudes-1) vertices on parallel rings
	unsigned long int start = vertices.size();
	for(unsigned long int lat=1 ; lat < latitudes ; lat++) {
		Coord_t z = glm::cos(M_PI*lat/latitudes);
		Coord_t r = glm::sin(M_PI*lat/latitudes);
		
		for(unsigned long int lon=0 ; lon < longitudes ; lon++) {
			Coord_t x = r*glm::cos(M_PI*2.0*lon/longitudes);
			Coord_t y = r*glm::sin(M_PI*2.0*lon/longitudes);
			Position_t pos = Position_t(x,y,z);

			// pos should be of length 1
			assert(glm::length(pos) < 1.0+eps && glm::length(pos) > 1.0-eps);

			vertices.push_back(Vertex_t(pos,Colour,pos));
		}
	}
	
	// 1 back pole
	unsigned long int back_pole = vertices.size();
	vertices.push_back(Vertex_t(Position_t(0.0,0.0,-1.0),Colour,Position_t(0.0,0.0,-1.0)));

	// longitudes front pole triangles:
	for(unsigned long int lon=0 ; lon < longitudes ; lon++) {
		triangles.push_back(TrIndex_t(	front_pole,
										start+lon,
										start+(lon+1)%longitudes));
	}

	// 2longitudes(latitudes-2) triangles on parallel rings
	for(unsigned long int lat=2 ; lat < latitudes ; lat++) {
		for(unsigned long int lon=0 ; lon < longitudes ; lon++) {
			triangles.push_back(TrIndex_t(	start+lon,
											start+longitudes+(lon+1)%longitudes,
											start+(lon+1)%longitudes));
			triangles.push_back(TrIndex_t(	start+lon,
											start+longitudes+lon,
											start+longitudes+(lon+1)%longitudes));
		}
		start+=longitudes;
	}

	// longitudes back pole triangles:
	for(unsigned long int lon=0 ; lon < longitudes ; lon++) {
		triangles.push_back(TrIndex_t(	back_pole,
										start+(lon+1)%longitudes,
										start+lon));
	}

	assert(GetVerticesNum() == 2 + longitudes*(latitudes-1));
	assert(GetTrianglesNum() == 2*longitudes*(latitudes-1));
}