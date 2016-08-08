#pragma once



struct TextureData{
	TextureData(){};
	TextureData(unsigned int id,unsigned int type):id(id),type(type){};
	unsigned int id;
	unsigned int type;

};
