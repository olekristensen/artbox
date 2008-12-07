#define OF_ADDON_USING_OFXGUI
#define OF_ADDON_USING_OFXOSC

#include "ofMain.h"
#include "ofAddons.h"

#ifndef _OFX_SHARED_H_
#define _OFX_SHARED_H_


class SharedVariable{
	enum{SHARED_BOOL, SHARED_INT, SHARED_FLOAT, SHARED_STRING};
public:
	
	int * valueInt;
	float * valueFloat;
	bool * valueBool;
	string * valueString;
	
	int oldInt;
	float oldFloat;
	bool oldBool;
	string oldString;
	bool allowChange;
	string id;
	
	int type;	
	
	SharedVariable(int * val, string name, bool _allowChange = true){
		valueInt = val;
		type = SHARED_INT;
		allowChange = _allowChange;
		id = name;
	//	cout<<"Created int "<<name<<endl;
	}
	SharedVariable(float * val, string name,bool _allowChange= true){
		valueFloat = val;
		type = SHARED_FLOAT;
		allowChange = _allowChange;
		id = name;
	}
	SharedVariable(string * val, string name, bool _allowChange= true){
		valueString= val;
		type = SHARED_STRING;
		allowChange = _allowChange;
		id = name;
	}
	SharedVariable(bool * val, string name,bool _allowChange= true){
		valueBool= val;
		type = SHARED_BOOL;
		allowChange = _allowChange;
		id = name;
	//	cout<<"Created bool "<<name<<" "<<*val<<endl;
	}
	
	void update(ofxOscSender * sender, string toolName){
	//	cout<<toolName<<endl;
		switch (type) {
			case SHARED_BOOL:
				if(oldBool != *valueBool){
					ofxOscMessage m;
					m.setAddress( ("/"+toolName+"/"+id).c_str());
					m.addIntArg(*valueBool);
					sender->sendMessage( m );
			//		cout<<"shared variable send osc "<< m.getAddress()<<endl;
				}
				oldBool = *valueBool;
				break;
			case SHARED_FLOAT:
				if(oldFloat != *valueFloat){
					ofxOscMessage m;
					m.setAddress( ("/"+toolName+"/"+id).c_str());
					m.addFloatArg(*valueFloat);
					sender->sendMessage( m );
				}
				oldFloat = *valueFloat;
				break;				
			case SHARED_STRING:
				if(oldString != *valueString){
					ofxOscMessage m;
					m.setAddress( ("/"+toolName+"/"+id).c_str());
					m.addStringArg((*valueString).c_str());
					sender->sendMessage( m );
				}
				oldString = *valueString;
				break;
			case SHARED_INT:
				if(oldInt != *valueInt){
					ofxOscMessage m;
					m.setAddress( ("/"+toolName+"/"+id).c_str());
					m.addIntArg(*valueBool);
					sender->sendMessage( m );
				}
				oldInt = *valueInt;
				break;
			default:
				break;
		}

	}
	
	void handleOsc(ofxOscMessage *m, string toolName){					   
		if ( strcmp( m->getAddress(), ("/"+toolName+"/"+id).c_str() ) == 0 ){
		//	cout<<"shared variable recieved osc "<< m->getAddress()<<endl;
			if(type == SHARED_BOOL){
				*valueBool = m->getArgAsInt32(0);
				oldBool = m->getArgAsInt32(0);
			} else if(type == SHARED_INT){
				*valueInt = m->getArgAsInt32(0);
				oldInt = m->getArgAsInt32(0);
			} else if(type == SHARED_STRING){
				*valueString = m->getArgAsString(0);
				oldString = m->getArgAsString(0);
			} else if(type == SHARED_FLOAT){
				*valueFloat = m->getArgAsFloat(0);
				oldFloat = m->getArgAsFloat(0);
			}
		}
	}
	
};

#endif