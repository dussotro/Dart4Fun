#ifndef STUBS_H__INCLUDED
#define STUBS_H__INCLUDED

#include <v_repLib.h>
#include <string>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <boost/lexical_cast.hpp>

struct exception : public std::exception
{
    std::string s;
    exception(std::string s_) : s(s_) {}
    ~exception() throw() {}
    const char* what() const throw() {return s.c_str();}
};

simInt simRegisterScriptCallbackFunctionE(const simChar *funcNameAtPluginName, const simChar *callTips, simVoid (*callBack)(struct SScriptCallBack *cb));
simInt simRegisterScriptVariableE(const simChar *varName, const simChar *varValue, simInt stackID);
simVoid simCallScriptFunctionExE(simInt scriptHandleOrType,const simChar* functionNameAtScriptName,simInt stackId);
simInt simCreateStackE();
simVoid simReleaseStackE(simInt stackHandle);
simInt simCopyStackE(simInt stackHandle);
simVoid simPushNullOntoStackE(simInt stackHandle);
simVoid simPushBoolOntoStackE(simInt stackHandle, simBool value);
simVoid simPushInt32OntoStackE(simInt stackHandle, simInt value);
simVoid simPushFloatOntoStackE(simInt stackHandle, simFloat value);
simVoid simPushDoubleOntoStackE(simInt stackHandle, simDouble value);
simVoid simPushStringOntoStackE(simInt stackHandle, const simChar *value, simInt stringSize);
simVoid simPushUInt8TableOntoStackE(simInt stackHandle, const simUChar *values, simInt valueCnt);
simVoid simPushInt32TableOntoStackE(simInt stackHandle, const simInt *values, simInt valueCnt);
simVoid simPushFloatTableOntoStackE(simInt stackHandle, const simFloat *values, simInt valueCnt);
simVoid simPushDoubleTableOntoStackE(simInt stackHandle, const simDouble *values, simInt valueCnt);
simVoid simPushTableOntoStackE(simInt stackHandle);
simVoid simInsertDataIntoStackTableE(simInt stackHandle);
simInt simGetStackSizeE(simInt stackHandle);
simInt simPopStackItemE(simInt stackHandle, simInt count);
simVoid simMoveStackItemToTopE(simInt stackHandle, simInt cIndex);
simInt simIsStackValueNullE(simInt stackHandle);
simInt simGetStackBoolValueE(simInt stackHandle, simBool *boolValue);
simInt simGetStackInt32ValueE(simInt stackHandle, simInt *numberValue);
simInt simGetStackFloatValueE(simInt stackHandle, simFloat *numberValue);
simInt simGetStackDoubleValueE(simInt stackHandle, simDouble *numberValue);
simChar* simGetStackStringValueE(simInt stackHandle, simInt *stringSize);
simInt simGetStackTableInfoE(simInt stackHandle, simInt infoType);
simInt simGetStackUInt8TableE(simInt stackHandle, simUChar *array, simInt count);
simInt simGetStackInt32TableE(simInt stackHandle, simInt *array, simInt count);
simInt simGetStackFloatTableE(simInt stackHandle, simFloat *array, simInt count);
simInt simGetStackDoubleTableE(simInt stackHandle, simDouble *array, simInt count);
simVoid simUnfoldStackTableE(simInt stackHandle);
simInt simGetInt32ParameterE(simInt parameter);
simChar* simCreateBufferE(simInt size);
simVoid simReleaseBufferE(simChar *buffer);


void read__bool(int stack, bool *value);
void read__int(int stack, int *value);
void read__float(int stack, float *value);
void read__std__string(int stack, std::string *value);
void write__bool(bool value, int stack);
void write__int(int value, int stack);
void write__float(float value, int stack);
void write__std__string(std::string value, int stack);

bool registerScriptStuff();

enum Test
{
    sim_customui_test_a = 39457,
    sim_customui_test_b,
    sim_customui_test_c,
};

const char* test_string(Test x);

struct create_in
{
    std::string xml;
    create_in();
};

struct create_out
{
    int uiHandle;
    create_out();
};

void create(SScriptCallBack *p, create_in *in, create_out *out);
int create(SScriptCallBack *p, std::string xml);
void create(SScriptCallBack *p, create_out *out, std::string xml);
void create_callback(SScriptCallBack *p);

struct destroy_in
{
    int handle;
    destroy_in();
};

struct destroy_out
{
    destroy_out();
};

void destroy(SScriptCallBack *p, destroy_in *in, destroy_out *out);
void destroy(SScriptCallBack *p, int handle);
void destroy(SScriptCallBack *p, destroy_out *out, int handle);
void destroy_callback(SScriptCallBack *p);

struct getSliderValue_in
{
    int handle;
    int id;
    getSliderValue_in();
};

struct getSliderValue_out
{
    int value;
    getSliderValue_out();
};

void getSliderValue(SScriptCallBack *p, getSliderValue_in *in, getSliderValue_out *out);
int getSliderValue(SScriptCallBack *p, int handle, int id);
void getSliderValue(SScriptCallBack *p, getSliderValue_out *out, int handle, int id);
void getSliderValue_callback(SScriptCallBack *p);

struct setSliderValue_in
{
    int handle;
    int id;
    int value;
    bool suppressEvents;
    setSliderValue_in();
};

struct setSliderValue_out
{
    setSliderValue_out();
};

void setSliderValue(SScriptCallBack *p, setSliderValue_in *in, setSliderValue_out *out);
void setSliderValue(SScriptCallBack *p, int handle, int id, int value, bool suppressEvents = false);
void setSliderValue(SScriptCallBack *p, setSliderValue_out *out, int handle, int id, int value, bool suppressEvents = false);
void setSliderValue_callback(SScriptCallBack *p);

struct getEditValue_in
{
    int handle;
    int id;
    getEditValue_in();
};

struct getEditValue_out
{
    std::string value;
    getEditValue_out();
};

void getEditValue(SScriptCallBack *p, getEditValue_in *in, getEditValue_out *out);
std::string getEditValue(SScriptCallBack *p, int handle, int id);
void getEditValue(SScriptCallBack *p, getEditValue_out *out, int handle, int id);
void getEditValue_callback(SScriptCallBack *p);

struct setEditValue_in
{
    int handle;
    int id;
    std::string value;
    bool suppressEvents;
    setEditValue_in();
};

struct setEditValue_out
{
    setEditValue_out();
};

void setEditValue(SScriptCallBack *p, setEditValue_in *in, setEditValue_out *out);
void setEditValue(SScriptCallBack *p, int handle, int id, std::string value, bool suppressEvents = false);
void setEditValue(SScriptCallBack *p, setEditValue_out *out, int handle, int id, std::string value, bool suppressEvents = false);
void setEditValue_callback(SScriptCallBack *p);

struct getSpinboxValue_in
{
    int handle;
    int id;
    getSpinboxValue_in();
};

struct getSpinboxValue_out
{
    float value;
    getSpinboxValue_out();
};

void getSpinboxValue(SScriptCallBack *p, getSpinboxValue_in *in, getSpinboxValue_out *out);
float getSpinboxValue(SScriptCallBack *p, int handle, int id);
void getSpinboxValue(SScriptCallBack *p, getSpinboxValue_out *out, int handle, int id);
void getSpinboxValue_callback(SScriptCallBack *p);

struct setSpinboxValue_in
{
    int handle;
    int id;
    float value;
    bool suppressEvents;
    setSpinboxValue_in();
};

struct setSpinboxValue_out
{
    setSpinboxValue_out();
};

void setSpinboxValue(SScriptCallBack *p, setSpinboxValue_in *in, setSpinboxValue_out *out);
void setSpinboxValue(SScriptCallBack *p, int handle, int id, float value, bool suppressEvents = false);
void setSpinboxValue(SScriptCallBack *p, setSpinboxValue_out *out, int handle, int id, float value, bool suppressEvents = false);
void setSpinboxValue_callback(SScriptCallBack *p);

struct getCheckboxValue_in
{
    int handle;
    int id;
    getCheckboxValue_in();
};

struct getCheckboxValue_out
{
    int value;
    getCheckboxValue_out();
};

void getCheckboxValue(SScriptCallBack *p, getCheckboxValue_in *in, getCheckboxValue_out *out);
int getCheckboxValue(SScriptCallBack *p, int handle, int id);
void getCheckboxValue(SScriptCallBack *p, getCheckboxValue_out *out, int handle, int id);
void getCheckboxValue_callback(SScriptCallBack *p);

struct setCheckboxValue_in
{
    int handle;
    int id;
    int value;
    bool suppressEvents;
    setCheckboxValue_in();
};

struct setCheckboxValue_out
{
    setCheckboxValue_out();
};

void setCheckboxValue(SScriptCallBack *p, setCheckboxValue_in *in, setCheckboxValue_out *out);
void setCheckboxValue(SScriptCallBack *p, int handle, int id, int value, bool suppressEvents = false);
void setCheckboxValue(SScriptCallBack *p, setCheckboxValue_out *out, int handle, int id, int value, bool suppressEvents = false);
void setCheckboxValue_callback(SScriptCallBack *p);

struct getRadiobuttonValue_in
{
    int handle;
    int id;
    getRadiobuttonValue_in();
};

struct getRadiobuttonValue_out
{
    int value;
    getRadiobuttonValue_out();
};

void getRadiobuttonValue(SScriptCallBack *p, getRadiobuttonValue_in *in, getRadiobuttonValue_out *out);
int getRadiobuttonValue(SScriptCallBack *p, int handle, int id);
void getRadiobuttonValue(SScriptCallBack *p, getRadiobuttonValue_out *out, int handle, int id);
void getRadiobuttonValue_callback(SScriptCallBack *p);

struct setRadiobuttonValue_in
{
    int handle;
    int id;
    int value;
    bool suppressEvents;
    setRadiobuttonValue_in();
};

struct setRadiobuttonValue_out
{
    setRadiobuttonValue_out();
};

void setRadiobuttonValue(SScriptCallBack *p, setRadiobuttonValue_in *in, setRadiobuttonValue_out *out);
void setRadiobuttonValue(SScriptCallBack *p, int handle, int id, int value, bool suppressEvents = false);
void setRadiobuttonValue(SScriptCallBack *p, setRadiobuttonValue_out *out, int handle, int id, int value, bool suppressEvents = false);
void setRadiobuttonValue_callback(SScriptCallBack *p);

struct getLabelText_in
{
    int handle;
    int id;
    getLabelText_in();
};

struct getLabelText_out
{
    std::string text;
    getLabelText_out();
};

void getLabelText(SScriptCallBack *p, getLabelText_in *in, getLabelText_out *out);
std::string getLabelText(SScriptCallBack *p, int handle, int id);
void getLabelText(SScriptCallBack *p, getLabelText_out *out, int handle, int id);
void getLabelText_callback(SScriptCallBack *p);

struct setLabelText_in
{
    int handle;
    int id;
    std::string text;
    bool suppressEvents;
    setLabelText_in();
};

struct setLabelText_out
{
    setLabelText_out();
};

void setLabelText(SScriptCallBack *p, setLabelText_in *in, setLabelText_out *out);
void setLabelText(SScriptCallBack *p, int handle, int id, std::string text, bool suppressEvents = false);
void setLabelText(SScriptCallBack *p, setLabelText_out *out, int handle, int id, std::string text, bool suppressEvents = false);
void setLabelText_callback(SScriptCallBack *p);

struct insertComboboxItem_in
{
    int handle;
    int id;
    int index;
    std::string text;
    bool suppressEvents;
    insertComboboxItem_in();
};

struct insertComboboxItem_out
{
    insertComboboxItem_out();
};

void insertComboboxItem(SScriptCallBack *p, insertComboboxItem_in *in, insertComboboxItem_out *out);
void insertComboboxItem(SScriptCallBack *p, int handle, int id, int index, std::string text, bool suppressEvents = false);
void insertComboboxItem(SScriptCallBack *p, insertComboboxItem_out *out, int handle, int id, int index, std::string text, bool suppressEvents = false);
void insertComboboxItem_callback(SScriptCallBack *p);

struct removeComboboxItem_in
{
    int handle;
    int id;
    int index;
    bool suppressEvents;
    removeComboboxItem_in();
};

struct removeComboboxItem_out
{
    removeComboboxItem_out();
};

void removeComboboxItem(SScriptCallBack *p, removeComboboxItem_in *in, removeComboboxItem_out *out);
void removeComboboxItem(SScriptCallBack *p, int handle, int id, int index, bool suppressEvents = false);
void removeComboboxItem(SScriptCallBack *p, removeComboboxItem_out *out, int handle, int id, int index, bool suppressEvents = false);
void removeComboboxItem_callback(SScriptCallBack *p);

struct getComboboxItemCount_in
{
    int handle;
    int id;
    getComboboxItemCount_in();
};

struct getComboboxItemCount_out
{
    int count;
    getComboboxItemCount_out();
};

void getComboboxItemCount(SScriptCallBack *p, getComboboxItemCount_in *in, getComboboxItemCount_out *out);
int getComboboxItemCount(SScriptCallBack *p, int handle, int id);
void getComboboxItemCount(SScriptCallBack *p, getComboboxItemCount_out *out, int handle, int id);
void getComboboxItemCount_callback(SScriptCallBack *p);

struct getComboboxItemText_in
{
    int handle;
    int id;
    int index;
    getComboboxItemText_in();
};

struct getComboboxItemText_out
{
    std::string text;
    getComboboxItemText_out();
};

void getComboboxItemText(SScriptCallBack *p, getComboboxItemText_in *in, getComboboxItemText_out *out);
std::string getComboboxItemText(SScriptCallBack *p, int handle, int id, int index);
void getComboboxItemText(SScriptCallBack *p, getComboboxItemText_out *out, int handle, int id, int index);
void getComboboxItemText_callback(SScriptCallBack *p);

struct hide_in
{
    int handle;
    hide_in();
};

struct hide_out
{
    hide_out();
};

void hide(SScriptCallBack *p, hide_in *in, hide_out *out);
void hide(SScriptCallBack *p, int handle);
void hide(SScriptCallBack *p, hide_out *out, int handle);
void hide_callback(SScriptCallBack *p);

struct show_in
{
    int handle;
    show_in();
};

struct show_out
{
    show_out();
};

void show(SScriptCallBack *p, show_in *in, show_out *out);
void show(SScriptCallBack *p, int handle);
void show(SScriptCallBack *p, show_out *out, int handle);
void show_callback(SScriptCallBack *p);

struct isVisible_in
{
    int handle;
    isVisible_in();
};

struct isVisible_out
{
    bool visibility;
    isVisible_out();
};

void isVisible(SScriptCallBack *p, isVisible_in *in, isVisible_out *out);
bool isVisible(SScriptCallBack *p, int handle);
void isVisible(SScriptCallBack *p, isVisible_out *out, int handle);
void isVisible_callback(SScriptCallBack *p);

struct getPosition_in
{
    int handle;
    getPosition_in();
};

struct getPosition_out
{
    int x;
    int y;
    getPosition_out();
};

void getPosition(SScriptCallBack *p, getPosition_in *in, getPosition_out *out);
void getPosition(SScriptCallBack *p, getPosition_out *out, int handle);
void getPosition_callback(SScriptCallBack *p);

struct setPosition_in
{
    int handle;
    int x;
    int y;
    bool suppressEvents;
    setPosition_in();
};

struct setPosition_out
{
    setPosition_out();
};

void setPosition(SScriptCallBack *p, setPosition_in *in, setPosition_out *out);
void setPosition(SScriptCallBack *p, int handle, int x, int y, bool suppressEvents = false);
void setPosition(SScriptCallBack *p, setPosition_out *out, int handle, int x, int y, bool suppressEvents = false);
void setPosition_callback(SScriptCallBack *p);

struct setImageData_in
{
    int handle;
    int id;
    std::string data;
    int width;
    int height;
    setImageData_in();
};

struct setImageData_out
{
    setImageData_out();
};

void setImageData(SScriptCallBack *p, setImageData_in *in, setImageData_out *out);
void setImageData(SScriptCallBack *p, int handle, int id, std::string data, int width, int height);
void setImageData(SScriptCallBack *p, setImageData_out *out, int handle, int id, std::string data, int width, int height);
void setImageData_callback(SScriptCallBack *p);

struct setEnabled_in
{
    int handle;
    int id;
    bool enabled;
    bool suppressEvents;
    setEnabled_in();
};

struct setEnabled_out
{
    setEnabled_out();
};

void setEnabled(SScriptCallBack *p, setEnabled_in *in, setEnabled_out *out);
void setEnabled(SScriptCallBack *p, int handle, int id, bool enabled, bool suppressEvents = false);
void setEnabled(SScriptCallBack *p, setEnabled_out *out, int handle, int id, bool enabled, bool suppressEvents = false);
void setEnabled_callback(SScriptCallBack *p);

struct onclickCallback_in
{
    int handle;
    int id;
    onclickCallback_in();
};

struct onclickCallback_out
{
    onclickCallback_out();
};

bool onclickCallback(simInt scriptId, const char *func, onclickCallback_in *in_args, onclickCallback_out *out_args);

struct onchangeIntCallback_in
{
    int handle;
    int id;
    int value;
    onchangeIntCallback_in();
};

struct onchangeIntCallback_out
{
    onchangeIntCallback_out();
};

bool onchangeIntCallback(simInt scriptId, const char *func, onchangeIntCallback_in *in_args, onchangeIntCallback_out *out_args);

struct onchangeDoubleCallback_in
{
    int handle;
    int id;
    float value;
    onchangeDoubleCallback_in();
};

struct onchangeDoubleCallback_out
{
    onchangeDoubleCallback_out();
};

bool onchangeDoubleCallback(simInt scriptId, const char *func, onchangeDoubleCallback_in *in_args, onchangeDoubleCallback_out *out_args);

struct onchangeStringCallback_in
{
    int handle;
    int id;
    std::string value;
    onchangeStringCallback_in();
};

struct onchangeStringCallback_out
{
    onchangeStringCallback_out();
};

bool onchangeStringCallback(simInt scriptId, const char *func, onchangeStringCallback_in *in_args, onchangeStringCallback_out *out_args);

struct oneditingfinishedCallback_in
{
    int handle;
    int id;
    std::string value;
    oneditingfinishedCallback_in();
};

struct oneditingfinishedCallback_out
{
    oneditingfinishedCallback_out();
};

bool oneditingfinishedCallback(simInt scriptId, const char *func, oneditingfinishedCallback_in *in_args, oneditingfinishedCallback_out *out_args);

struct oncloseCallback_in
{
    int handle;
    oncloseCallback_in();
};

struct oncloseCallback_out
{
    oncloseCallback_out();
};

bool oncloseCallback(simInt scriptId, const char *func, oncloseCallback_in *in_args, oncloseCallback_out *out_args);


// following functions must be implemented in the plugin

void create(SScriptCallBack *p, const char *cmd, create_in *in, create_out *out);
void destroy(SScriptCallBack *p, const char *cmd, destroy_in *in, destroy_out *out);
void getSliderValue(SScriptCallBack *p, const char *cmd, getSliderValue_in *in, getSliderValue_out *out);
void setSliderValue(SScriptCallBack *p, const char *cmd, setSliderValue_in *in, setSliderValue_out *out);
void getEditValue(SScriptCallBack *p, const char *cmd, getEditValue_in *in, getEditValue_out *out);
void setEditValue(SScriptCallBack *p, const char *cmd, setEditValue_in *in, setEditValue_out *out);
void getSpinboxValue(SScriptCallBack *p, const char *cmd, getSpinboxValue_in *in, getSpinboxValue_out *out);
void setSpinboxValue(SScriptCallBack *p, const char *cmd, setSpinboxValue_in *in, setSpinboxValue_out *out);
void getCheckboxValue(SScriptCallBack *p, const char *cmd, getCheckboxValue_in *in, getCheckboxValue_out *out);
void setCheckboxValue(SScriptCallBack *p, const char *cmd, setCheckboxValue_in *in, setCheckboxValue_out *out);
void getRadiobuttonValue(SScriptCallBack *p, const char *cmd, getRadiobuttonValue_in *in, getRadiobuttonValue_out *out);
void setRadiobuttonValue(SScriptCallBack *p, const char *cmd, setRadiobuttonValue_in *in, setRadiobuttonValue_out *out);
void getLabelText(SScriptCallBack *p, const char *cmd, getLabelText_in *in, getLabelText_out *out);
void setLabelText(SScriptCallBack *p, const char *cmd, setLabelText_in *in, setLabelText_out *out);
void insertComboboxItem(SScriptCallBack *p, const char *cmd, insertComboboxItem_in *in, insertComboboxItem_out *out);
void removeComboboxItem(SScriptCallBack *p, const char *cmd, removeComboboxItem_in *in, removeComboboxItem_out *out);
void getComboboxItemCount(SScriptCallBack *p, const char *cmd, getComboboxItemCount_in *in, getComboboxItemCount_out *out);
void getComboboxItemText(SScriptCallBack *p, const char *cmd, getComboboxItemText_in *in, getComboboxItemText_out *out);
void hide(SScriptCallBack *p, const char *cmd, hide_in *in, hide_out *out);
void show(SScriptCallBack *p, const char *cmd, show_in *in, show_out *out);
void isVisible(SScriptCallBack *p, const char *cmd, isVisible_in *in, isVisible_out *out);
void getPosition(SScriptCallBack *p, const char *cmd, getPosition_in *in, getPosition_out *out);
void setPosition(SScriptCallBack *p, const char *cmd, setPosition_in *in, setPosition_out *out);
void setImageData(SScriptCallBack *p, const char *cmd, setImageData_in *in, setImageData_out *out);
void setEnabled(SScriptCallBack *p, const char *cmd, setEnabled_in *in, setEnabled_out *out);

#endif // STUBS_H__INCLUDED
