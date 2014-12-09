#ifndef _DESTROYER_H_
#define _DESTROYER_H_

#include <iostream>

template<class Singleton>
class Destroyer
{
	public:
		Destroyer(Singleton* singleton = 0) : 
			c_singleton(singleton) {}
		~Destroyer()
		{
			delete c_singleton;
			c_singleton = 0;
		}

		void SetSingleton(Singleton* singleton)
		{
			c_singleton = singleton;
		}
	
	private:
		Destroyer(Destroyer const&);
		void operator=(Destroyer const&);

	private:
		Singleton* c_singleton;
};

#endif
