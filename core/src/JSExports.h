//
// Created by pengfei.zhou on 2020-05-28.
//

#ifndef JSC4A_JSVALUEWRAPPER_H
#define JSC4A_JSVALUEWRAPPER_H

#include <string>
#include <unordered_map>
#include <vector>

namespace js_export {
    enum class JSType : char {
        JSTypeNull = 0,
        JSTypeNumber = 1,
        JSTypeBoolean = 2,
        JSTypeString = 3,
        JSTypeObject = 4,
        JSTypeArray = 5,
    };

    class JSNull;

    class JSNumber;

    class JSBoolean;

    class JSString;

    class JSObject;

    class JSArray;

    class JSValue {
    public:
        JSValue();

        ~JSValue();

        JSType m_type;

        bool isNull();

        bool isNumber();

        bool isBoolean();

        bool isString();

        bool isObject();

        bool isArray();

        JSNull *asNull();

        JSNumber *asNumber();

        JSBoolean *asBoolean();

        JSString *asString();

        JSObject *asObject();

        JSArray *asArray();

    private:
    };

    class JSNull : public JSValue {
    public:
        JSNull();
    };

    class JSNumber : public JSValue {
    public:
        explicit JSNumber(double v);

        double value();

    private:
        double m_value;
    };

    class JSBoolean : public JSValue {
    public:
        explicit JSBoolean(bool v);

        bool value();

    private:
        bool m_value;
    };

    class JSString : public JSValue {
    public:
        explicit JSString(const char *v);

        explicit JSString(const std::string &v);

        const char *value();

    private:
        std::string m_value;
    };

    class JSObject : public JSValue {
    public:
        JSObject();

        void setProperty(std::string &name, JSValue *value);

        JSValue *getProperty(std::string &name);

    private:
        std::unordered_map<std::string, std::shared_ptr<JSValue>> m_value;
    };

    class JSArray : public JSValue {
    public:
        JSArray(int size);

        void put(int index, JSValue *value);

        JSValue *get(int index);

    private:
        int m_size;

        std::vector<std::shared_ptr<JSValue>> m_value;
    };

    typedef JSValue *(*InjectedFunction)(JSValue *[], int);

    void InjectJSFunction(void *jse_ptr, const char *name, InjectedFunction func_ptr);
}
#endif //JSC4A_JSVALUEWRAPPER_H
