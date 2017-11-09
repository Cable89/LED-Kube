#include <iostream>
#include "main.h"
#include "usb.h"
#include "cube.h"
#include "effect.h"
#include "menu.h"
using namespace std;

int main(){
	Effect^ kube = gcnew Effect(4,57600);
	kube->start();
	while(1){
		//runEffects(kube);
		cout << "rotate_random_pixels" << endl;
		kube->effect_rotate_random_pixels(1000,10);
		cout << "spheremove" << endl;
		kube->spheremove(1000,10);
		cout << "sidewaves" << endl;
		kube->sidewaves(1000,10);
		cout << "ripples" << endl;
		kube->ripples(1000,10);
		cout << "sinelines" << endl;
		kube->sinelines(1000, 10);
		cout << "fireworks" << endl;
		kube->fireworks(10,100);
		cout << "rain" << endl;
		kube->rain(200,80);
		cout << "PeakMeter" << endl;
		kube->peakMeter(20000);
		kube->peakMeter_rolling(2000);
	}
	delete kube;
	
	return 0;
}
/*
void runEffects(Effect^ kube){
	cout << "rotate_random_pixels" << endl;
	kube->effect_rotate_random_pixels(1000,10);
	cout << "spheremove" << endl;
	kube->spheremove(1000,10);
	cout << "sidewaves" << endl;
	kube->sidewaves(1000,10);
	cout << "ripples" << endl;
	kube->ripples(1000,10);
	cout << "sinelines" << endl;
	kube->sinelines(1000, 10);
	cout << "fireworks" << endl;
	kube->fireworks(10,100);
	cout << "rain" << endl;
	kube->rain(200,80);
}
*/