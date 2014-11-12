#ifndef POSEIDON_EXCEPTION_HPP_
#define POSEIDON_EXCEPTION_HPP_

#include "cxx_ver.hpp"
#include <exception>
#include <cerrno>
#include <cstddef>
#include "shared_ntmbs.hpp"

namespace Poseidon {

class Exception : public std::exception {
protected:
	const char *const m_file;
	const std::size_t m_line;
	const SharedNtmbs m_message; // 拷贝构造函数不抛出异常。

public:
	Exception(const char *file, std::size_t line, SharedNtmbs message) NOEXCEPT;
	~Exception() NOEXCEPT;

public:
	const char *what() const NOEXCEPT {
		return m_message.get();
	}

	const char *file() const NOEXCEPT {
		return m_file;
	}
	std::size_t line() const NOEXCEPT {
		return m_line;
	}
};

class SystemError : public Exception {
private:
	const int m_code;

public:
	SystemError(const char *file, std::size_t line, int code = errno) NOEXCEPT;
	~SystemError() NOEXCEPT;

public:
	int code() const NOEXCEPT {
		return m_code;
	}
};

class ProtocolException : public Exception {
private:
	const unsigned m_code;

public:
	ProtocolException(
		const char *file, std::size_t line, SharedNtmbs message, unsigned code) NOEXCEPT;
	~ProtocolException() NOEXCEPT;

public:
	unsigned code() const NOEXCEPT {
		return m_code;
	}
};

}

#define DEBUG_THROW(etype_, ...)	throw etype_(__FILE__, __LINE__, ## __VA_ARGS__)

#endif
