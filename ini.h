/**
 * Copyright (c) 2016 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `ini.c` for details.
 */

# pragma once

# include "rc.h"
# include "lex.h"
# include "b40.h"
struct INI {
	enum { SECTION, COMMENT, KEY };
	struct K :
	public B40LL,
	public LEX::A {
		K(B40LL&&, const LEX::A &);
	};
	class S : public B40LL {
		K * L = nullptr ;
		size_t Ln = 0UL ;
	public:
		S(B40LL&&);
		void insert(intptr_t, B40LL&&, const LEX::A &);
		K * operator[ ](unsigned long long);
		K * begin(void);
		K * end(void);
	};
	S * L = nullptr ;
	size_t Ln = 0UL ;
	S * from = nullptr ;
	S * to = nullptr ;
	S & operator[ ](unsigned long long K);
	S * begin(void);
	S * end(void);
	~
	INI(void);
	INI(void);
	INI(RC&&);
/*	B40<unsigned long long> val ;
	struct X {
		bool is_section ;
	};
	LEX::X * begin(void);
	LEX::X * end(void);*/
};
/*# include "b40.h"
# include <type_traits> // std::move <utility>
struct INI {
	struct L {
		B40<unsigned long long> name ;
		char * value = nullptr ;
		inline L(void){ }
		inline L(B40<unsigned long long> name, char * value): name(std::move(name)), value(value){ }
		inline L(L&& a){
			name = std::move(a.name);
			value = a.value ;
			a.value = nullptr ;
		}
		inline L& operator = (L&& a)noexcept {
			name = std::move(a.name);
			value = a.value ;
			a.value = nullptr ;
			return *this ;
		}
	};
//	std::vector<row> vector ;
	inline ~
	INI(void);
	inline INI(void);
	inline INI(RC&&);
	inline L * begin(void);
	inline L * end(void);
	inline INI& operator = (INI&&)noexcept ;
	inline L & operator[ ](size_t);
	const size_t count = 0u ;
private:
	L * Ls = nullptr ;
};
# include <list>
inline INI::~INI(void){
	if(Ls){
		for(size_t i=0u; i < count; ++i)
			if( Ls[i].value )
				delete[ ] Ls[i].value ; // move to L's dtor
		delete[ ] Ls ;
	}
}
inline INI::INI(void){ }
inline INI::INI(RC&& file){
	std::list<L> buffer ;
	const char * end(nullptr);
	if(const char * begin = &file[0])
	while(end = strstr(begin, "\n")){
		char name[48], value[48] = {0}; // buffer
		if(*begin == '[')	sscanf(nullptr, "[%s]", name);
		else				sscanf(nullptr, "%s=%s", name, value);
		buffer.emplace_back(B40<unsigned long long>(name), *value?strcpy(new char[strlen(value)+1], value):nullptr);
		begin = end ;
	};
	//memcpy()...
	Ls = new L[const_cast<size_t&>(count) = buffer.size( )];
	for(size_t i(0u); buffer.size( ); ++ i){
		Ls[i] = std::move( buffer.front( ) );
		buffer.pop_front( );
	}
}
inline INI& INI::operator = (INI&& a)noexcept {
	Ls = a.Ls ; a.Ls = nullptr ;
	const_cast<size_t&>(count) = a.count ;
	const_cast<size_t&>(a.count) = 0u ;
	return *this ;
}
inline INI::L & INI::operator[ ](size_t i){
	assert(Ls);
	assert(i < count);
	return Ls[i];
}
*/
// include <memory> // std::shared_ptr

#define INI_VERSION "0.1.1"

struct ini_t {
  char *data;
  char *end;
};


# include <string>
class ini {
	ini_t * shared ;
	std::string __section ; // not in use
public:
	inline~ini(void);
	inline ini(void);
	inline ini(RC&&);
	inline void operator = (ini&&)noexcept ;
	inline char const * operator[ ](const char *);
	inline int scanf(const char * key, const char * fmt, ...);
	inline operator bool(void)const { return shared ; }
};
/**
 * Copyright (c) 2016 rxi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/* Case insensitive string compare */
inline int strcmpci(const char *a, const char *b) {
  for (;;) {
    int d = tolower(*a) - tolower(*b);
    if (d != 0 || !*a) {
      return d;
    }
    a++, b++;
  }
}

/* Returns the next string in the split data */
inline char* next(ini_t *ini, char *p) {
  p += strlen(p);
  while (p < ini->end && *p == '\0') {
    p++;
  }
  return p;
}

inline void trim_back(ini_t *ini, char *p) {
  while (p >= ini->data && (*p == ' ' || *p == '\t' || *p == '\r')) {
    *p-- = '\0';
  }
}

inline char* discard_line(ini_t *ini, char *p) {
  while (p < ini->end && *p != '\n') {
    *p++ = '\0';
  }
  return p;
}


inline char *unescape_quoted_value(ini_t *ini, char *p) {
  /* Use `q` as write-head and `p` as read-head, `p` is always ahead of `q`
   * as escape sequences are always larger than their resultant data */
  char *q = p;
  p++;
  while (p < ini->end && *p != '"' && *p != '\r' && *p != '\n') {
    if (*p == '\\') {
      /* Handle escaped char */
      p++;
      switch (*p) {
        default   : *q = *p;    break;
        case 'r'  : *q = '\r';  break;
        case 'n'  : *q = '\n';  break;
        case 't'  : *q = '\t';  break;
        case '\r' :
        case '\n' :
        case '\0' : goto end;
      }

    } else {
      /* Handle normal char */
      *q = *p;
    }
    q++, p++;
  }
end:
  return q;
}


/* Splits data in place into strings containing section-headers, keys and
 * values using one or more '\0' as a delimiter. Unescapes quoted values */
inline void split_data(ini_t *ini) {
  char *value_start, *line_start;
  char *p = ini->data;

  while (p < ini->end) {
    switch (*p) {
      case '\r':
      case '\n':
      case '\t':
      case ' ':
        *p = '\0';
        /* Fall through */

      case '\0':
        p++;
        break;

      case '[':
        p += strcspn(p, "]\n");
        *p = '\0';
        break;

      case ';':
        p = discard_line(ini, p);
        break;

      default:
        line_start = p;
        p += strcspn(p, "=\n");

        /* Is line missing a '='? */
        if (*p != '=') {
          p = discard_line(ini, line_start);
          break;
        }
        trim_back(ini, p - 1);

        /* Replace '=' and whitespace after it with '\0' */
        do {
          *p++ = '\0';
        } while (*p == ' ' || *p == '\r' || *p == '\t');

        /* Is a value after '=' missing? */
        if (*p == '\n' || *p == '\0') {
          p = discard_line(ini, line_start);
          break;
        }

        if (*p == '"') {
          /* Handle quoted string value */
          value_start = p;
          p = unescape_quoted_value(ini, p);

          /* Was the string empty? */
          if (p == value_start) {
            p = discard_line(ini, line_start);
            break;
          }

          /* Discard the rest of the line after the string value */
          p = discard_line(ini, p);

        } else {
          /* Handle normal value */
          p += strcspn(p, "\n");
          trim_back(ini, p - 1);
        }
        break;
    }
  }
}
// ini.cpp
inline ini::~ini(void){
	if( ini_t * ini = shared ){
		free(ini->data);
		delete shared ;
		shared = nullptr ;
	}
}
inline ini::ini(void){ }
# include <cassert>
inline ini::ini(RC&& a){
  ini_t *ini = NULL;
  int sz;

  /* Init ini struct */
	ini = shared = new ini_t ;
  //assert( ini = (ini_t*)malloc(sizeof(*ini)) );
  memset(ini, 0, sizeof(*ini));

  /* Get file size */
  sz = a.n ;

  /* Load file content into memory, null terminate, init end var */
  ini->data = (char*)malloc(sz + 1);
  ini->data[sz] = '\0';
  ini->end = ini->data + sz;
  memcpy(ini->data, &a[0], sz);

  /* Prepare data */
  split_data(ini);

  /* Clean up and return */

}
inline void ini::operator = (ini&& a)noexcept {
	shared = a.shared ; a.shared = nullptr ;
	__section = a.__section ; a.__section = nullptr ;
}
inline const char * ini::operator[ ](char const * key){
	if(!shared)return nullptr ;
  const char *current_section = "";
  char *val;
  char *p = shared->data;

  if (*p == '\0') {
    p = next(shared, p);
  }

  while (p < shared->end) {
    if (*p == '[') {
      /* Handle section */
      current_section = p + 1;

    } else {
      /* Handle key */
      val = next(shared, p);
      if (!__section.size( ) || !strcmpci(__section.c_str( ), current_section)) {
        if (!strcmpci(p, key)) {
          return val;
        }
      }
      p = val;
    }

    p = next(shared, p);
  }

  return NULL;
}
# include <cstdarg>
inline int ini::scanf(const char * key, const char * fmt, ...){
//  const char *val = ini_get(shared.get( ), __section.size( )?__section.c_str( ):nullptr, key);
	const char *val = operator[ ](key);
  if (!val) {
    return 0;
  }
//  if (scanfmt) {
	va_list va ;
	va_start(va, fmt);
    int n = vsscanf(val, fmt, va);
	va_end(va);
//  } else {
//    *((const char**) dst) = val;
//  }
	return n;
//  return 1;
}