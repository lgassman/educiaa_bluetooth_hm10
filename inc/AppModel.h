/*
 * Model.h
 *
 *  Created on: Sep 22, 2019
 *      Author: leo
 */

#ifndef PROGRAMS_BTEXAMPLE_INC_APPMODEL_H_
#define PROGRAMS_BTEXAMPLE_INC_APPMODEL_H_



struct AppModel;

typedef void (*AppModelChangeObserver)(void * , struct AppModel * );


typedef struct AppModel{
	unsigned char enabled;
	AppModelChangeObserver observerFunction;
	void * observerObject;
}AppModel;




void appModel_init(AppModel * model, unsigned char enabled);
void appModel_setObserver(AppModel * model, void * observerObject, AppModelChangeObserver observerFunction );
void appModel_enable(AppModel * model);
void appModel_disable(AppModel * model);
void appModel_toggle(AppModel * model);


unsigned char appModel_isEnabled(AppModel * model);


#endif /* PROGRAMS_BTEXAMPLE_INC_APPMODEL_H_ */
