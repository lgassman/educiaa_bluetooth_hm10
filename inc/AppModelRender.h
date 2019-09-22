/*
 * ModelRender.h
 *
 *  Created on: Sep 22, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_BTEXAMPLE_INC_APPMODELRENDER_H_
#define PROGRAMS_BTEXAMPLE_INC_APPMODELRENDER_H_

#include <sapi.h>
#include <AppModel.h>

typedef struct {
	gpioMap_t gpio;
	AppModel * model;
} AppModelRender ;

void appModelRender_init(AppModelRender * render, AppModel * model, gpioMap_t gpio);
void appModelRender_update(AppModelRender * render);

#endif /* PROGRAMS_BTEXAMPLE_INC_APPMODELRENDER_H_ */
