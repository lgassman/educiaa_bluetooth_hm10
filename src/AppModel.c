/*
 * Model.c
 *
 *  Created on: Sep 22, 2019
 *      Author: leo
 */

#include "AppModel.h"

#ifndef NULL
	#define NULL 0
#endif



void appModel_init(AppModel * model, unsigned char enabled) {
	model->enabled = enabled;
	model->observerObject = NULL;
	model->observerFunction = NULL;
}

void appModel_setObserver(AppModel * model, void * observerObject, AppModelChangeObserver observerFunction ) {
	model->observerObject = observerObject;
	model->observerFunction = observerFunction;
}

void setValue(AppModel * model, unsigned char value) {
	model->enabled = value;
	if(model->observerFunction != NULL) {
		model->observerFunction(model->observerObject, model);
	}
}

void appModel_enable(AppModel * model) {
	setValue(model, 1);
}

void appModel_disable(AppModel * model) {
	setValue(model, 0);
}

unsigned char appModel_isEnabled(AppModel * model) {
	return model->enabled;
}

void appModel_toggle(AppModel * model){
	setValue(model, !model->enabled);
}


