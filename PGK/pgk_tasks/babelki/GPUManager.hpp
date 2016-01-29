#ifndef GPU_MANAGER_HPP
#define GPU_MANAGER_HPP

#include <iostream>
#include <utility>
#include <tuple>
#include <vector>
#include <algorithm>
#include "BasicHeader.hpp"
#include "IDrawable.hpp"
#include "PointLight.hpp"
#include "IShader.hpp"

class GPUManager {
public:
	virtual void DrawTriangles(GLsizei triangles_num,GLuint element_buffer_offset=0) {
		DrawElements(GL_TRIANGLES,triangles_num*3,INDEX_TYPE,(void*)element_buffer_offset);
	}

	virtual void DrawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid* indices) {
		buffers.finalize();
		element_buffers.finalize();
		glDrawElements(mode,count,type,indices);
	}

	virtual void BindProgram(IShader* p) {
		if(!isBoundProgram || programCache != p) {
			if(isBoundProgram) programCache->OnUnbind();
			isBoundProgram = true;
			programCache = p;
			p->OnBind();
			isDifferentProgramForSameArrayBuffer = true;
		}
	}

	virtual void SetUniforms(const IDrawable& d,const ICamera* camera,const std::vector<const PointLight*>& lights) {
		assert(isBoundProgram);
		programCache->SetUniforms(d,camera,lights);
	}

	virtual std::tuple<GLuint,GLuint,GLuint> StoreVertices(	const std::vector<Vertex_t>& vertices,
															const std::vector<TrIndex_t>& triangles) {
		GLuint vbuffer,vbuffer_offset,ebuffer,ebuffer_offset;
		std::tie(vbuffer,vbuffer_offset) = buffers.store_data((const unsigned char*)vertices.data(),sizeof(Vertex_t)*vertices.size());
		if(vbuffer_offset == 0) {
			std::tie(ebuffer,ebuffer_offset) = element_buffers.store_data((const unsigned char*)triangles.data(),sizeof(TrIndex_t)*triangles.size());
		} else {
			std::vector<TrIndex_t> new_triangles(triangles);
			for(auto& tr : new_triangles) tr += vbuffer_offset/sizeof(Vertex_t);
			std::tie(ebuffer,ebuffer_offset) = element_buffers.store_data((const unsigned char*)new_triangles.data(),sizeof(TrIndex_t)*new_triangles.size());
		}
		return std::make_tuple(vbuffer,ebuffer,ebuffer_offset);
	}

	virtual void BindArrayBuffer(GLuint id) {
		if(!isBoundArrayBuffer || arrayBufferCache != id) {
			assert(buffers.member(id));
			isBoundArrayBuffer = true;
			arrayBufferCache = id;
			glBindBuffer(GL_ARRAY_BUFFER,id);
			if(isBoundProgram) programCache->OnArrayBufferBind();
			isDifferentProgramForSameArrayBuffer = false;
		} else if(isDifferentProgramForSameArrayBuffer) {
			programCache->OnArrayBufferBind();
			isDifferentProgramForSameArrayBuffer = false;
		}
	}

	virtual void BindElementArrayBuffer(GLuint id) {
		if(!isBoundElementArrayBuffer || elementArrayBufferCache != id) {
			assert(element_buffers.member(id));
			isBoundElementArrayBuffer = true;
			elementArrayBufferCache = id;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
		}
	}

	virtual void ClearBuffers() {
		if(isDepthTest) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		else glClear(GL_COLOR_BUFFER_BIT);
	}

	virtual void SetClearColour(Colour_t c) {
		if(!isSetClearColour || clearColourCache != c) {
			isSetClearColour = true;
			clearColourCache = c;
			glClearColor(c.x,c.y,c.z,0.0); //fuj!
		}
	}

	virtual void SetBackFaceCulling(bool state) {
		if(isBackFaceCulling != state) {
			isBackFaceCulling = state;
			if(state) glEnable(GL_CULL_FACE);
			else glDisable(GL_CULL_FACE);
		}
	}
	
	virtual void SetDepthTest(bool state) {
		if(isDepthTest != state) {
			isDepthTest = state;
			if(state) {
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS); 
			} else {
				glDisable(GL_DEPTH_TEST);
			}
		}
	}

	GPUManager() { buffers.setParent(this); element_buffers.setParent(this); }

	virtual ~GPUManager() {
		buffers.clear();
		element_buffers.clear();
	}
protected:
	bool isBoundArrayBuffer = false;
	GLuint arrayBufferCache;
	bool isDifferentProgramForSameArrayBuffer = false;

	bool isBoundElementArrayBuffer = false;
	GLuint elementArrayBufferCache;

	bool isBoundProgram = false;
	IShader* programCache;

	bool isSetClearColour = false;
	Colour_t clearColourCache;
	bool isBackFaceCulling = false;
	bool isDepthTest = false;

	class BuffersPool {
	public:
		std::pair<GLuint,GLuint> store_data(const unsigned char* bufferdata,GLuint size) {
			assert(size > 0);
			if(!is_open()) open_id = gen();
			GLuint offset = open_data.size();
			open_data.insert(open_data.end(),bufferdata,bufferdata+size);
			return std::make_pair(open_id,offset);
		}
		void finalize() { if(is_open()) { send(open_id,open_data.data(),open_data.size()); open_data.clear(); } }
		bool member(GLuint id) { return (find(all.begin(),all.end(),id) != all.end()); }
		void clear() { glDeleteBuffers(all.size(), all.data()); }
		void setParent(GPUManager* target) { parent = target; }
	private:
		GLuint gen() { GLuint res; glGenBuffers(1, &res); all.push_back(res); return res; }
		void send(GLuint id,const unsigned char* data,GLuint size) { parent->bindBuffer(id); glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,GL_STATIC_DRAW); }
		bool is_open() { return !open_data.empty(); }
		std::vector<GLuint> all;
		GLuint open_id;
		std::vector<unsigned char> open_data;
		GPUManager* parent;
	} buffers,element_buffers;

	virtual void bindBuffer(GLuint id) {
		if(!isBoundElementArrayBuffer || elementArrayBufferCache != id) {
			isBoundElementArrayBuffer = true;
			elementArrayBufferCache = id;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
		}
	}
};

#endif