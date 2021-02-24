// Jsob.h version 1.0.0 made by twoone3
// Github: https://github.com/twoone-3/Json
// All development is aimed at learning
#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#pragma warning(disable:4996)
#define addTab for (unsigned num = tab; num; num--)s += '\t';
#define CHECK_END if(!*it) return Error::UNEXPECTED_NULL_CHARACTER
#define JsonAssert(condition) if(!(condition))abort()
#define CHECK(x) do{Error err = x;if(err != Error::OK)return err;}while(0)

using std::string;
using std::to_string;
using std::map;
using std::move;
using std::ostream;
using std::ostringstream;

class Json {
public:
	typedef map<size_t, Json> Array;
	typedef map<string, Json> Object;
	enum class Type {
		Null, Bool, Int, Int64,
		Double, String, Array, Object
	};
	enum class Error {
		OK,
		INVALID_CHARACTER,
		UNEXPECTED_NULL_CHARACTER,
		MISS_COLON,
		MISS_DOUBLE_QUOTATION_MARK,
		MISS_COMMAS_OR_BRACES,
		MISS_SLASH_OR_ASTERISK,
		UNKNOW_ESCAPE,
		NUMBER_OVERFLOW
	};

	Json() : t(Type::Null) { data.b = 0; }
	Json(const bool b) : t(Type::Bool) { data.b = b; }
	Json(const int i) : t(Type::Int) { data.i = i; }
	Json(const long long l) : t(Type::Int64) { data.l = l; }
	Json(const double d) : t(Type::Double) { data.d = d; }
	Json(const char* s) : t(Type::String) { data.s = new char[strlen(s) + 1]; strcpy(data.s, s); }
	Json(const string& s) : t(Type::String) { data.s = new char[s.length() + 1]; strcpy(data.s, s.c_str()); }
	Json(const Array& a) : t(Type::Array) { data.a = new Array(a); }
	Json(const Object& o) : t(Type::Object) { data.o = new Object(o); }
	Json(const Type& type) : t(type) {
		data.i = 0;
		switch (type) {
		case Type::Null:break;
		case Type::Bool:break;
		case Type::Int:break;
		case Type::Int64:break;
		case Type::Double:break;
		case Type::String:break;
		case Type::Array:
			data.a = new Array;
			break;
		case Type::Object:
			data.o = new Object;
			break;
		}
	}
	Json(const Json& j) {
		clear();
		switch (j.t) {
		case Type::Null:break;
		case Type::Bool:data.b = j.data.b; break;
		case Type::Int:data.i = j.data.i; break;
		case Type::Int64:data.l = j.data.l; break;
		case Type::Double:data.d = j.data.d; break;
		case Type::String:
			data.s = new char[strlen(j.data.s) + 1];
			strcpy(data.s, j.data.s);
			break;
		case Type::Array:
			data.a = new Array;
			*data.a = *j.data.a;
			break;
		case Type::Object:
			data.o = new Object;
			*data.o = *j.data.o;
			break;
		}
		t = j.t;
	};
	Json(Json&& j)noexcept {
		t = j.t;
		data.l = j.data.l;
		j.t = Type::Null;
		j.data.l = 0;
	};
	~Json() { clear(); }

	string toFastString()const {
		switch (t) {
		case Type::Null:return "null";
		case Type::Bool:return data.b ? "true" : "false";
		case Type::Int:return to_string(data.i);
		case Type::Int64:return to_string(data.l);
		case Type::Double:return double_to_string(data.d);
		case Type::String:return '"' + string(data.s) + '"';
		case Type::Array: {
			string s;
			s += '[';
			if (data.a->empty())
				return s += ']';
			for (auto& i : *data.a) {
				s += i.second.toFastString();
				s += ',';
			}
			s.pop_back();
			s += ']';
			return s;
		}
		case Type::Object: {
			string s;
			s += '{';
			if (data.o->empty())
				return s += '}';
			for (auto& i : *data.o) {
				s += '"';
				s += i.first;
				s += '"';
				s += ':';
				s += i.second.toFastString();
				s += ',';
			}
			s.pop_back();
			s += '}';
			return s;
		}
		}
		return "";
	}
	string toStyledString()const {
		static unsigned tab = 0;
		switch (t) {
		case Type::Null:return "null";
		case Type::Bool:return data.b ? "true" : "false";
		case Type::Int:return to_string(data.i);
		case Type::Int64:return to_string(data.l);
		case Type::Double:return double_to_string(data.d);
		case Type::String:return '"' + string(data.s) + '"';
		case Type::Array: {
			string s;
			s += '[';
			if (data.a->empty()) {
				return s += ']';
			}
			s += '\n';
			tab++;
			for (auto& i : *data.a) {
				addTab;
				s += i.second.toStyledString();
				s += ',';
				s += '\n';
			}
			tab--;
			s.resize(s.length() - 2);
			s += '\n';
			addTab;
			s += ']';
			return s;
		}
		case Type::Object: {
			string s;
			s += '{';
			if (data.o->empty()) {
				return s += '}';
			}
			s += '\n';
			tab++;
			for (auto& i : *data.o) {
				addTab;
				s += '"';
				s += i.first;
				s += '"';
				s += ':';
				s += ' ';
				s += i.second.toStyledString();
				s += ',';
				s += '\n';
			}
			tab--;
			s.resize(s.length() - 2);
			s += '\n';
			addTab;
			s += '}';
			return s;
		}
		}
		return "";
	}

	Type type()const { return t; }
	void remove(const unsigned i) {
		JsonAssert(t == Type::Array);
		data.a->erase(i);
	}
	void remove(const string& i) {
		JsonAssert(t == Type::Object);
		data.o->erase(i);
	}
	void append(const Json& j) {
		JsonAssert(t == Type::Array || t == Type::Null);
		if (t == Type::Null) {
			*this = Type::Array;
		}
		data.a->emplace(data.a->size(), j);
	}
	size_t size()const {
		switch (t) {
		case Type::Null:break;
		case Type::Bool:break;
		case Type::Int:break;
		case Type::Int64:break;
		case Type::Double:break;
		case Type::String:break;
		case Type::Array:return data.a->size();
		case Type::Object:return data.o->size();
		}
		return 0;
	}
	bool empty()const {
		switch (t) {
		case Type::Null:return 1;
		case Type::Bool:break;
		case Type::Int:break;
		case Type::Int64:break;
		case Type::Double:break;
		case Type::String:break;
		case Type::Array:return data.a->empty();
		case Type::Object:return data.o->empty();
		}
		return 0;
	}
	bool Has(const string& key)const {
		JsonAssert(t == Type::Object);
		return data.o->find(key) != data.o->end();
	}
	void clear() {
		switch (t) {
		case Type::Null:break;
		case Type::Bool:break;
		case Type::Int:break;
		case Type::Int64:break;
		case Type::Double:break;
		case Type::String:
			delete[] data.s;
			break;
		case Type::Array:
			delete data.a;
			break;
		case Type::Object:
			delete data.o;
			break;
		}
		t = Type::Null;
		data.o = 0;
	}

	auto asBool()const { return data.b; }
	auto asInt()const { return data.i; }
	auto asLongLong()const { return data.l; }
	auto asDouble()const { return data.d; }
	auto asString()const { return *data.s; }
	auto asArray()const { return *data.a; }
	auto asObject()const { return *data.o; }

	Json& operator[](const string& i) {
		JsonAssert(t == Type::Object || t == Type::Null);
		if (t == Type::Null) {
			*this = Type::Object;
		}
		return (*data.o)[i];
	}
	Json& operator[](const unsigned i) {
		JsonAssert(t == Type::Array || t == Type::Null);
		if (t == Type::Null) {
			*this = Type::Array;
		}
		return (*data.a)[i];
	}
	const Json& operator[](const string& i)const {
		JsonAssert(t == Type::Object);
		return (*data.o)[i];
	}
	const Json& operator[](const unsigned i)const {
		JsonAssert(t == Type::Array);
		return (*data.a)[i];
	}
	Json& operator=(const Json& j) {
		clear();
		switch (j.t) {
		case Type::Null:break;
		case Type::Bool:data.b = j.data.b; break;
		case Type::Int:data.i = j.data.i; break;
		case Type::Int64:data.l = j.data.l; break;
		case Type::Double:data.d = j.data.d; break;
		case Type::String:data.s = j.data.s; break;
		case Type::Array:
			data.a = new Array;
			*data.a = *j.data.a;
			break;
		case Type::Object:
			data.o = new Object;
			*data.o = *j.data.o;
			break;
		}
		t = j.t;
		return *this;
	};
	Json& operator=(Json&& j)noexcept {
		t = j.t;
		data.l = j.data.l;
		j.t = Type::Null;
		j.data.l = 0;
		return *this;
	};

	Error fromString(const string& s) {
		return fromString(s.c_str());
	}
	Error fromString(const char* s) {
		clear();
		return read_Value(s);
	}
private:
	Error read_Value(const char*& it) {
		CHECK(skip(it));
		switch (*it) {
		case 'n':
			if (!strncmp(it, "null", 4))it += 4;
			else return Error::INVALID_CHARACTER;
			break;
		case 't':
			if (!strncmp(it, "true", 4)) { *this = true; it += 4; }
			else return Error::INVALID_CHARACTER;
			break;
		case 'f':
			if (!strncmp(it, "false", 5)) { *this = false; it += 5; }
			else return Error::INVALID_CHARACTER;
			break;
		case '[':return read_Array(it);
		case '{':return read_Object(it);
		case '"': {
			string s;
			Error err = read_String(it, s);
			*this = s;
			return err;
		};
		default:
			if (*it == '-' || *it == '+' || (*it >= '0' && *it <= '9')) {
				return read_Number(it);
			}
			else return Error::INVALID_CHARACTER;
		}
		return Error::OK;
	}
#define ISDIGIT(num) ((num >= '0') && (num <= '9'))
#define ISDIGIT1TO9(num) ((num >= '1') && (num <= '9'))
	Error read_Number(const char*& it) {
		const char* tmp_it = it;
		if (*tmp_it == '-')
			tmp_it++;
		if (*tmp_it == '0')
			tmp_it++;
		else {
			if (!ISDIGIT1TO9(*tmp_it))
				return Error::INVALID_CHARACTER;
			for (tmp_it++; ISDIGIT(*tmp_it); tmp_it++);
		}
		if (*tmp_it == '.') {
			tmp_it++;
			if (!ISDIGIT(*tmp_it))
				return Error::INVALID_CHARACTER;
			for (tmp_it++; ISDIGIT(*tmp_it); tmp_it++);
		}
		if (*tmp_it == 'e' || *tmp_it == 'E') {
			tmp_it++;
			if (*tmp_it == '-' || *tmp_it == '+')
				tmp_it++;
			if (!ISDIGIT(*tmp_it))
				return Error::INVALID_CHARACTER;
			for (tmp_it++; ISDIGIT(*tmp_it); tmp_it++);
		}
		double num = strtod(it, NULL);
		if (errno == ERANGE && (num == HUGE_VAL || num == -HUGE_VAL))
			return Error::NUMBER_OVERFLOW;
		it = tmp_it;
		if ((num - (int)num) == 0) {
			*this = (int)num;
			return Error::OK;
		}
		*this = num;
		return Error::OK;
	}
	Error read_Object(const char*& it) {
		it++;
		CHECK(skip(it));
		*this = Type::Object;
		if (*it == '}') {
			it++;
			return Error::OK;
		}
		while (1) {
			CHECK(skip(it));
			CHECK_END;
			if (*it != '"')
				return Error::MISS_DOUBLE_QUOTATION_MARK;
			string key;
			CHECK(read_String(it, key));
			CHECK(skip(it));
			CHECK_END;
			if (*it != ':')
				return Error::MISS_COLON;
			it++;
			CHECK(skip(it));
			CHECK_END;
			Json j;
			CHECK(j.read_Value(it));
			data.o->emplace(key, move(j));
			CHECK(skip(it));
			CHECK_END;
			if (*it == ',')
				it++;
			else if (*it == '}') {
				it++;
				return Error::OK;
			}
			else return Error::MISS_COMMAS_OR_BRACES;
		}
	}
	Error read_Array(const char*& it) {
		it++;
		*this = Type::Array;
		CHECK(skip(it));
		if (*it == ']') {
			it++;
			return Error::OK;
		}
		while (*it) {
			Json j;
			CHECK(j.read_Value(it));
			CHECK(skip(it));
			CHECK_END;
			data.a->emplace(data.a->size(), move(j));
			if (*it == ',') {
				it++;
			}
			else if (*it == ']') {
				it++;
				break;
			}
			else return Error::MISS_COMMAS_OR_BRACES;
		}
		return Error::OK;
	}
	static Error skip(const char*& it) {
		while (*it == ' ' or *it == '\n' or *it == '\t' or *it == '\r' or *it == '/') {
			if (*it == '/') {
				it++;
				if (*it == '/') {
					it++;
					while (*it != '\n') {
						it++;
						CHECK_END;
					}
					it++;
				}
				else if (*it == '*') {
					it++;
					while (*it != '*' or *(it + 1) != '/') {
						it++;
						CHECK_END;
					}
					it++;
				}
				else {
					return Error::MISS_SLASH_OR_ASTERISK;
				}
			}
			it++;
		}
		return Error::OK;
	}
	static string double_to_string(const double d) {
		ostringstream ss;
		ss << d;
		return ss.str();
	}
	static Error read_Hex4(const char*& it, unsigned& u) {
		u = 0;
		char ch = 0;
		for (int i = 0; i < 4; i++) {
			u <<= 4;
			CHECK_END;
			ch = *it++;
			if (ch >= '0' && ch <= '9')
				u |= ch - '0';
			else if (ch >= 'a' && ch <= 'f')
				u |= ch - 'a' + 10;
			else if (ch >= 'A' && ch <= 'F')
				u |= ch - 'A' + 10;
			else return Error::INVALID_CHARACTER;
		}
		return Error::OK;
	}
	static void encode_utf8(unsigned& u, string& s) {
		if (u <= 0x7F)
			s += (u & 0xFF);
		else if (u <= 0x7FF) {
			s += (0xC0 | (0xFF & (u >> 6)));
			s += (0x80 | (0x3F & u));
		}
		else if (u <= 0xffff) {
			s += (0xE0 | (0xFF & (u >> 12)));
			s += (0x80 | (0x3F & (u >> 6)));
			s += (0x80 | (0x3F & u));
		}
		else {
			s += (0xF0 | (0xFF & (u >> 18)));
			s += (0x80 | (0x3F & (u >> 12)));
			s += (0x80 | (0x3F & (u >> 6)));
			s += (0x80 | (0x3F & u));
		}
	}
	static Error read_String(const char*& it, string& s) {
		char ch = 0;
		it++;
		while (1) {
			ch = *it++;
			switch (ch) {
			case '\"':return Error::OK;
			case '\\':
				CHECK_END;
				switch (*it++) {
				case '"': s += '"'; break;
				case 'n': s += '\n'; break;
				case 'r': s += '\r'; break;
				case 't': s += '\t'; break;
				case 'f': s += '\f'; break;
				case 'b': s += '\b'; break;
				case '/': s += '/'; break;
				case '\\': s += '\\'; break;
				case 'u': {
					unsigned u = 0;
					read_Hex4(it, u);
					if (u >= 0xD800 && u <= 0xDBFF) {
						CHECK_END;
						if (*it++ != '\\')
							return Error::INVALID_CHARACTER;
						if (*it++ != 'u')
							return Error::INVALID_CHARACTER;
						unsigned tmp_u;
						read_Hex4(it, tmp_u);
						if (tmp_u < 0xDC00 || tmp_u > 0xDFFF)
							return Error::INVALID_CHARACTER;
						u = 0x10000 + (u - 0xD800) * 0x400 + (tmp_u - 0xDC00);
					}
					if (u > 0x10FFFF)
						return Error::INVALID_CHARACTER;
					encode_utf8(u, s);
					break;
				}
				default:return Error::UNKNOW_ESCAPE;
				}
				break;
			default:
				//if (ch < ' ')return 0;
				s += ch;
				break;
			}
		}
		return Error::OK;
	}

	union Value {
		bool b; int i; long long l; double d;
		char* s; Array* a; Object* o;
	} data;
	Type t;
};

ostream& operator<<(ostream& o, const Json::Error e) {
	if (e == Json::Error::OK)
		return o << "OK";
	else
		return o << "Error:" << (int)e;
}
#undef addTab
#undef CHECK_END
#undef JsonAssert
#undef CHECK
