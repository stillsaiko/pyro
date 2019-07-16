# pragma once
# include <wav.h> // LR
# include <vector>
struct LR { short L, R ; };
namespace pyro {
	struct note {
		~
		note(void);
		note(void);
		note(char key, size_t n);
		note& operator = (note&&)noexcept ;
		void flush(LR*, size_t);
	private:public:
		size_t pitch = 0u;
		size_t n = 0u ;
		float * decay = nullptr ;
		size_t iter = 0u ;
	};
}