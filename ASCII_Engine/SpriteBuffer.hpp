#ifndef SPRITEBUFFER_HPP
#define SPRITEBUFFER_HPP

#include "SpriteBase.hpp"
#include <vector>

class SpriteBuffer : public SpriteBase
{
	//temporarios
	friend std::ostream &operator<<(std::ostream &, const SpriteBuffer &);
public:
	SpriteBuffer(unsigned , unsigned );
	virtual ~SpriteBuffer(){}
	
	void clear();
	
	//SpriteBase
	virtual void putAt(const SpriteBase &, unsigned = 0, unsigned = 0);
	virtual std::string whoami() const {return "SpriteBuffer";}
	
	//RenderBase
	virtual void init() {};
	virtual void update() {};
	
	std::string particionaString(std::string &obj, unsigned int inicio, unsigned int fim);
	
private:
	std::vector<std::string> sprt;
	
	//SpriteBase
	virtual std::string getLinha(unsigned) const;
	unsigned int contaCaracteres(const std::string &s) const;
};

#endif // SPRITEBUFFER_HPP
