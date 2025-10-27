#include "system.h"
#include "launch.hpp"

int main(){
	App app;
	app.init();
	while(1){
		app.run();
	}
}
