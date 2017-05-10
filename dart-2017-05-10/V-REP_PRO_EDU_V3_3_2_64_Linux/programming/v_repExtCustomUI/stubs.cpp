#include "stubs.h"

#include <iostream>

simInt simRegisterScriptCallbackFunctionE(const simChar *funcNameAtPluginName, const simChar *callTips, simVoid (*callBack)(struct SScriptCallBack *cb))
{
    simInt ret = simRegisterScriptCallbackFunction(funcNameAtPluginName, callTips, callBack);
    if(ret == 0)
    {
        std::cout << "Plugin 'CustomUI': warning: replaced function '" << funcNameAtPluginName << "'" << std::endl;
    }
    if(ret == -1)
        throw exception("simRegisterScriptCallbackFunction: error");
    return ret;
}

simInt simRegisterScriptVariableE(const simChar *varName, const simChar *varValue, simInt stackID)
{
    simInt ret = simRegisterScriptVariable(varName, varValue, stackID);
    if(ret == 0)
    {
        std::cout << "Plugin 'CustomUI': warning: replaced variable '" << varName << "'" << std::endl;
    }
    if(ret == -1)
        throw exception("simRegisterScriptVariable: error");
    return ret;
}

simVoid simCallScriptFunctionExE(simInt scriptHandleOrType,const simChar* functionNameAtScriptName,simInt stackId)
{
    if(simCallScriptFunctionEx(scriptHandleOrType, functionNameAtScriptName, stackId) == -1)
        throw exception("simCallScriptFunctionEx: error");
}

simInt simCreateStackE()
{
    simInt ret = simCreateStack();
    if(ret == -1)
        throw exception("simCreateStack: error");
    return ret;
}

simVoid simReleaseStackE(simInt stackHandle)
{
    if(simReleaseStack(stackHandle) != 1)
        throw exception("simReleaseStack: error");
}

simInt simCopyStackE(simInt stackHandle)
{
    simInt ret = simCopyStack(stackHandle);
    if(ret == -1)
        throw exception("simCopyStack: error");
    return ret;
}

simVoid simPushNullOntoStackE(simInt stackHandle)
{
    if(simPushNullOntoStack(stackHandle) == -1)
        throw exception("simPushNullOntoStack: error");
}

simVoid simPushBoolOntoStackE(simInt stackHandle, simBool value)
{
    if(simPushBoolOntoStack(stackHandle, value) == -1)
        throw exception("simPushBoolOntoStack: error");
}

simVoid simPushInt32OntoStackE(simInt stackHandle, simInt value)
{
    if(simPushInt32OntoStack(stackHandle, value) == -1)
        throw exception("simPushInt32OntoStack: error");
}

simVoid simPushFloatOntoStackE(simInt stackHandle, simFloat value)
{
    if(simPushFloatOntoStack(stackHandle, value) == -1)
        throw exception("simPushFloatOntoStack: error");
}

simVoid simPushDoubleOntoStackE(simInt stackHandle, simDouble value)
{
    if(simPushDoubleOntoStack(stackHandle, value) == -1)
        throw exception("simPushDoubleOntoStack: error");
}

simVoid simPushStringOntoStackE(simInt stackHandle, const simChar *value, simInt stringSize)
{
    if(simPushStringOntoStack(stackHandle, value, stringSize) == -1)
        throw exception("simPushStringOntoStack: error");
}

simVoid simPushUInt8TableOntoStackE(simInt stackHandle, const simUChar *values, simInt valueCnt)
{
    if(simPushUInt8TableOntoStack(stackHandle, values, valueCnt) == -1)
        throw exception("simPushUInt8TableOntoStack: error");
}

simVoid simPushInt32TableOntoStackE(simInt stackHandle, const simInt *values, simInt valueCnt)
{
    if(simPushInt32TableOntoStack(stackHandle, values, valueCnt) == -1)
        throw exception("simPushInt32TableOntoStack: error");
}

simVoid simPushFloatTableOntoStackE(simInt stackHandle, const simFloat *values, simInt valueCnt)
{
    if(simPushFloatTableOntoStack(stackHandle, values, valueCnt) == -1)
        throw exception("simPushFloatTableOntoStack: error");
}

simVoid simPushDoubleTableOntoStackE(simInt stackHandle, const simDouble *values, simInt valueCnt)
{
    if(simPushDoubleTableOntoStack(stackHandle, values, valueCnt) == -1)
        throw exception("simPushDoubleTableOntoStack: error");
}

simVoid simPushTableOntoStackE(simInt stackHandle)
{
    if(simPushTableOntoStack(stackHandle) == -1)
        throw exception("simPushTableOntoStack: error");
}

simVoid simInsertDataIntoStackTableE(simInt stackHandle)
{
    if(simInsertDataIntoStackTable(stackHandle) == -1)
        throw exception("simInsertDataIntoStackTable: error");
}

simInt simGetStackSizeE(simInt stackHandle)
{
    simInt ret = simGetStackSize(stackHandle);
    if(ret == -1)
        throw exception("simGetStackSize: error");
    return ret;
}    

simInt simPopStackItemE(simInt stackHandle, simInt count)
{
    simInt ret = simPopStackItem(stackHandle, count);
    if(ret == -1)
        throw exception("simPopStackItem: error");
    return ret;
}    

simVoid simMoveStackItemToTopE(simInt stackHandle, simInt cIndex)
{
    if(simMoveStackItemToTop(stackHandle, cIndex) == -1)
        throw exception("simMoveStackItemToTop: error");
}

simInt simIsStackValueNullE(simInt stackHandle)
{
    simInt ret = simIsStackValueNull(stackHandle);
    if(ret == -1)
        throw exception("simIsStackValueNull: error");
    return ret;
}

simInt simGetStackBoolValueE(simInt stackHandle, simBool *boolValue)
{
    simInt ret = simGetStackBoolValue(stackHandle, boolValue);
    if(ret == -1)
        throw exception("simGetStackBoolValue: error");
    return ret;
}

simInt simGetStackInt32ValueE(simInt stackHandle, simInt *numberValue)
{
    simInt ret = simGetStackInt32Value(stackHandle, numberValue);
    if(ret == -1)
        throw exception("simGetStackInt32Value: error");
    return ret;
}

simInt simGetStackFloatValueE(simInt stackHandle, simFloat *numberValue)
{
    simInt ret = simGetStackFloatValue(stackHandle, numberValue);
    if(ret == -1)
        throw exception("simGetStackFloatValue: error");
    return ret;
}

simInt simGetStackDoubleValueE(simInt stackHandle, simDouble *numberValue)
{
    simInt ret = simGetStackDoubleValue(stackHandle, numberValue);
    if(ret == -1)
        throw exception("simGetStackDoubleValue: error");
    return ret;
}

simChar* simGetStackStringValueE(simInt stackHandle, simInt *stringSize)
{
    simChar *ret = simGetStackStringValue(stackHandle, stringSize);
    // if stringSize is NULL, we cannot distinguish error (-1) from type error (0)
    if(ret == NULL && stringSize && *stringSize == -1)
        throw exception("simGetStackStringValue: error");
    return ret;
}

simInt simGetStackTableInfoE(simInt stackHandle, simInt infoType)
{
    simInt ret = simGetStackTableInfo(stackHandle, infoType);
    if(ret == -1)
        throw exception("simGetStackTableInfo: error");
    return ret;
}

simInt simGetStackUInt8TableE(simInt stackHandle, simUChar *array, simInt count)
{
    simInt ret = simGetStackUInt8Table(stackHandle, array, count);
    if(ret == -1)
        throw exception("simGetStackUInt8Table: error");
    return ret;
}

simInt simGetStackInt32TableE(simInt stackHandle, simInt *array, simInt count)
{
    simInt ret = simGetStackInt32Table(stackHandle, array, count);
    if(ret == -1)
        throw exception("simGetStackInt32Table: error");
    return ret;
}

simInt simGetStackFloatTableE(simInt stackHandle, simFloat *array, simInt count)
{
    simInt ret = simGetStackFloatTable(stackHandle, array, count);
    if(ret == -1)
        throw exception("simGetStackFloatTable: error");
    return ret;
}

simInt simGetStackDoubleTableE(simInt stackHandle, simDouble *array, simInt count)
{
    simInt ret = simGetStackDoubleTable(stackHandle, array, count);
    if(ret == -1)
        throw exception("simGetStackDoubleTable: error");
    return ret;
}

simVoid simUnfoldStackTableE(simInt stackHandle)
{
    if(simUnfoldStackTable(stackHandle) == -1)
        throw exception("simUnfoldStackTable: error");
}

simInt simGetInt32ParameterE(simInt parameter)
{
    simInt ret;
    if(simGetInt32Parameter(parameter, &ret) == -1)
        throw exception("simGetInt32Parameter: error");
    return ret;
}

simChar* simCreateBufferE(simInt size)
{
    simChar *ret = simCreateBuffer(size);
    if(ret == NULL)
        throw exception("simCreateBuffer: error");
    return ret;
}

simVoid simReleaseBufferE(simChar *buffer)
{
    if(simReleaseBuffer(buffer) == -1)
        throw exception("simReleaseBuffer: error");
}

void read__bool(int stack, bool *value)
{
    simBool v;
    if(simGetStackBoolValueE(stack, &v) == 1)
    {
        *value = v;
        simPopStackItemE(stack, 1);
    }
    else
    {
        throw exception("expected bool");
    }
}

void read__int(int stack, int *value)
{
    int v;
    if(simGetStackInt32ValueE(stack, &v) == 1)
    {
        *value = v;
        simPopStackItemE(stack, 1);
    }
    else
    {
        throw exception("expected int");
    }
}

void read__float(int stack, float *value)
{
    simFloat v;
    if(simGetStackFloatValueE(stack, &v) == 1)
    {
        *value = v;
        simPopStackItemE(stack, 1);
    }
    else
    {
        throw exception("expected float");
    }
}

void read__std__string(int stack, std::string *value)
{
    simChar *str;
    simInt strSize;
    if((str = simGetStackStringValueE(stack, &strSize)) != NULL && strSize >= 0)
    {
        *value = std::string(str, strSize);
        simPopStackItemE(stack, 1);
        simReleaseBufferE(str);
    }
    else
    {
        throw exception("expected string");
    }
}

void write__bool(bool value, int stack)
{
    simBool v = value;
    simPushBoolOntoStackE(stack, v);
}

void write__int(int value, int stack)
{
    simInt v = value;
    simPushInt32OntoStackE(stack, v);
}

void write__float(float value, int stack)
{
    simFloat v = value;
    simPushFloatOntoStackE(stack, v);
}

void write__std__string(std::string value, int stack)
{
    const simChar *v = value.c_str();
    simPushStringOntoStackE(stack, v, value.length());
}

bool registerScriptStuff()
{
    try
    {
        simRegisterScriptVariableE("sim_customui_test_a", (boost::lexical_cast<std::string>(sim_customui_test_a)).c_str(), 0);
        simRegisterScriptVariableE("sim_customui_test_b", (boost::lexical_cast<std::string>(sim_customui_test_b)).c_str(), 0);
        simRegisterScriptVariableE("sim_customui_test_c", (boost::lexical_cast<std::string>(sim_customui_test_c)).c_str(), 0);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_create@CustomUI", "number uiHandle=simExtCustomUI_create(string xml)", create_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_destroy@CustomUI", "simExtCustomUI_destroy(number handle)", destroy_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getSliderValue@CustomUI", "number value=simExtCustomUI_getSliderValue(number handle,number id)", getSliderValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setSliderValue@CustomUI", "simExtCustomUI_setSliderValue(number handle,number id,number value,bool suppressEvents=false)", setSliderValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getEditValue@CustomUI", "string value=simExtCustomUI_getEditValue(number handle,number id)", getEditValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setEditValue@CustomUI", "simExtCustomUI_setEditValue(number handle,number id,string value,bool suppressEvents=false)", setEditValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getSpinboxValue@CustomUI", "number value=simExtCustomUI_getSpinboxValue(number handle,number id)", getSpinboxValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setSpinboxValue@CustomUI", "simExtCustomUI_setSpinboxValue(number handle,number id,number value,bool suppressEvents=false)", setSpinboxValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getCheckboxValue@CustomUI", "number value=simExtCustomUI_getCheckboxValue(number handle,number id)", getCheckboxValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setCheckboxValue@CustomUI", "simExtCustomUI_setCheckboxValue(number handle,number id,number value,bool suppressEvents=false)", setCheckboxValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getRadiobuttonValue@CustomUI", "number value=simExtCustomUI_getRadiobuttonValue(number handle,number id)", getRadiobuttonValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setRadiobuttonValue@CustomUI", "simExtCustomUI_setRadiobuttonValue(number handle,number id,number value,bool suppressEvents=false)", setRadiobuttonValue_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getLabelText@CustomUI", "string text=simExtCustomUI_getLabelText(number handle,number id)", getLabelText_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setLabelText@CustomUI", "simExtCustomUI_setLabelText(number handle,number id,string text,bool suppressEvents=false)", setLabelText_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_insertComboboxItem@CustomUI", "simExtCustomUI_insertComboboxItem(number handle,number id,number index,string text,bool suppressEvents=false)", insertComboboxItem_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_removeComboboxItem@CustomUI", "simExtCustomUI_removeComboboxItem(number handle,number id,number index,bool suppressEvents=false)", removeComboboxItem_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getComboboxItemCount@CustomUI", "number count=simExtCustomUI_getComboboxItemCount(number handle,number id)", getComboboxItemCount_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getComboboxItemText@CustomUI", "string text=simExtCustomUI_getComboboxItemText(number handle,number id,number index)", getComboboxItemText_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_hide@CustomUI", "simExtCustomUI_hide(number handle)", hide_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_show@CustomUI", "simExtCustomUI_show(number handle)", show_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_isVisible@CustomUI", "bool visibility=simExtCustomUI_isVisible(number handle)", isVisible_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_getPosition@CustomUI", "number x,number y=simExtCustomUI_getPosition(number handle)", getPosition_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setPosition@CustomUI", "simExtCustomUI_setPosition(number handle,number x,number y,bool suppressEvents=false)", setPosition_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setImageData@CustomUI", "simExtCustomUI_setImageData(number handle,number id,string data,number width,number height)", setImageData_callback);
        simRegisterScriptCallbackFunctionE("simExtCustomUI_setEnabled@CustomUI", "simExtCustomUI_setEnabled(number handle,number id,bool enabled,bool suppressEvents=false)", setEnabled_callback);
    }
    catch(std::exception& ex)
    {
        std::cout << "Initialization failed (registerScriptStuff): " << ex.what() << std::endl;
        return false;
    }
    catch(std::string& s)
    {
        std::cout << "Initialization failed (registerScriptStuff): " << s << std::endl;
        return false;
    }
    catch(int& n)
    {
        std::cout << "Initialization failed (registerScriptStuff): error #" << n << std::endl;
        return false;
    }
    return true;
}

const char* test_string(Test x)
{
    switch(x)
    {
        case sim_customui_test_a: return "sim_customui_test_a";
        case sim_customui_test_b: return "sim_customui_test_b";
        case sim_customui_test_c: return "sim_customui_test_c";
        default: return "???";
    }
}

create_in::create_in()
{
}

create_out::create_out()
{
    uiHandle = -1;
}

void create(SScriptCallBack *p, create_in *in_args, create_out *out_args)
{
    create(p, "simExtCustomUI_create", in_args, out_args);
}

int create(SScriptCallBack *p, std::string xml)
{
    create_in in_args;
    in_args.xml = xml;
    create_out out_args;
    create(p, &in_args, &out_args);
    return out_args.uiHandle;
}

void create(SScriptCallBack *p, create_out *out_args, std::string xml)
{
    create_in in_args;
    in_args.xml = xml;
    create(p, &in_args, out_args);
}

void create_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_create";

    create_in in_args;
    create_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 1)
            throw exception("too few arguments");
        if(numArgs > 1)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (xml) of type std::string
                simMoveStackItemToTopE(p->stackID, 0);
                read__std__string(p->stackID, &(in_args.xml));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (xml)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (xml))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (xml)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        create(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (uiHandle) of type int
            write__int(out_args.uiHandle, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (uiHandle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (uiHandle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (uiHandle))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

destroy_in::destroy_in()
{
}

destroy_out::destroy_out()
{
}

void destroy(SScriptCallBack *p, destroy_in *in_args, destroy_out *out_args)
{
    destroy(p, "simExtCustomUI_destroy", in_args, out_args);
}

void destroy(SScriptCallBack *p, int handle)
{
    destroy_in in_args;
    in_args.handle = handle;
    destroy_out out_args;
    destroy(p, &in_args, &out_args);
}

void destroy(SScriptCallBack *p, destroy_out *out_args, int handle)
{
    destroy_in in_args;
    in_args.handle = handle;
    destroy(p, &in_args, out_args);
}

void destroy_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_destroy";

    destroy_in in_args;
    destroy_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 1)
            throw exception("too few arguments");
        if(numArgs > 1)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        destroy(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getSliderValue_in::getSliderValue_in()
{
}

getSliderValue_out::getSliderValue_out()
{
}

void getSliderValue(SScriptCallBack *p, getSliderValue_in *in_args, getSliderValue_out *out_args)
{
    getSliderValue(p, "simExtCustomUI_getSliderValue", in_args, out_args);
}

int getSliderValue(SScriptCallBack *p, int handle, int id)
{
    getSliderValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getSliderValue_out out_args;
    getSliderValue(p, &in_args, &out_args);
    return out_args.value;
}

void getSliderValue(SScriptCallBack *p, getSliderValue_out *out_args, int handle, int id)
{
    getSliderValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getSliderValue(p, &in_args, out_args);
}

void getSliderValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getSliderValue";

    getSliderValue_in in_args;
    getSliderValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getSliderValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (value) of type int
            write__int(out_args.value, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (value))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setSliderValue_in::setSliderValue_in()
{
    suppressEvents = false;
}

setSliderValue_out::setSliderValue_out()
{
}

void setSliderValue(SScriptCallBack *p, setSliderValue_in *in_args, setSliderValue_out *out_args)
{
    setSliderValue(p, "simExtCustomUI_setSliderValue", in_args, out_args);
}

void setSliderValue(SScriptCallBack *p, int handle, int id, int value, bool suppressEvents)
{
    setSliderValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setSliderValue_out out_args;
    setSliderValue(p, &in_args, &out_args);
}

void setSliderValue(SScriptCallBack *p, setSliderValue_out *out_args, int handle, int id, int value, bool suppressEvents)
{
    setSliderValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setSliderValue(p, &in_args, out_args);
}

void setSliderValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setSliderValue";

    setSliderValue_in in_args;
    setSliderValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (value) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.value));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (value)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (value))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (value)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setSliderValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getEditValue_in::getEditValue_in()
{
}

getEditValue_out::getEditValue_out()
{
}

void getEditValue(SScriptCallBack *p, getEditValue_in *in_args, getEditValue_out *out_args)
{
    getEditValue(p, "simExtCustomUI_getEditValue", in_args, out_args);
}

std::string getEditValue(SScriptCallBack *p, int handle, int id)
{
    getEditValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getEditValue_out out_args;
    getEditValue(p, &in_args, &out_args);
    return out_args.value;
}

void getEditValue(SScriptCallBack *p, getEditValue_out *out_args, int handle, int id)
{
    getEditValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getEditValue(p, &in_args, out_args);
}

void getEditValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getEditValue";

    getEditValue_in in_args;
    getEditValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getEditValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (value) of type std::string
            write__std__string(out_args.value, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (value))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setEditValue_in::setEditValue_in()
{
    suppressEvents = false;
}

setEditValue_out::setEditValue_out()
{
}

void setEditValue(SScriptCallBack *p, setEditValue_in *in_args, setEditValue_out *out_args)
{
    setEditValue(p, "simExtCustomUI_setEditValue", in_args, out_args);
}

void setEditValue(SScriptCallBack *p, int handle, int id, std::string value, bool suppressEvents)
{
    setEditValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setEditValue_out out_args;
    setEditValue(p, &in_args, &out_args);
}

void setEditValue(SScriptCallBack *p, setEditValue_out *out_args, int handle, int id, std::string value, bool suppressEvents)
{
    setEditValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setEditValue(p, &in_args, out_args);
}

void setEditValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setEditValue";

    setEditValue_in in_args;
    setEditValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (value) of type std::string
                simMoveStackItemToTopE(p->stackID, 0);
                read__std__string(p->stackID, &(in_args.value));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (value)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (value))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (value)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setEditValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getSpinboxValue_in::getSpinboxValue_in()
{
}

getSpinboxValue_out::getSpinboxValue_out()
{
}

void getSpinboxValue(SScriptCallBack *p, getSpinboxValue_in *in_args, getSpinboxValue_out *out_args)
{
    getSpinboxValue(p, "simExtCustomUI_getSpinboxValue", in_args, out_args);
}

float getSpinboxValue(SScriptCallBack *p, int handle, int id)
{
    getSpinboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getSpinboxValue_out out_args;
    getSpinboxValue(p, &in_args, &out_args);
    return out_args.value;
}

void getSpinboxValue(SScriptCallBack *p, getSpinboxValue_out *out_args, int handle, int id)
{
    getSpinboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getSpinboxValue(p, &in_args, out_args);
}

void getSpinboxValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getSpinboxValue";

    getSpinboxValue_in in_args;
    getSpinboxValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getSpinboxValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (value) of type float
            write__float(out_args.value, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (value))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setSpinboxValue_in::setSpinboxValue_in()
{
    suppressEvents = false;
}

setSpinboxValue_out::setSpinboxValue_out()
{
}

void setSpinboxValue(SScriptCallBack *p, setSpinboxValue_in *in_args, setSpinboxValue_out *out_args)
{
    setSpinboxValue(p, "simExtCustomUI_setSpinboxValue", in_args, out_args);
}

void setSpinboxValue(SScriptCallBack *p, int handle, int id, float value, bool suppressEvents)
{
    setSpinboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setSpinboxValue_out out_args;
    setSpinboxValue(p, &in_args, &out_args);
}

void setSpinboxValue(SScriptCallBack *p, setSpinboxValue_out *out_args, int handle, int id, float value, bool suppressEvents)
{
    setSpinboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setSpinboxValue(p, &in_args, out_args);
}

void setSpinboxValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setSpinboxValue";

    setSpinboxValue_in in_args;
    setSpinboxValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (value) of type float
                simMoveStackItemToTopE(p->stackID, 0);
                read__float(p->stackID, &(in_args.value));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (value)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (value))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (value)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setSpinboxValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getCheckboxValue_in::getCheckboxValue_in()
{
}

getCheckboxValue_out::getCheckboxValue_out()
{
}

void getCheckboxValue(SScriptCallBack *p, getCheckboxValue_in *in_args, getCheckboxValue_out *out_args)
{
    getCheckboxValue(p, "simExtCustomUI_getCheckboxValue", in_args, out_args);
}

int getCheckboxValue(SScriptCallBack *p, int handle, int id)
{
    getCheckboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getCheckboxValue_out out_args;
    getCheckboxValue(p, &in_args, &out_args);
    return out_args.value;
}

void getCheckboxValue(SScriptCallBack *p, getCheckboxValue_out *out_args, int handle, int id)
{
    getCheckboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getCheckboxValue(p, &in_args, out_args);
}

void getCheckboxValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getCheckboxValue";

    getCheckboxValue_in in_args;
    getCheckboxValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getCheckboxValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (value) of type int
            write__int(out_args.value, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (value))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setCheckboxValue_in::setCheckboxValue_in()
{
    suppressEvents = false;
}

setCheckboxValue_out::setCheckboxValue_out()
{
}

void setCheckboxValue(SScriptCallBack *p, setCheckboxValue_in *in_args, setCheckboxValue_out *out_args)
{
    setCheckboxValue(p, "simExtCustomUI_setCheckboxValue", in_args, out_args);
}

void setCheckboxValue(SScriptCallBack *p, int handle, int id, int value, bool suppressEvents)
{
    setCheckboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setCheckboxValue_out out_args;
    setCheckboxValue(p, &in_args, &out_args);
}

void setCheckboxValue(SScriptCallBack *p, setCheckboxValue_out *out_args, int handle, int id, int value, bool suppressEvents)
{
    setCheckboxValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setCheckboxValue(p, &in_args, out_args);
}

void setCheckboxValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setCheckboxValue";

    setCheckboxValue_in in_args;
    setCheckboxValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (value) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.value));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (value)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (value))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (value)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setCheckboxValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getRadiobuttonValue_in::getRadiobuttonValue_in()
{
}

getRadiobuttonValue_out::getRadiobuttonValue_out()
{
}

void getRadiobuttonValue(SScriptCallBack *p, getRadiobuttonValue_in *in_args, getRadiobuttonValue_out *out_args)
{
    getRadiobuttonValue(p, "simExtCustomUI_getRadiobuttonValue", in_args, out_args);
}

int getRadiobuttonValue(SScriptCallBack *p, int handle, int id)
{
    getRadiobuttonValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getRadiobuttonValue_out out_args;
    getRadiobuttonValue(p, &in_args, &out_args);
    return out_args.value;
}

void getRadiobuttonValue(SScriptCallBack *p, getRadiobuttonValue_out *out_args, int handle, int id)
{
    getRadiobuttonValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getRadiobuttonValue(p, &in_args, out_args);
}

void getRadiobuttonValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getRadiobuttonValue";

    getRadiobuttonValue_in in_args;
    getRadiobuttonValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getRadiobuttonValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (value) of type int
            write__int(out_args.value, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (value))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setRadiobuttonValue_in::setRadiobuttonValue_in()
{
    suppressEvents = false;
}

setRadiobuttonValue_out::setRadiobuttonValue_out()
{
}

void setRadiobuttonValue(SScriptCallBack *p, setRadiobuttonValue_in *in_args, setRadiobuttonValue_out *out_args)
{
    setRadiobuttonValue(p, "simExtCustomUI_setRadiobuttonValue", in_args, out_args);
}

void setRadiobuttonValue(SScriptCallBack *p, int handle, int id, int value, bool suppressEvents)
{
    setRadiobuttonValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setRadiobuttonValue_out out_args;
    setRadiobuttonValue(p, &in_args, &out_args);
}

void setRadiobuttonValue(SScriptCallBack *p, setRadiobuttonValue_out *out_args, int handle, int id, int value, bool suppressEvents)
{
    setRadiobuttonValue_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.value = value;
    in_args.suppressEvents = suppressEvents;
    setRadiobuttonValue(p, &in_args, out_args);
}

void setRadiobuttonValue_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setRadiobuttonValue";

    setRadiobuttonValue_in in_args;
    setRadiobuttonValue_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (value) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.value));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (value)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (value))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (value)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setRadiobuttonValue(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getLabelText_in::getLabelText_in()
{
}

getLabelText_out::getLabelText_out()
{
}

void getLabelText(SScriptCallBack *p, getLabelText_in *in_args, getLabelText_out *out_args)
{
    getLabelText(p, "simExtCustomUI_getLabelText", in_args, out_args);
}

std::string getLabelText(SScriptCallBack *p, int handle, int id)
{
    getLabelText_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getLabelText_out out_args;
    getLabelText(p, &in_args, &out_args);
    return out_args.text;
}

void getLabelText(SScriptCallBack *p, getLabelText_out *out_args, int handle, int id)
{
    getLabelText_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getLabelText(p, &in_args, out_args);
}

void getLabelText_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getLabelText";

    getLabelText_in in_args;
    getLabelText_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getLabelText(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (text) of type std::string
            write__std__string(out_args.text, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (text)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (text))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (text))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setLabelText_in::setLabelText_in()
{
    suppressEvents = false;
}

setLabelText_out::setLabelText_out()
{
}

void setLabelText(SScriptCallBack *p, setLabelText_in *in_args, setLabelText_out *out_args)
{
    setLabelText(p, "simExtCustomUI_setLabelText", in_args, out_args);
}

void setLabelText(SScriptCallBack *p, int handle, int id, std::string text, bool suppressEvents)
{
    setLabelText_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.text = text;
    in_args.suppressEvents = suppressEvents;
    setLabelText_out out_args;
    setLabelText(p, &in_args, &out_args);
}

void setLabelText(SScriptCallBack *p, setLabelText_out *out_args, int handle, int id, std::string text, bool suppressEvents)
{
    setLabelText_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.text = text;
    in_args.suppressEvents = suppressEvents;
    setLabelText(p, &in_args, out_args);
}

void setLabelText_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setLabelText";

    setLabelText_in in_args;
    setLabelText_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (text) of type std::string
                simMoveStackItemToTopE(p->stackID, 0);
                read__std__string(p->stackID, &(in_args.text));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (text)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (text))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (text)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setLabelText(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

insertComboboxItem_in::insertComboboxItem_in()
{
    suppressEvents = false;
}

insertComboboxItem_out::insertComboboxItem_out()
{
}

void insertComboboxItem(SScriptCallBack *p, insertComboboxItem_in *in_args, insertComboboxItem_out *out_args)
{
    insertComboboxItem(p, "simExtCustomUI_insertComboboxItem", in_args, out_args);
}

void insertComboboxItem(SScriptCallBack *p, int handle, int id, int index, std::string text, bool suppressEvents)
{
    insertComboboxItem_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.index = index;
    in_args.text = text;
    in_args.suppressEvents = suppressEvents;
    insertComboboxItem_out out_args;
    insertComboboxItem(p, &in_args, &out_args);
}

void insertComboboxItem(SScriptCallBack *p, insertComboboxItem_out *out_args, int handle, int id, int index, std::string text, bool suppressEvents)
{
    insertComboboxItem_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.index = index;
    in_args.text = text;
    in_args.suppressEvents = suppressEvents;
    insertComboboxItem(p, &in_args, out_args);
}

void insertComboboxItem_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_insertComboboxItem";

    insertComboboxItem_in in_args;
    insertComboboxItem_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 4)
            throw exception("too few arguments");
        if(numArgs > 5)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (index) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.index));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (index)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (index))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (index)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (text) of type std::string
                simMoveStackItemToTopE(p->stackID, 0);
                read__std__string(p->stackID, &(in_args.text));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (text)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (text))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (text)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 5)
        {
            try
            {
                // read input argument 5 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 5 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 5 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 5 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        insertComboboxItem(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

removeComboboxItem_in::removeComboboxItem_in()
{
    suppressEvents = false;
}

removeComboboxItem_out::removeComboboxItem_out()
{
}

void removeComboboxItem(SScriptCallBack *p, removeComboboxItem_in *in_args, removeComboboxItem_out *out_args)
{
    removeComboboxItem(p, "simExtCustomUI_removeComboboxItem", in_args, out_args);
}

void removeComboboxItem(SScriptCallBack *p, int handle, int id, int index, bool suppressEvents)
{
    removeComboboxItem_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.index = index;
    in_args.suppressEvents = suppressEvents;
    removeComboboxItem_out out_args;
    removeComboboxItem(p, &in_args, &out_args);
}

void removeComboboxItem(SScriptCallBack *p, removeComboboxItem_out *out_args, int handle, int id, int index, bool suppressEvents)
{
    removeComboboxItem_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.index = index;
    in_args.suppressEvents = suppressEvents;
    removeComboboxItem(p, &in_args, out_args);
}

void removeComboboxItem_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_removeComboboxItem";

    removeComboboxItem_in in_args;
    removeComboboxItem_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (index) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.index));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (index)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (index))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (index)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        removeComboboxItem(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getComboboxItemCount_in::getComboboxItemCount_in()
{
}

getComboboxItemCount_out::getComboboxItemCount_out()
{
}

void getComboboxItemCount(SScriptCallBack *p, getComboboxItemCount_in *in_args, getComboboxItemCount_out *out_args)
{
    getComboboxItemCount(p, "simExtCustomUI_getComboboxItemCount", in_args, out_args);
}

int getComboboxItemCount(SScriptCallBack *p, int handle, int id)
{
    getComboboxItemCount_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getComboboxItemCount_out out_args;
    getComboboxItemCount(p, &in_args, &out_args);
    return out_args.count;
}

void getComboboxItemCount(SScriptCallBack *p, getComboboxItemCount_out *out_args, int handle, int id)
{
    getComboboxItemCount_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    getComboboxItemCount(p, &in_args, out_args);
}

void getComboboxItemCount_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getComboboxItemCount";

    getComboboxItemCount_in in_args;
    getComboboxItemCount_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 2)
            throw exception("too few arguments");
        if(numArgs > 2)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getComboboxItemCount(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (count) of type int
            write__int(out_args.count, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (count)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (count))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (count))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getComboboxItemText_in::getComboboxItemText_in()
{
}

getComboboxItemText_out::getComboboxItemText_out()
{
}

void getComboboxItemText(SScriptCallBack *p, getComboboxItemText_in *in_args, getComboboxItemText_out *out_args)
{
    getComboboxItemText(p, "simExtCustomUI_getComboboxItemText", in_args, out_args);
}

std::string getComboboxItemText(SScriptCallBack *p, int handle, int id, int index)
{
    getComboboxItemText_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.index = index;
    getComboboxItemText_out out_args;
    getComboboxItemText(p, &in_args, &out_args);
    return out_args.text;
}

void getComboboxItemText(SScriptCallBack *p, getComboboxItemText_out *out_args, int handle, int id, int index)
{
    getComboboxItemText_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.index = index;
    getComboboxItemText(p, &in_args, out_args);
}

void getComboboxItemText_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getComboboxItemText";

    getComboboxItemText_in in_args;
    getComboboxItemText_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 3)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (index) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.index));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (index)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (index))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (index)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getComboboxItemText(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (text) of type std::string
            write__std__string(out_args.text, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (text)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (text))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (text))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

hide_in::hide_in()
{
}

hide_out::hide_out()
{
}

void hide(SScriptCallBack *p, hide_in *in_args, hide_out *out_args)
{
    hide(p, "simExtCustomUI_hide", in_args, out_args);
}

void hide(SScriptCallBack *p, int handle)
{
    hide_in in_args;
    in_args.handle = handle;
    hide_out out_args;
    hide(p, &in_args, &out_args);
}

void hide(SScriptCallBack *p, hide_out *out_args, int handle)
{
    hide_in in_args;
    in_args.handle = handle;
    hide(p, &in_args, out_args);
}

void hide_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_hide";

    hide_in in_args;
    hide_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 1)
            throw exception("too few arguments");
        if(numArgs > 1)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        hide(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

show_in::show_in()
{
}

show_out::show_out()
{
}

void show(SScriptCallBack *p, show_in *in_args, show_out *out_args)
{
    show(p, "simExtCustomUI_show", in_args, out_args);
}

void show(SScriptCallBack *p, int handle)
{
    show_in in_args;
    in_args.handle = handle;
    show_out out_args;
    show(p, &in_args, &out_args);
}

void show(SScriptCallBack *p, show_out *out_args, int handle)
{
    show_in in_args;
    in_args.handle = handle;
    show(p, &in_args, out_args);
}

void show_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_show";

    show_in in_args;
    show_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 1)
            throw exception("too few arguments");
        if(numArgs > 1)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        show(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

isVisible_in::isVisible_in()
{
}

isVisible_out::isVisible_out()
{
}

void isVisible(SScriptCallBack *p, isVisible_in *in_args, isVisible_out *out_args)
{
    isVisible(p, "simExtCustomUI_isVisible", in_args, out_args);
}

bool isVisible(SScriptCallBack *p, int handle)
{
    isVisible_in in_args;
    in_args.handle = handle;
    isVisible_out out_args;
    isVisible(p, &in_args, &out_args);
    return out_args.visibility;
}

void isVisible(SScriptCallBack *p, isVisible_out *out_args, int handle)
{
    isVisible_in in_args;
    in_args.handle = handle;
    isVisible(p, &in_args, out_args);
}

void isVisible_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_isVisible";

    isVisible_in in_args;
    isVisible_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 1)
            throw exception("too few arguments");
        if(numArgs > 1)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        isVisible(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (visibility) of type bool
            write__bool(out_args.visibility, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (visibility)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (visibility))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (visibility))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

getPosition_in::getPosition_in()
{
}

getPosition_out::getPosition_out()
{
}

void getPosition(SScriptCallBack *p, getPosition_in *in_args, getPosition_out *out_args)
{
    getPosition(p, "simExtCustomUI_getPosition", in_args, out_args);
}

void getPosition(SScriptCallBack *p, getPosition_out *out_args, int handle)
{
    getPosition_in in_args;
    in_args.handle = handle;
    getPosition(p, &in_args, out_args);
}

void getPosition_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_getPosition";

    getPosition_in in_args;
    getPosition_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 1)
            throw exception("too few arguments");
        if(numArgs > 1)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        getPosition(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

        try
        {
            // write output argument 1 (x) of type int
            write__int(out_args.x, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 1 (x)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 1 (x))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 1 (x))";
            throw exception(ss.str());
        }
        try
        {
            // write output argument 2 (y) of type int
            write__int(out_args.y, p->stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing output argument 2 (y)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing output argument 2 (y))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " (when writing output argument 2 (y))";
            throw exception(ss.str());
        }
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setPosition_in::setPosition_in()
{
    suppressEvents = false;
}

setPosition_out::setPosition_out()
{
}

void setPosition(SScriptCallBack *p, setPosition_in *in_args, setPosition_out *out_args)
{
    setPosition(p, "simExtCustomUI_setPosition", in_args, out_args);
}

void setPosition(SScriptCallBack *p, int handle, int x, int y, bool suppressEvents)
{
    setPosition_in in_args;
    in_args.handle = handle;
    in_args.x = x;
    in_args.y = y;
    in_args.suppressEvents = suppressEvents;
    setPosition_out out_args;
    setPosition(p, &in_args, &out_args);
}

void setPosition(SScriptCallBack *p, setPosition_out *out_args, int handle, int x, int y, bool suppressEvents)
{
    setPosition_in in_args;
    in_args.handle = handle;
    in_args.x = x;
    in_args.y = y;
    in_args.suppressEvents = suppressEvents;
    setPosition(p, &in_args, out_args);
}

void setPosition_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setPosition";

    setPosition_in in_args;
    setPosition_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (x) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.x));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (x)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (x))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (x)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (y) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.y));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (y)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (y))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (y)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setPosition(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setImageData_in::setImageData_in()
{
}

setImageData_out::setImageData_out()
{
}

void setImageData(SScriptCallBack *p, setImageData_in *in_args, setImageData_out *out_args)
{
    setImageData(p, "simExtCustomUI_setImageData", in_args, out_args);
}

void setImageData(SScriptCallBack *p, int handle, int id, std::string data, int width, int height)
{
    setImageData_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.data = data;
    in_args.width = width;
    in_args.height = height;
    setImageData_out out_args;
    setImageData(p, &in_args, &out_args);
}

void setImageData(SScriptCallBack *p, setImageData_out *out_args, int handle, int id, std::string data, int width, int height)
{
    setImageData_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.data = data;
    in_args.width = width;
    in_args.height = height;
    setImageData(p, &in_args, out_args);
}

void setImageData_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setImageData";

    setImageData_in in_args;
    setImageData_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 5)
            throw exception("too few arguments");
        if(numArgs > 5)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (data) of type std::string
                simMoveStackItemToTopE(p->stackID, 0);
                read__std__string(p->stackID, &(in_args.data));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (data)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (data))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (data)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (width) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.width));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (width)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (width))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (width)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 5)
        {
            try
            {
                // read input argument 5 (height) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.height));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 5 (height)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 5 (height))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 5 (height)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setImageData(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

setEnabled_in::setEnabled_in()
{
    suppressEvents = false;
}

setEnabled_out::setEnabled_out()
{
}

void setEnabled(SScriptCallBack *p, setEnabled_in *in_args, setEnabled_out *out_args)
{
    setEnabled(p, "simExtCustomUI_setEnabled", in_args, out_args);
}

void setEnabled(SScriptCallBack *p, int handle, int id, bool enabled, bool suppressEvents)
{
    setEnabled_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.enabled = enabled;
    in_args.suppressEvents = suppressEvents;
    setEnabled_out out_args;
    setEnabled(p, &in_args, &out_args);
}

void setEnabled(SScriptCallBack *p, setEnabled_out *out_args, int handle, int id, bool enabled, bool suppressEvents)
{
    setEnabled_in in_args;
    in_args.handle = handle;
    in_args.id = id;
    in_args.enabled = enabled;
    in_args.suppressEvents = suppressEvents;
    setEnabled(p, &in_args, out_args);
}

void setEnabled_callback(SScriptCallBack *p)
{
    const char *cmd = "simExtCustomUI_setEnabled";

    setEnabled_in in_args;
    setEnabled_out out_args;

    try
    {
        // check argument count
        
        int numArgs = simGetStackSizeE(p->stackID);
        if(numArgs < 3)
            throw exception("too few arguments");
        if(numArgs > 4)
            throw exception("too many arguments");

        // read input arguments from stack

        if(numArgs >= 1)
        {
            try
            {
                // read input argument 1 (handle) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.handle));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 1 (handle)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 1 (handle))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 1 (handle)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 2)
        {
            try
            {
                // read input argument 2 (id) of type int
                simMoveStackItemToTopE(p->stackID, 0);
                read__int(p->stackID, &(in_args.id));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 2 (id)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 2 (id))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 2 (id)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 3)
        {
            try
            {
                // read input argument 3 (enabled) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.enabled));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 3 (enabled)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 3 (enabled))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 3 (enabled)";
                throw exception(ss.str());
            }
        }


        if(numArgs >= 4)
        {
            try
            {
                // read input argument 4 (suppressEvents) of type bool
                simMoveStackItemToTopE(p->stackID, 0);
                read__bool(p->stackID, &(in_args.suppressEvents));
            }
            catch(std::exception& ex)
            {
                std::string msg = ex.what();
                msg += " when reading input argument 4 (suppressEvents)";
                throw exception(msg);
            }
            catch(std::string& s)
            {
                std::string msg = s;
                msg += " (when reading input argument 4 (suppressEvents))";
                throw exception(msg);
            }
            catch(int& n)
            {
                std::stringstream ss;
                ss << "error #" << n << " when reading input argument 4 (suppressEvents)";
                throw exception(ss.str());
            }
        }


        // clear stack
        simPopStackItemE(p->stackID, 0);


        setEnabled(p, cmd, &in_args, &out_args);
    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
    }

    try
    {
        // clear stack
        simPopStackItemE(p->stackID, 0);


        // write output arguments to stack

    }
    catch(std::exception& e)
    {
        simSetLastError(cmd, e.what());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(std::string& s)
    {
        simSetLastError(cmd, s.c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
    catch(int& n)
    {
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(cmd, ss.str().c_str());
        // clear stack
        simPopStackItem(p->stackID, 0); // don't throw
    }
}

onclickCallback_in::onclickCallback_in()
{
}

onclickCallback_out::onclickCallback_out()
{
}

bool onclickCallback(simInt scriptId, const char *func, onclickCallback_in *in_args, onclickCallback_out *out_args)
{
    int stackID = -1;

    try
    {
        stackID = simCreateStackE();
        
        // write input arguments to stack
        
        try
        {
            // write input argument 1 (handle) of type int
            write__int(in_args->handle, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 1 (handle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 1 (handle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 1 (handle)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 2 (id) of type int
            write__int(in_args->id, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 2 (id)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 2 (id))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 2 (id)";
            throw exception(ss.str());
        }

        
        simCallScriptFunctionExE(scriptId, func, stackID);

        // read output arguments from stack
        

        simReleaseStackE(stackID);
        stackID = -1;
    }
    catch(std::exception& ex)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, ex.what());
        return false;
    }
    catch(std::string& s)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, s.c_str());
        return false;
    }
    catch(int& n)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(func, ss.str().c_str());
        return false;
    }
    
    return true;
}

onchangeIntCallback_in::onchangeIntCallback_in()
{
}

onchangeIntCallback_out::onchangeIntCallback_out()
{
}

bool onchangeIntCallback(simInt scriptId, const char *func, onchangeIntCallback_in *in_args, onchangeIntCallback_out *out_args)
{
    int stackID = -1;

    try
    {
        stackID = simCreateStackE();
        
        // write input arguments to stack
        
        try
        {
            // write input argument 1 (handle) of type int
            write__int(in_args->handle, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 1 (handle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 1 (handle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 1 (handle)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 2 (id) of type int
            write__int(in_args->id, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 2 (id)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 2 (id))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 2 (id)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 3 (value) of type int
            write__int(in_args->value, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 3 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 3 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 3 (value)";
            throw exception(ss.str());
        }

        
        simCallScriptFunctionExE(scriptId, func, stackID);

        // read output arguments from stack
        

        simReleaseStackE(stackID);
        stackID = -1;
    }
    catch(std::exception& ex)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, ex.what());
        return false;
    }
    catch(std::string& s)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, s.c_str());
        return false;
    }
    catch(int& n)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(func, ss.str().c_str());
        return false;
    }
    
    return true;
}

onchangeDoubleCallback_in::onchangeDoubleCallback_in()
{
}

onchangeDoubleCallback_out::onchangeDoubleCallback_out()
{
}

bool onchangeDoubleCallback(simInt scriptId, const char *func, onchangeDoubleCallback_in *in_args, onchangeDoubleCallback_out *out_args)
{
    int stackID = -1;

    try
    {
        stackID = simCreateStackE();
        
        // write input arguments to stack
        
        try
        {
            // write input argument 1 (handle) of type int
            write__int(in_args->handle, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 1 (handle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 1 (handle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 1 (handle)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 2 (id) of type int
            write__int(in_args->id, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 2 (id)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 2 (id))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 2 (id)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 3 (value) of type float
            write__float(in_args->value, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 3 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 3 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 3 (value)";
            throw exception(ss.str());
        }

        
        simCallScriptFunctionExE(scriptId, func, stackID);

        // read output arguments from stack
        

        simReleaseStackE(stackID);
        stackID = -1;
    }
    catch(std::exception& ex)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, ex.what());
        return false;
    }
    catch(std::string& s)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, s.c_str());
        return false;
    }
    catch(int& n)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(func, ss.str().c_str());
        return false;
    }
    
    return true;
}

onchangeStringCallback_in::onchangeStringCallback_in()
{
}

onchangeStringCallback_out::onchangeStringCallback_out()
{
}

bool onchangeStringCallback(simInt scriptId, const char *func, onchangeStringCallback_in *in_args, onchangeStringCallback_out *out_args)
{
    int stackID = -1;

    try
    {
        stackID = simCreateStackE();
        
        // write input arguments to stack
        
        try
        {
            // write input argument 1 (handle) of type int
            write__int(in_args->handle, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 1 (handle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 1 (handle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 1 (handle)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 2 (id) of type int
            write__int(in_args->id, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 2 (id)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 2 (id))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 2 (id)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 3 (value) of type std::string
            write__std__string(in_args->value, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 3 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 3 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 3 (value)";
            throw exception(ss.str());
        }

        
        simCallScriptFunctionExE(scriptId, func, stackID);

        // read output arguments from stack
        

        simReleaseStackE(stackID);
        stackID = -1;
    }
    catch(std::exception& ex)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, ex.what());
        return false;
    }
    catch(std::string& s)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, s.c_str());
        return false;
    }
    catch(int& n)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(func, ss.str().c_str());
        return false;
    }
    
    return true;
}

oneditingfinishedCallback_in::oneditingfinishedCallback_in()
{
}

oneditingfinishedCallback_out::oneditingfinishedCallback_out()
{
}

bool oneditingfinishedCallback(simInt scriptId, const char *func, oneditingfinishedCallback_in *in_args, oneditingfinishedCallback_out *out_args)
{
    int stackID = -1;

    try
    {
        stackID = simCreateStackE();
        
        // write input arguments to stack
        
        try
        {
            // write input argument 1 (handle) of type int
            write__int(in_args->handle, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 1 (handle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 1 (handle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 1 (handle)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 2 (id) of type int
            write__int(in_args->id, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 2 (id)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 2 (id))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 2 (id)";
            throw exception(ss.str());
        }
        try
        {
            // write input argument 3 (value) of type std::string
            write__std__string(in_args->value, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 3 (value)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 3 (value))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 3 (value)";
            throw exception(ss.str());
        }

        
        simCallScriptFunctionExE(scriptId, func, stackID);

        // read output arguments from stack
        

        simReleaseStackE(stackID);
        stackID = -1;
    }
    catch(std::exception& ex)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, ex.what());
        return false;
    }
    catch(std::string& s)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, s.c_str());
        return false;
    }
    catch(int& n)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(func, ss.str().c_str());
        return false;
    }
    
    return true;
}

oncloseCallback_in::oncloseCallback_in()
{
}

oncloseCallback_out::oncloseCallback_out()
{
}

bool oncloseCallback(simInt scriptId, const char *func, oncloseCallback_in *in_args, oncloseCallback_out *out_args)
{
    int stackID = -1;

    try
    {
        stackID = simCreateStackE();
        
        // write input arguments to stack
        
        try
        {
            // write input argument 1 (handle) of type int
            write__int(in_args->handle, stackID);
        }
        catch(std::exception& ex)
        {
            std::string msg = ex.what();
            msg += " when writing input argument 1 (handle)";
            throw exception(msg);
        }
        catch(std::string& s)
        {
            std::string msg = s;
            msg += " (when writing input argument 1 (handle))";
            throw exception(msg);
        }
        catch(int& n)
        {
            std::stringstream ss;
            ss << "error #" << n << " when writing input argument 1 (handle)";
            throw exception(ss.str());
        }

        
        simCallScriptFunctionExE(scriptId, func, stackID);

        // read output arguments from stack
        

        simReleaseStackE(stackID);
        stackID = -1;
    }
    catch(std::exception& ex)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, ex.what());
        return false;
    }
    catch(std::string& s)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        simSetLastError(func, s.c_str());
        return false;
    }
    catch(int& n)
    {
        if(stackID != -1)
            simReleaseStack(stackID); // don't throw
        std::stringstream ss;
        ss << "error #" << n;
        simSetLastError(func, ss.str().c_str());
        return false;
    }
    
    return true;
}

