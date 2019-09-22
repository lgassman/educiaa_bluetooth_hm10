/*
 * AppModelRender.c
 *
 *  Created on: Sep 22, 2019
 *      Author: leo
 */
#include "AppModelRender.h"

void appModelRender_init(AppModelRender * render, AppModel * model, gpioMap_t gpio) {
	render->model = model;
	render->gpio = gpio;
}

void appModelRender_update(AppModelRender * render) {
	gpioWrite(render->gpio, appModel_isEnabled(render->model));
}




