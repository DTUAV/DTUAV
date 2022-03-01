﻿/*
* Copyright (C) 2019 YY Inc. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License"); 
* you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at
*
*	http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, 
* software distributed under the License is distributed on an "AS IS" BASIS, 
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and 
* limitations under the License.
*/

#ifndef __X_JSON_WRITER_H
#define __X_JSON_WRITER_H

#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

#include "rapidjson_custom.h"
#include "thirdparty/rapidjson/prettywriter.h"
#include "thirdparty/rapidjson/stringbuffer.h"

#include "xtypes.h"
#include "traits.h"
#include "xwriter.h"

namespace x2struct {

class JsonWriter:public XWriter<JsonWriter> {
    typedef rapidjson::StringBuffer JSON_WRITER_BUFFER;
    typedef rapidjson::Writer<rapidjson::StringBuffer> JSON_WRITER_WRITER;
    typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> JSON_WRITER_PRETTY;
public:
    friend class XWriter<JsonWriter>;
    using xdoc_type::convert;

    JsonWriter(int indentCount=0, char indentChar=' ') {
        _buf = new JSON_WRITER_BUFFER;
        if (indentCount < 0) {
            _writer = new JSON_WRITER_WRITER(*_buf);
            _pretty = 0;
        } else {
            _pretty = new JSON_WRITER_PRETTY(*_buf);
            _pretty->SetIndent(indentChar, indentCount);
            _writer = 0;
        }
    }
    ~JsonWriter() {
        if (0 != _buf) {
            delete _buf;
        }
        if (0 != _writer) {
            delete _writer;
        }
        if (0 != _pretty) {
            delete _pretty;
        }
    }
public:
    std::string toStr() {
        return _buf->GetString();
    }

    void x2struct_set_key(const char*key) { // openssl defined set_key macro, so we named it x2struct_set_key ...
        if (0!=key && key[0]!='\0') {
            if (0 != _writer) {
                _writer->Key(key);
            } else {
                _pretty->Key(key);
            }
        }
    }
    void array_begin() {
        if (0 != _writer) {
            _writer->StartArray();
        } else {
            _pretty->StartArray();
        }
    }
    void array_end() {
        if (0 != _writer) {
            _writer->EndArray();
        } else {
            _pretty->EndArray();
        }
    }
    void object_begin() {
        if (0 != _writer) {
            _writer->StartObject();
        } else {
            _pretty->StartObject();
        }
    }
    void object_end() {
        if (0 != _writer) {
            _writer->EndObject();
        } else {
            _pretty->EndObject();
        }
    }
    const std::string&type() {
        static std::string t("json");
        return t;
    }

    JsonWriter& convert(const char*key, const std::string &val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->String(val);
        } else {
            _pretty->String(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, bool val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Bool(val);
        } else {
            _pretty->Bool(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, int16_t val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Int(val);
        } else {
            _pretty->Int(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, uint16_t val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Uint(val);
        } else {
            _pretty->Uint(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, int32_t val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Int(val);
        } else {
            _pretty->Int(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, uint32_t val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Uint(val);
        } else {
            _pretty->Uint(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, int64_t val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Int64(val);
        } else {
            _pretty->Int64(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, uint64_t val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Uint64(val);
        } else {
            _pretty->Uint64(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, double val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Double(val);
        } else {
            _pretty->Double(val);
        }
        return *this;
    }
    JsonWriter& convert(const char*key, float val) {
        x2struct_set_key(key);
        if (0 != _writer) {
            _writer->Double(val);
        } else {
            _pretty->Double(val);
        }
        return *this;
    }

    template<typename T>
    JsonWriter& convert(const char*key, const std::vector<T>&data) {
        x2struct_set_key(key);
        this->array_begin();
        for (size_t i=0; i<data.size(); ++i) {
            this->convert("", data[i]);
        }
        this->array_end();
        return *this;
    }

    template<typename T>
    JsonWriter& convert(const char*key, const std::list<T>&data) {
        x2struct_set_key(key);
        this->array_begin();
        for (typename std::list<T>::const_iterator it=data.begin(); it!=data.end(); ++it) {
            this->convert("", *it);
        }
        this->array_end();
        return *this;
    }

    template<typename T>
    JsonWriter& convert(const char*key, const std::set<T>&data) {
        x2struct_set_key(key);
        this->array_begin();
        for (typename std::set<T>::const_iterator it=data.begin(); it!=data.end(); ++it) {
            this->convert("", *it);
        }
        this->array_end();
        return *this;
    }

    template <typename T>
    void convert(const char*key, const std::map<std::string, T> &data) {
        x2struct_set_key(key);
        this->object_begin();
        for (typename std::map<std::string,T>::const_iterator iter=data.begin(); iter!=data.end(); ++iter) {
            this->convert(iter->first.c_str(), iter->second);
        }
        this->object_end();
    }

    template <typename KEY, typename T>
    void convert(const char*key, const std::map<KEY, T> &data) {
        x2struct_set_key(key);
        this->object_begin();
        for (typename std::map<KEY,T>::const_iterator iter=data.begin(); iter!=data.end(); ++iter) {
            std::string _k =Util::tostr(iter->first);
            this->convert(_k.c_str(), iter->second);
        }
        this->object_end();
    }

    #ifdef X_SUPPORT_C0X
    // unordered_map
    template <typename T>
    void convert(const char*key, const std::unordered_map<std::string, T> &data) {
        x2struct_set_key(key);
        this->object_begin();
        for (typename std::unordered_map<std::string,T>::const_iterator iter=data.begin(); iter!=data.end(); ++iter) {
            this->convert(iter->first.c_str(), iter->second);
        }
        this->object_end();
    }

    // shared_ptr
    template <typename TYPE>
    void convert(const char*key, const std::shared_ptr<TYPE>& val) {
        if (NULL == val.get()) {
            return;
        }
        this->convert(key, *val);
    }

    // class/struct that not defined macro XTOSTRUCT
    template <typename T, typename std::enable_if<!x_has_x2struct<T>::value, int>::type = 0>
    void convert(const char*key, const T& data, x_for_class(T, int) *unused=0) {
        (void)unused;
        x2struct_set_key(key);
        this->object_begin();
        x_struct_to_str(*this, key, data);
        this->object_end();
    }

    // class/struct that defined macro XTOSTRUCT
    template <typename T, typename std::enable_if<x_has_x2struct<T>::value, int>::type = 0>
    void convert(const char*key, const T& data) {
    #else
    template <typename T>
    void convert(const char*key, const T& data, x_for_class(T, int) *p=0) {
        (void)p;
    #endif
        x2struct_set_key(key);
        this->object_begin();
        data.__struct_to_str(*this, key);
        this->object_end();
    }
private:
    JSON_WRITER_BUFFER* _buf;
    JSON_WRITER_WRITER* _writer;
    JSON_WRITER_PRETTY* _pretty;
};

}

#endif
